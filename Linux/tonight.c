#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <locale.h>
#include <errno.h>
#include <stdarg.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <stropts.h>
#include "tonight.h"

static char c;
static int i;
static float f;
static double d;
static char str[1001];

static char __buffer[1024];
static int text_color = 7, background_color = 0;

/* Exceptions */
static EXCEPTION_DEFINE ___GenericException = {"Generic exception throwed", NULL};
EXCEPTION TONIGHT GenericException = &___GenericException;

static EXCEPTION_DEFINE ___AssertException = {"Assert fail", &GenericException};
static EXCEPTION_DEFINE ___ErrnoException = {"Errno error", &GenericException};
static EXCEPTION_DEFINE ___MemoryAllocException = {"Memory allocate error", &GenericException};
static EXCEPTION_DEFINE ___ArrayIndexBoundException = {"Invalid array index", &GenericException};
static EXCEPTION_DEFINE ___FileOpenException = {"File open error", &GenericException};
static EXCEPTION_DEFINE ___InputException = {"Input error", &GenericException};
static EXCEPTION_DEFINE ___ConvertException = {"Convert error", &GenericException};
static EXCEPTION_DEFINE ___NotImplementException = {"Not implemented method error", &GenericException};

EXCEPTION TONIGHT AssertException = &___AssertException;
EXCEPTION TONIGHT ErrnoException = &___ErrnoException;
EXCEPTION TONIGHT MemoryAllocException = &___MemoryAllocException;
EXCEPTION TONIGHT ArrayIndexBoundException = &___ArrayIndexBoundException;
EXCEPTION TONIGHT FileOpenException = &___FileOpenException;
EXCEPTION TONIGHT InputException = &___InputException;
EXCEPTION TONIGHT ConvertException = &___ConvertException;
EXCEPTION TONIGHT NotImplementException = &___NotImplementException;

/* try - catch - throw */

enum ctrl{
	CTRL_CONTINUE,
	CTRL_FINALLY,
	CTRL_CATCH,
	CTRL_BREAK,
	CTRL_TRY
};

typedef struct{
	pointer jump;
	int ctrl;
	bool inside_try;
	bool exec_try;
	bool thrown;
	bool final;
}strContext, *Context;

typedef struct{
	Context context;
	pointer next;
}Stack_node, *Stack;

static strContext begin = {
	NULL, CTRL_CONTINUE, false, false, false, false
};

static struct{
	Stack stack;
	Context current;
	Exception value;
}except = {NULL, &begin, NULL};

static Context createContext(void){
	Context ctxt = calloc(1, sizeof(strContext));
	if(!ctxt) exit(EXIT_FAILURE);
	ctxt->jump = malloc(sizeof(jmp_buf));
	if(!ctxt->jump) exit(EXIT_FAILURE);
	return ctxt;
}

static void deleteContext(Context ctxt){
	if(ctxt){
		if(ctxt->jump) free(ctxt->jump);
		free(ctxt);
	}
}

static void push_context(Context value){
	Stack node = malloc(sizeof(Stack_node));
	if(!node) exit(EXIT_FAILURE);
	node->context = value;
	node->next = except.stack;
	except.stack = node;
}

static Context pop_context(void){
	Stack node = except.stack;
	if(node){
		Context ctx = node->context;
		except.stack = node->next;
		free(node);
		return ctx;
	}
	return NULL;
}

Exception TONIGHT getException(void){
	return except.value;
}

pointer TONIGHT __create_try_context(void){
	Context ctxTry = createContext();
	ctxTry->inside_try = true;
	ctxTry->ctrl = CTRL_TRY;
	push_context(except.current);
	except.current = ctxTry;
	except.current->exec_try = false;
	except.current->final = false;
	return ctxTry->jump;
}

INLINE void TONIGHT __restaure_try_context(void){
	deleteContext(except.current);
	except.current = pop_context();
}

bool TONIGHT __try_context(void){
	switch(except.current->ctrl){
		case CTRL_TRY:
			except.current->ctrl = CTRL_BREAK;
			except.current->exec_try = true;
			return true;
		case CTRL_BREAK:
			__restaure_try_context();
		case CTRL_CONTINUE:
			return false;
		case CTRL_CATCH:
			except.current->ctrl = CTRL_BREAK;
			return true;
		case CTRL_FINALLY:
			except.current->ctrl = CTRL_CONTINUE;
			except.current->final = true;
			return true;
	}
}

bool TONIGHT __function_try(void){
	if(except.current->exec_try){
		except.current->exec_try = false;
		return true;
	}
	return false;
}

bool TONIGHT __function_catch(EXCEPTION _exception){
	if(except.current->thrown){
		EXCEPTION *_e = &except.value->exception;
		while(_e){
			if(*_e == _exception){
				__restaure_try_context();
				except.current->ctrl = CTRL_FINALLY;
				except.current->thrown = false;
				return true;
			}
			_e = (*_e)->_super;
		}
	}
	return false;
}

bool TONIGHT __function_finally(void){
	if(except.current->final){
		except.current->final = false;
		return true;
	}
	return false;
}

void TONIGHT THROW(EXCEPTION __exc, string message){
	if(except.current->inside_try){
		static _Exception exc;
		exc.exception = __exc;
		exc.message = message;
		except.current->thrown = true;
		except.value = &exc;
		except.current->ctrl = CTRL_CATCH;
		longjmp(except.current->jump, 1);
	}
}

INLINE string TONIGHT Error(Exception exc){
	return exc->exception->error_name;
}

INLINE string TONIGHT Message(Exception exc){
	return exc->message;
}

INLINE EXCEPTION TONIGHT ExceptionType(Exception exc){
	return exc->exception;
}

/* Functions */

/**
*	@Atention!
*	
*	Function: pressKey
*	This function needs be changed
*/
static bool TONIGHT pressKey(void){
	static int bytesWaiting;
	static struct termios old_term, new_term;
	tcgetattr(stdin->_fileno, &old_term);
	new_term = old_term;
	new_term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(stdin->_fileno, TCSANOW, &new_term);
	ioctl(stdin->_fileno, FIONREAD, &bytesWaiting);
	tcsetattr(stdin->_fileno, TCSANOW, &old_term);
	return bytesWaiting ? true : false;
}

static int TONIGHT getKey(void){
	struct termios oldattr, newattr;
	tcgetattr(stdin->_fileno, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);
	newattr.c_cc[VTIME] = 0;
	newattr.c_cc[VMIN] = 1;
	tcsetattr(stdin->_fileno, TCSANOW, &newattr);
	newattr.c_cc[VMIN] = 0;
	i = 0;
	while(true){
		c = getchar();
		if(!c || c == EOF) break;
		if(!i) tcsetattr(stdin->_fileno, TCSANOW, &newattr);
		i += c;
	}
	tcsetattr(stdin->_fileno, TCSANOW, &oldattr);
	return i;
}

static INLINE int TONIGHT getKeyEcho(void){
	putchar((char)(i = getKey()));
	return i;
}

static void __assert(bool test){
	if(!test)
		throw(AssertException, "Assert test failed");
}

static void __checkErrno(void){
	if(errno)
		throw(ErrnoException, strerror(errno));
}

INLINE void TONIGHT __sleep(unsigned int miliseconds){
	usleep(miliseconds * 1000);
}

INLINE double TONIGHT decimal(double n){
	return n - (long int)n;
}

INLINE void TONIGHT cursor_position(int x, int y){
	printf("\033[%d;%dH", y, x);
}

INLINE string TONIGHT __locale(void){
	return setlocale(LC_ALL, "");
}

INLINE static pointer __Default_void_function(){
	THROW(NotImplementException, "Function not implemented");
	return NULL;
}

INLINE static void __initRandom(void){
	srand((unsigned int)time(NULL));
}

static INLINE string TONIGHT __concatString(char dest[], char from[], int length){
	return strncat(dest, from, length - strlen(dest) - 1);
}

INLINE string TONIGHT toString(register char __array[]){
	return strcpy(Memory.alloc((strlen(__array) + 1) * sizeof(char)), __array);
}

string TONIGHT concat(string wrd_1, ...){
	va_list va;
	static char s[1001];
	static string p;
	*s = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, string))
		__concatString(s, p, sizeof s);
	va_end(va);
	return toString(s);
}

string TONIGHT nconcat(int size, string wrd_1, ...){
	va_list va;
	static char ARRAY s = NULL;
	static string p;
	if(s)
		Array.free(s);
	s = Array.Char(size + 1);
	*s = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, string))
		strcat(s, p);
	va_end(va);
	return toString(s);
}

retString TONIGHT retConcat(string wrd_1, ...){
	va_list va;
	string p;
	static retString ret;
	*ret.Text = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, string))
		__concatString(ret.Text, p, sizeof ret);
	va_end(va);
	return ret;
}

bool TONIGHT equal(register string const wrd_1, register string const wrd_2){
	register string s1 = wrd_1, s2 = wrd_2;
	while(*s1 && *s2){
		if(*s1 != *s2){
			if(isupper(*s1))
				if(tolower(*s1) != *s2)
					return false;
			if(islower(*s1))
				if(toupper(*s1) != *s2)
					return false;
		}
		s1++; s2++;
	}
	return (bool)*s1 == *s2;
}

string TONIGHT s_cs(char var){
	char c[] = {var, 0};
	return toString(c);
}

string TONIGHT s_bs(bool var){
	return var ? toString("TRUE") : toString("FALSE");
}

string TONIGHT s_is(int var){
	static char s[15];
	snprintf(s, sizeof s, "%i", var);
	return toString(s);
}

string TONIGHT s_fsf(float var, int _decimal){
	static char s[100];
	snprintf(s, sizeof s, "%.*f", _decimal, var);
	return toString(s);
}

string TONIGHT s_dsf(double var, int _decimal){
	static char s[100];
	snprintf(s, sizeof s, "%.*lf", _decimal, var);
	return toString(s);
}

string TONIGHT s_ds(double var){
	double n;
	static char s[100];
	snprintf(s, sizeof s, "%.10g", var);
	return toString(s);
}

INLINE string TONIGHT s_fs(float var){
	return s_ds((double)var);
}

retString TONIGHT cs(char var){
	register char *s = s_cs(var);
	static retString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

retString TONIGHT bs(bool var){
	register char *s = s_bs(var);
	static retString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

retString TONIGHT is(int var){
	register char *s = s_is(var);
	static retString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

retString TONIGHT fsf(float var, int _decimal){
	register char *s = s_fsf(var, _decimal);
	static retString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

retString TONIGHT dsf(double var, int _decimal){
	register char *s = s_dsf(var, _decimal);
	static retString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

retString TONIGHT ds(double var){
	register char *s = s_ds(var);
	static retString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

INLINE retString TONIGHT fs(float var){
	return ds((double)var);
}

long_retString TONIGHT longRetConcat(string wrd_1, ...){
	va_list va;
	string p;
	static long_retString ret;
	*ret.Text = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, string))
		__concatString(ret.Text, p, sizeof ret);
	va_end(va);
	return ret;
}

long_retString TONIGHT cls(char var){
	register char *s = s_cs(var);
	static long_retString ret;
	strncpy(ret.Text, s, sizeof ret);
	free(s);
	return ret;
}

long_retString TONIGHT bls(bool var){
	register char *s = s_bs(var);
	static long_retString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

long_retString TONIGHT ils(int var){
	register char *s = s_is(var);
	static long_retString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

long_retString TONIGHT fls(float var){
	register char *s = s_fs(var);
	static long_retString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

long_retString TONIGHT dls(double var){
	register char *s = s_ds(var);
	static long_retString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

long_retString TONIGHT flsf(float var, int d){
	register char *s = s_fsf(var, d);
	static long_retString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

long_retString TONIGHT dlsf(double var, int d){
	register char *s = s_dsf(var, d);
	static long_retString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

retString TONIGHT formated(const string format, ...){
	va_list v;
	retString ret;
	va_start(v, format);
	vsnprintf(ret.Text, sizeof ret, format, v);
	va_end(v);
	return ret;
}

long_retString TONIGHT longFormated(const string format, ...){
	va_list v;
	long_retString ret;
	va_start(v, format);
	vsnprintf(ret.Text, sizeof ret, format, v);
	va_end(v);
	return ret;
}

/* Functions to Tonight.std.Console.input */

static char TONIGHT $throws __Scanner_nextChar(void){
	if(scanf("%c", &c) != 1)
		throw(InputException, "Impossible to read a \"char\" from the standard input");
	return c;
}

static int TONIGHT $throws __Scanner_nextInt(void){
	if(scanf("%i", &i) != 1)
		throw(InputException, "Impossible to read an \"int\" from the standard input");
	return i;
}

static float TONIGHT $throws __Scanner_nextFloat(void){
	if(scanf("%f", &f) != 1)
		throw(InputException, "Impossible to read a \"float\" from the standard input");
	return f;
}

static double TONIGHT $throws __Scanner_nextDouble(void){
	if(scanf("%lf", &d) != 1)
		throw(InputException, "Impossible to read a \"double\" from the standard input");
	return d;
}

static string TONIGHT $throws __Scanner_next(void){
	if(scanf("%1000s", str) != 1)
		throw(InputException, "Impossible to read a \"string\" from the standard input");
	return toString(str);
}

static string TONIGHT $throws __Scanner_nextLine(void){
	if(scanf(" %1000[^\n]s", str) != 1)
		throw(InputException, "Impossible to read a \"string\" from the standard input");
	return toString(str);
}

static string TONIGHT __Scanner_Password(int nchar){
	int i = 0;
	char* senha = Array.Char(nchar + 1);
	while((senha[i] = Tonight.getKey()) != key_ENTER){
		if(senha[i] != key_BS && i < nchar){
			printf("*");
			i++;
		}
		else if(i != 0){
			printf("\b \b");
			i--;
		}
	}
	senha[i] = '\0';
	return (senha);
}

static INLINE void TONIGHT  __Scanner_clear(void){
	while(!feof(stdin))
		if(fgetc(stdin) == '\n')
			return;
}

static INLINE void TONIGHT __Scanner_ignore(void){
	scanf("%*s");
}

static INLINE void TONIGHT __Scanner_ignoreChar(void){
	scanf("%*c");
}

/* Functions to Tonight.std.file.input */
static char TONIGHT $throws __Scanner_file_nextChar(file _file){
	if(fscanf(_file, "%c", &c) != 1)
		throw(InputException, "Impossible to read a \"char\" from the file");
	return c;
}

static int TONIGHT $throws __Scanner_file_nextInt(file _file){
	if(fscanf(_file, "%i", &i) != 1)
		throw(InputException, "Impossible to read an \"int\" from the file");
	return i;
}

static float TONIGHT $throws __Scanner_file_nextFloat(file _file){
	if(fscanf(_file, "%f", &f) != 1)
		throw(InputException, "Impossible to read a \"float\" from the file");
	return f;
}

static double TONIGHT $throws __Scanner_file_nextDouble(file _file){
	if(fscanf(_file, "%lf", &d) != 1)
		throw(InputException, "Impossible to read a \"double\" from the file");
	return d;
}

static string TONIGHT $throws __Scanner_file_next(file _file){
	if(fscanf(_file, "%1000s", str) != 1)
		throw(InputException, "Impossible to read a \"string\" from the file");
	return toString(str);
}

static string TONIGHT $throws __Scanner_file_nextLine(file _file){
	if(fscanf(_file, " %1000[^\n]s", str) != 1)
		throw(InputException, "Impossible to read a \"string\" from the file");
	return toString(str);
}

static INLINE void TONIGHT __Scanner_file_clear(file _file){
	while(!feof(_file))
		if(fgetc(_file) == '\n')
			return;
}

static INLINE void TONIGHT __Scanner_file_ignore(file _file){
	fscanf(_file, "%*s");
}

static INLINE void TONIGHT __Scanner_file_ignoreChar(file _file){
	fscanf(_file, "%*c");
}

/* Functions to Tonight.std.string.input */
static char TONIGHT $throws __Scanner_string_nextChar(string str){
	if(sscanf(str, "%c", &c) != 1)
		throw(InputException, "Impossible to read a \"char\" from the string");
	return c;
}

static int TONIGHT $throws __Scanner_string_nextInt(string str){
	if(sscanf(str, "%i", &i) != 1)
		throw(InputException, "Impossible to read an \"int\" from the string");
	return i;
}

static float TONIGHT $throws __Scanner_string_nextFloat(string str){
	if(sscanf(str, "%f", &f) != 1)
		throw(InputException, "Impossible to read a \"float\" from the string");
	return f;
}

static double TONIGHT $throws __Scanner_string_nextDouble(string str){
	if(sscanf(str, "%lf", &d) != 1)
		throw(InputException, "Impossible to read a \"double\" from the string");
	return d;
}

static string TONIGHT $throws __Scanner_string_next(string s){
	if(sscanf(s, "%1000s", str) != 1)
		throw(InputException, "Impossible to read a \"string\" from the string");
	return toString(s);
}

static string TONIGHT $throws __Scanner_string_nextLine(string s){
	if(sscanf(s, " %1000[^\n]s", str) != 1)
		throw(InputException, "Impossible to read a \"string\" from the string");
	return toString(s);
}

static void TONIGHT __Scanner_string_clear(string str){
	while(*str != '\n')
		++ str;
}

static void TONIGHT __Scanner_string_ignore(string str){
	sscanf(str, "%*s");
}

static void TONIGHT __Scanner_string_ignoreChar(string str){
	sscanf(str, "%*c");
}

/* Functions to Tonight.std.object.input */
static char TONIGHT $throws __Scanner_object_nextChar(IScanner iScan, object obj){
	string s = iScan.getString(obj);
	char c = __Scanner_string_nextChar(s);
	free(s);
	return c;
}

static int TONIGHT $throws __Scanner_object_nextInt(IScanner iScan, object obj){
	string s = iScan.getString(obj);
	int i = __Scanner_string_nextInt(s);
	free(s);
	return i;
}

static float TONIGHT $throws __Scanner_object_nextFloat(IScanner iScan, object obj){
	string s = iScan.getString(obj);
	float f = __Scanner_string_nextFloat(s);
	free(s);
	return f;
}

static double TONIGHT $throws __Scanner_object_nextDouble(IScanner iScan, object obj){
	string s = iScan.getString(obj);
	double d = __Scanner_string_nextDouble(s);
	free(s);
	return d;
}

static string TONIGHT $throws __Scanner_object_next(IScanner iScan, object obj){
	string s = iScan.getString(obj);
	string str = __Scanner_string_next(s);
	free(s);
	return str;
}

static INLINE string TONIGHT __Scanner_object_nextLine(IScanner iScan, object obj){
	return iScan.getString(obj);
}

static INLINE void TONIGHT  __Scanner_object_clear(IScanner iScan, object obj){
	iScan.setString(obj, "");
}

static INLINE void TONIGHT __Scanner_object_ignore(IScanner iScan, object obj){
	string s = iScan.getString(obj);
	free(s);
}

static INLINE void TONIGHT __Scanner_object_ignoreChar(IScanner iScan, object obj){
	string s = iScan.getString(obj);
	iScan.setString(obj, ++s);
	free(s);
}

/* Functions to Tonight.std.Console.output */
static void TONIGHT __Recorder_text(file, string);
static INLINE void TONIGHT __Recorder_textln(file, string);

static INLINE void TONIGHT __Screen_text(string txt){
	__Recorder_text(stdout, txt);
}

static INLINE void TONIGHT __Screen_textln(string txt){
	__Recorder_textln(stdout, txt);
}

static void TONIGHT __Screen_print(string txt, ...){
	va_list t;
	register string s;
	va_start(t, txt);
	for(s = txt; s; s = va_arg(t, string))
		__Screen_text(s);
	va_end(t);
}

static void TONIGHT __Screen_println(string txt, ...){
	va_list t;
	register string s;
	for(s = txt; s; s = va_arg(t, string))
		__Screen_text(s);
	va_end(t);
	putchar('\n');
}

static void TONIGHT __Screen_printargln(string txt, ...){
	va_list t;
	register string s;
	va_start(t, txt);
	for(s = txt; s; s = va_arg(t, string))
		__Screen_textln(s);
	va_end(t);
}

static void TONIGHT __Screen_nl(void){
	putchar('\n');
}

static void TONIGHT __Screen_nls(int qtd){
	while(qtd--)
		putchar('\n');
}

static void TONIGHT __Screen_buffer(void){
	setbuf(stdout, __buffer);
}

static void TONIGHT __Screen_clear(void){
	if(!fflush(stdout))
		throw(GenericException, strerror(errno));
}

static void TONIGHT __clearScreen(void){
	printf("\e[2J\e[H");
}

/* Functions to Tonight.std.file.output */
static void TONIGHT __Recorder_text(file _file, string txt){
	fprintf(_file, "%s", txt);
}

static INLINE void TONIGHT __Recorder_textln(file _file, string txt){
	fprintf(_file, "%s\n", txt);
}

static void TONIGHT __Recorder_print(file _file, string txt, ...){
	va_list t;
	string s;
	va_start(t, txt);
	for(s = txt; s; s = va_arg(t, string))
		fprintf(_file, "%s", s);
	va_end(t);
}

static void TONIGHT __Recorder_println(file _file, string txt, ...){
	va_list t;
	string s;
	va_start(t, txt);
	for(s = txt; s; s = va_arg(t, string))
		fprintf(_file, "%s", s);
	va_end(t);
	putc('\n', _file);
}

static void TONIGHT __Recorder_printargln(file _file, string txt, ...){
	va_list t;
	string s;
	va_start(t, txt);
	for(s = txt; s; s = va_arg(t, string))
		fprintf(_file, "%s\n", s);
	va_end(t);
}

static INLINE void TONIGHT __Recorder_nl(file __file){
	fputc('\n', __file);
}

static INLINE void TONIGHT __Recorder_nls(file __file, int qtd){
	while(qtd--)
		fputc('\n', __file);
}

static void TONIGHT __Recorder_buffer(file __file){
	setbuf(__file, __buffer);
}

static void TONIGHT $throws __Recorder_clear(file __file){
	if(!fflush(__file))
		throw(GenericException, strerror(errno));
}

/* Functions to Tonight.std.error */
static void TONIGHT __Error_text(string txt){
	fprintf(stderr, "%s", txt);
}

static INLINE void TONIGHT __Error_textln(string txt){
	fprintf(stderr, "%s\n", txt);
}

static void TONIGHT __Error_print(string txt, ...){
	va_list t;
	string s;
	va_start(t, txt);
	for(s = txt; s; s = va_arg(t, string))
		fprintf(stderr, "%s", s);
	va_end(t);
}

static void TONIGHT __Error_println(string txt, ...){
	va_list t;
	string s;
	va_start(t, txt);
	for(s = txt; s; s = va_arg(t, string))
		fprintf(stderr, "%s", s);
	va_end(t);
	putc('\n', stderr);
}

static void TONIGHT __Error_printargln(string txt, ...){
	va_list t;
	string s;
	va_start(t, txt);
	for(s = txt; s; s = va_arg(t, string))
		fprintf(stderr, "%s\n", s);
	va_end(t);
}

static INLINE void TONIGHT __Error_nl(void){
	fputc('\n', stderr);
}

static INLINE void TONIGHT __Error_nls(int qtd){
	while(qtd--)
		fputc('\n', stderr);
}

static void TONIGHT __Error_buffer(void){
	setbuf(stderr, __buffer);
}

static void TONIGHT $throws __Error_clear(void){
	if(!fflush(stderr))
		throw(GenericException, strerror(errno));
}

/* Functions to Tonight.std.string.output */
static void TONIGHT __String_text(char *str, string txt){
	sprintf(str, "%s", txt);
}

static void TONIGHT __String_textln(char *str, string txt){
	sprintf(str, "%s\n", txt);
}

static void TONIGHT __String_print(char *str, string txt, ...){
	string s;
	va_list v;
	va_start(v, txt);
	for(s = txt; s; s = va_arg(v, string))
		strcat(str, s);
	va_end(v);
}

static void TONIGHT __String_println(char *str, string txt, ...){
	__String_print(str, txt);
	sprintf(str, "%s\n", str);
}

static void TONIGHT __String_printargln(char *str, string txt, ...){
	string s;
	va_list v;
	va_start(v, txt);
	for(s = txt; s; s = va_arg(v, string))
		strcat(str, s);
	va_end(v);
}

/* Functions to Tonight.std.object.output */
static INLINE void TONIGHT __Object_text(IWriter iWrt, object obj, string txt){
	iWrt.addText(obj, txt);
}

static INLINE void TONIGHT __Object_textln(IWriter iWrt, object obj, string txt){
	string s = concat(txt, "\n", $end);
	iWrt.addText(obj, s);
	Memory.free(s);
}

static void TONIGHT __Object_print(IWriter iWrt, object obj, string txt, ...){
	string a;
	va_list v;
	static char s[1000];
	*s = 0;
	va_start(v, txt);
	for(a = txt; a; a = va_arg(v, string))
		strcat(s, a);
	va_end(v);
	iWrt.addText(obj, &s[0]);
}

static void TONIGHT __Object_println(IWriter iWrt, object obj, string txt, ...){
	string a;
	va_list v;
	static char s[1000];
	*s = 0;
	va_start(v, txt);
	for(a = txt; a; a = va_arg(v, string))
		strcat(s, a);
	va_end(v);
	strcat(s, "\n");
	iWrt.addText(obj, &s[0]);
}

static void TONIGHT __Object_printargln(IWriter iWrt, object obj, string txt, ...){
	string a;
	va_list v;
	va_start(v, txt);
	for(a = txt; a; a = va_arg(v, string))
		__Object_println(iWrt, obj, a);
	va_end(v);
}

static void TONIGHT __Object_nl(IWriter iWrt, object obj){
	iWrt.addText(obj, "\n");
}

static void TONIGHT __Object_nls(IWriter iWrt, object obj, int qtd){
	while(qtd--)
		iWrt.addText(obj, "\n");
}

static void TONIGHT __Object_clear(IWriter iWrt, object obj){
	iWrt.clear(obj);
}

/* Functions to the Random class */
static char TONIGHT __Random_simple_nextChar(void){
	return (char)(rand()%256);
}

static INLINE int TONIGHT __Random_simple_nextInt(void){
	return rand();
}

static INLINE double TONIGHT __Random_simple_nextDouble(int _decimal){
	double d = floor((double)rand() / RAND_MAX * pow(10.0, _decimal)) / pow(10.0, _decimal);
	return _decimal ? rand() * d : (double)rand();
}

static INLINE float TONIGHT __Random_simple_nextFloat(int _decimal){
	return (float)__Random_simple_nextDouble(_decimal);
}

static INLINE char TONIGHT __Random_end_nextChar(char _end){
	return (char)(rand() % (_end + 1));
}

static INLINE int TONIGHT __Random_end_nextInt(int _end){
	return rand() % (_end + 1);
}

static INLINE double TONIGHT __Random_end_nextDouble(double _end, int _decimal){
	double d = floor((double)rand() / RAND_MAX * pow(10.0, _decimal)) / pow(10.0, _decimal);
	return _decimal ? ((rand() % (int)_end) + 1.0) * d : (double)(rand() % ((int)_end) + 1);
}

static INLINE float TONIGHT __Random_end_nextFloat(float _end, int _decimal){
	return (float)__Random_end_nextDouble((double)_end, _decimal);
}

static INLINE char TONIGHT __Random_begin_end_nextChar(char _begin, char _end){
	return __Random_end_nextChar(_end - _begin) + _begin;
}

static INLINE int TONIGHT __Random_begin_end_nextInt(int _begin, int _end){
	return __Random_end_nextInt(_end - _begin) + _begin;
}

static INLINE double TONIGHT __Random_begin_end_nextDouble(double _begin, double _end, int _decimal){
	return __Random_end_nextDouble(_end - _begin, _decimal) + _begin;
}

static INLINE float TONIGHT __Random_begin_end_nextFloat(float _begin, float _end, int _decimal){
	return (float)__Random_begin_end_nextDouble((double)_begin, (double)_end, _decimal);
}

/* Functions to Tonight.std.Clock */
static struct tm* TONIGHT __time(void){
	time_t s;
	time(&s);
	return localtime(&s);
}

static INLINE int TONIGHT __Time_hours(void){
	return (__time()->tm_hour);
}

static INLINE int TONIGHT __Time_minutes(void){
	return (__time()->tm_min);
}

static INLINE int TONIGHT __Time_seconds(void){
	return (__time()->tm_sec);
}

static INLINE int TONIGHT __Time_day_week(void){
	return (__time()->tm_wday);
}

static INLINE int TONIGHT __Time_day_month(void){
	return (__time()->tm_mday);
}

static INLINE int TONIGHT __Time_day_year(void){
	return (__time()->tm_yday);
}

static INLINE int TONIGHT __Time_month(void){
	return (__time()->tm_mon + 1);
}

static INLINE int TONIGHT __Time_year(void){
	return (__time()->tm_year + 1900);
}

/* Functions to the Colors class */
static INLINE void TONIGHT __Colors_textbackground(register int _tcolor, register int _bcolor){
	WORD w = (0x0F & (text_color = _tcolor)) + ((0x0F & (background_color = _bcolor)) << 4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), w);
}

static INLINE void TONIGHT __Colors_text(int _color){
	__Colors_textbackground((text_color = _color), background_color);
}

static INLINE void TONIGHT __Colors_background(int _color){
	__Colors_textbackground(text_color, (background_color = _color));
}

/* Initialize objects */
static INLINE Scanner TONIGHT __new_Scanner(Input father){
	return *(Scanner*)&father;
}

static INLINE Writer TONIGHT __new_Writer(Output father){
	return *(Writer*)&father;
}

static INLINE Random TONIGHT __new_Random(RandomicMaker father){
	return *(Random*)&father;
}

static INLINE Timer TONIGHT __new_Timer(TimerCreate father){
	return *(Timer*)&father;
}

static INLINE Painter TONIGHT __new_Painter(ColorCreate father){
	return *(Painter*)&father;
}

static file TONIGHT $throws __new_File(string fName, string fMode){
	file f = fopen(fName, fMode);
	if(!f)
		throw(FileOpenException, concat("Impossible to open the file \"", fName, "\"", $end));
	return f;
}

static object TONIGHT __new_Object(Class_Name name, ...){
	va_list v;
	object _new = Memory.alloc(sizeof(Intern_Object));
	va_start(v, name);
	_new->obj = Memory.alloc(name->size);
	_new->class_pointer = name;
	name->ctor(_new, &v);
	va_end(v);
	return _new;
}

void TONIGHT delete(object self){
	if(!self)
		return;
	if(self->class_pointer->dtor)
		self->class_pointer->dtor(self);
	Memory.free(self);
}

/* Alloc pointers */
static char* TONIGHT $throws __new_char(char value){
	char* c = Memory.alloc(sizeof(char));
	*c = value;
	return c;
}

static bool* TONIGHT $throws __new_bool(bool value){
	bool *b = Memory.alloc(sizeof(bool));
	*b = value;
	return b;
}

static int* TONIGHT $throws __new_int(int value){
	int *i = Memory.alloc(sizeof(int));
	*i = value;
	return i;
}

static float* TONIGHT $throws __new_float(float value){
	float *f = Memory.alloc(sizeof(float));
	*f = value;
	return f;
}

static double* TONIGHT $throws __new_double(double value){
	double *d = Memory.alloc(sizeof(double));
	*d = value;
	return d;
}

static string* TONIGHT $throws __new_String(string value){
	string *s = Memory.alloc(sizeof(string));
	*s = value;
	return s;
}

static pointer TONIGHT $throws __new_pointer(pointer value){
	pointer *p = Memory.alloc(sizeof(pointer));
	*p = value;
	return p;
}

static pointer TONIGHT $throws __new_memory(size_t q){
	pointer p = malloc(q + sizeof(size_t));
	if(!p)
		throw(MemoryAllocException, strerror(errno));
	*(size_t*)p = q;
	return p + sizeof(size_t);
}

static INLINE size_t TONIGHT __memory_size(pointer mem){
	return *(size_t*)(mem - sizeof(size_t));
}

static INLINE pointer TONIGHT __memory_copy(pointer mem) {
	size_t size = Memory.size(mem);
	return memcpy(Memory.alloc(size), mem, size);
}

static INLINE void TONIGHT __memory_free(pointer mem){
	free(mem - sizeof(size_t));
}

/* Initialize arrays */

static pointer TONIGHT $throws alloc_array(size_t size, int lenght){
	pointer p = malloc(sizeof(int) + sizeof(size_t) + size * lenght);
	if(!p)
		throw(MemoryAllocException, strerror(errno));
	*(int*)p = lenght;
	p += sizeof(int);
	*(size_t*)p = size;
	return p + sizeof(size_t);
}

static INLINE char* TONIGHT $throws __new_array_char(int q){
	return alloc_array(sizeof(char), q);
}

static INLINE bool* TONIGHT $throws __new_array_bool(int q){
	return alloc_array(sizeof(bool), q);
}

static INLINE int* TONIGHT $throws __new_array_int(int q){
	return alloc_array(sizeof(int), q);
}

static INLINE float* TONIGHT $throws __new_array_float(int q){
	return alloc_array(sizeof(float), q);
}

static INLINE double* TONIGHT $throws __new_array_double(int q){
	return alloc_array(sizeof(double), q);
}

static INLINE string* TONIGHT $throws __new_array_String(int q){
	return alloc_array(sizeof(string), q);
}

static INLINE object* TONIGHT $throws __new_array_Object(int q){
	return alloc_array(sizeof(object), q);
}

static INLINE pointer* TONIGHT $throws __new_array_pointer(int q){
	return alloc_array(sizeof(pointer), q);
}

static INLINE pointer TONIGHT $throws __new_array_generic(size_t size, int q){
	return alloc_array(size, q);
}

/* Initialize matrixes */
static char** TONIGHT $throws __new_matrix_char(int l, int c){
	char** m = alloc_array(sizeof(char*), l);
	register int i;
	for(i = 0; i < l; i++)
		m[i] = __new_array_char(c);
	return m;
}

static bool** TONIGHT $throws __new_matrix_bool(int l, int c){
	bool** m = alloc_array(sizeof(bool*), l);
	register int i;
	for(i = 0; i < l; i++)
		m[i] = __new_array_bool(c);
	return m;
}

static int** TONIGHT $throws __new_matrix_int(int l, int c){
	int** m = alloc_array(sizeof(int*), l);
	register int i;
	for(i = 0; i < l; i++)
		m[i] = __new_array_int(c);
	return m;
}

static float** TONIGHT $throws __new_matrix_float(int l, int c){
	float** m = alloc_array(sizeof(float*), l);
	register int i;
	for(i = 0; i < l; i++)
		m[i] = __new_array_float(c);
	return m;
}

static double** TONIGHT $throws __new_matrix_double(int l, int c){
	double** m = alloc_array(sizeof(double*), l);
	register int i;
	for(i = 0; i < l; i++)
		m[i] = __new_array_double(c);
	return m;
}

static string** TONIGHT $throws __new_matrix_String(int l, int c){
	string** m = alloc_array(sizeof(string*), l);
	register int i;
	for(i = 0; i < l; i++)
		m[i] = __new_array_String(c);
	return m;
}

static object** TONIGHT $throws __new_matrix_Object(int l, int c){
	object** m = alloc_array(sizeof(object*), l);
	register int i;
	for(i = 0; i < l; i++)
		m[i] = __new_array_Object(c);
	return m;
}

static pointer** TONIGHT $throws __new_matrix_pointer(int l, int c){
	pointer** m = alloc_array(sizeof(pointer*), l);
	register int i;
	for(i = 0; i < l; i++)
		m[i] = __new_array_pointer(c);
	return m;
}

static pointer TONIGHT $throws __new_matrix_generic(size_t size, int l, int c){
	pointer** m = alloc_array(sizeof(pointer*), l);
	register int i;
	for(i = 0; i < l; i++)
		m[i] = __new_array_generic(size, c);
	return m;
}

/* Functions to Convert */
static char TONIGHT char_fromString(string s){
	char ret = *s;
	if(* ++ s)
		throw(ConvertException, "Impossible to convert the string to a char");
	return ret;
}

static bool TONIGHT $throws bool_fromString(string s){
	if(equal(s, "true"))
		return true;
	if(equal(s, "false"))
		return false;
	throw(ConvertException, "Impossible to convert the string to a bool");
	return false;
}

static int TONIGHT $throws int_fromString(string s){
	int i;
	string a;
	i = (int)strtol(s, &a, 0);
	if(*a)
		throw(ConvertException, "Impossible to convert the string to integer");
	return i;
}

static float TONIGHT $throws float_fromString(string s){
	float f;
	string a;
	f = strtof(s, &a);
	if(*a)
		throw(ConvertException, "Impossible to convert the string to float");
	return f;
}

static double TONIGHT $throws double_fromString(string s){
	double d;
	string a;
	d = strtod(s, &a);
	if(*a)
		throw(ConvertException, "Impossible to convert the string to double");
	return d;
}

static string TONIGHT String_formated(const string frmt, ...){
	static char s[1001];
	va_list v;
	va_start(v, frmt);
	vsprintf(s, frmt, v);
	va_end(v);
	return toString(s);
}

/* Functions to Array */
static INLINE int TONIGHT Array_length(pointer array){
	return *(int*)(array - sizeof(size_t) - sizeof(int));
}

static INLINE size_t TONIGHT Array_size(pointer array){
	return *(size_t*)(array - sizeof(size_t));
}

static pointer TONIGHT $throws Array_access(pointer array, int index){
	int lenght = Array_length(array);
	size_t size = Array_size(array);
	if(index < 0 || index >= lenght)
		throw(ArrayIndexBoundException, "Index out of array bounds");
	return array + index * size;
}

static INLINE void TONIGHT Array_free(pointer array){
	free(array - sizeof(int) - sizeof(size_t));
}

static string TONIGHT Array_toString(pointer array, P_retString method){
	static char ARRAY str = NULL;
	register int i, length = Array_length(array);
	if(str)
		Array.free(str);
	str = Array.Char(Array.size(array) * 3 * Array.length(array));
	*str = 0;
	strcat(str, "[");
	for(i=0;i<length;i++)
		strncat(strncat(str, getText(method(Array_access(array, i))), 1001), ", ", 1000 - strlen(str));
	str[strlen(str) - 2] = ']';
	return toString(str);
}

/* Tonight */
const TONIGHT struct Resources Tonight = {
	.Std ={
		.Console = {
			.Input = {
				__Scanner_nextChar,
				__Scanner_nextInt,
				__Scanner_nextFloat,
				__Scanner_nextDouble,
				__Scanner_next,
				__Scanner_nextLine,
				__Scanner_clear,
				__Scanner_ignore,
				__Scanner_ignoreChar
			},
			.Output = {
				__Screen_text,
				__Screen_textln,
				__Screen_print,
				__Screen_println,
				__Screen_printargln,
				__Screen_nl,
				__Screen_nls,
				__Screen_buffer,
				__Screen_clear
			}
		},
		.File = {
			.Input = {
				__Scanner_file_nextChar,
				__Scanner_file_nextInt,
				__Scanner_file_nextFloat,
				__Scanner_file_nextDouble,
				__Scanner_file_next,
				__Scanner_file_nextLine,
				__Scanner_file_clear,
				__Scanner_file_ignore,
				__Scanner_file_ignoreChar
			},
			.Output = {
				__Recorder_text,
				__Recorder_textln,
				__Recorder_print,
				__Recorder_println,
				__Recorder_printargln,
				__Recorder_nl,
				__Recorder_nls,
				__Recorder_buffer,
				__Recorder_clear
			}
		},
		.String = {
			.Input = {
				__Scanner_string_nextChar,
				__Scanner_string_nextInt,
				__Scanner_string_nextFloat,
				__Scanner_string_nextDouble,
				__Scanner_string_next,
				__Scanner_string_nextLine,
				__Scanner_string_clear,
				__Scanner_string_ignore,
				__Scanner_string_ignoreChar
			},
			.Output = {
				__String_text,
				__String_textln,
				__String_print,
				__String_println,
				__String_printargln,
				__Default_void_function,
				__Default_void_function,
				__Default_void_function,
				__Default_void_function
			}
		},
		.Object = {
			.Input = {
				__Scanner_object_nextChar,
				__Scanner_object_nextInt,
				__Scanner_object_nextFloat,
				__Scanner_object_nextDouble,
				__Scanner_object_next,
				__Scanner_object_nextLine,
				__Scanner_object_clear,
				__Scanner_object_ignore,
				__Scanner_object_ignoreChar
			},
			.Output = {
				__Object_text,
				__Object_textln,
				__Object_print,
				__Object_println,
				__Object_printargln,
				__Object_nl,
				__Object_nls,
				__Default_void_function,
				__Object_clear
			}
		},
		.Error = {
			__Error_text,
			__Error_textln,
			__Error_print,
			__Error_println,
			__Error_printargln,
			__Error_nl,
			__Error_nls,
			__Error_buffer,
			__Error_clear
		},
		.Random = {
			.Simple = {
				__Random_simple_nextChar,
				__Random_simple_nextInt,
				__Random_simple_nextFloat,
				__Random_simple_nextDouble
			},
			.Limit = {
				__Random_end_nextChar,
				__Random_end_nextInt,
				__Random_end_nextFloat,
				__Random_end_nextDouble
			},
			.Range = {
				__Random_begin_end_nextChar,
				__Random_begin_end_nextInt,
				__Random_begin_end_nextFloat,
				__Random_begin_end_nextDouble
			}
		},
		.Clock = {
			__Time_hours,
			__Time_minutes,
			__Time_seconds,
			__Time_month,
			__Time_day_month,
			__Time_day_week,
			__Time_day_year,
			__Time_year
		}
	},
	.Resources = {
		.Color = {
			__Colors_text,
			__Colors_background,
			__Colors_textbackground
		}
	},
	
	.Convert = {
		char_fromString,
		bool_fromString,
		int_fromString,
		float_fromString,
		double_fromString,
		s_cs,
		s_bs,
		s_is,
		s_fs,
		s_ds,
		String_formated
	},
	.DefaultFunctionPointer = __Default_void_function,
	
	.assert = __assert,
	.checkErrno = __checkErrno,
	.locale = __locale,
	.password = __Scanner_Password,
	.clearScreen = __clearScreen,
	.getKey = getKey,
	.getKeyEcho = getKeyEcho,
	.pressKey = pressKey,
	.sleep = __sleep,
	.position = cursor_position,
	.initRandom = __initRandom
};

/* New (new) */
const TONIGHT struct __New New = {
	__new_Scanner,
	__new_Writer,
	__new_Random,
	__new_Timer,
	__new_Painter,
	__new_Object,
	
	__new_char,
	__new_bool,
	__new_int,
	__new_float,
	__new_double,
	__new_String,
	__new_pointer
};

/* Array */
const struct __Array Array = {
	.length = Array_length,
	.size = Array_size,
	.access = Array_access,
	.free = Array_free,
	.toString = Array_toString,
	
	.Char = __new_array_char,
	.Bool = __new_array_bool,
	.Int = __new_array_int,
	.Float = __new_array_float,
	.Double = __new_array_double,
	.String = __new_array_String,
	.Object = __new_array_Object,
	.Pointer = __new_array_pointer,
	.Generic = __new_array_generic
};

/* Matrix */
const struct __Matrix Matrix = {
	.Char = __new_matrix_char,
	.Bool = __new_matrix_bool,
	.Int = __new_matrix_int,
	.Float = __new_matrix_float,
	.Double = __new_matrix_double,
	.String = __new_matrix_String,
	.Object = __new_matrix_Object,
	.Pointer = __new_matrix_pointer,
	.Generic = __new_matrix_generic
};

const struct __Memory Memory = {
	.alloc = __new_memory,
	.size = __memory_size,
	.copy = __memory_copy,
	.free = __memory_free
};

/* File */
const struct __File File = {
	.open = __new_File,
	.close = (pointer)fclose,
	.end = (pointer)feof,
	.Mode.read = "r",
	.Mode.write = "w"
};

/* Key */
const struct __Key Key = {
	.Right = key_right,
	.Left = key_left,
	.Up = key_up,
	.Down = key_down,
	.Escape = key_ESC,
	.Enter = key_ENTER,
	.Space = key_SPACE,
	.BackSpace = key_BS
};

/* Exit */
const struct __Exit Exit = {
	.Success = EXIT_SUCCESS,
	.Failure = EXIT_FAILURE,
	.Now = exit
};

int TONIGHT TonightMode(P_int func, int argc, string argv[]){
	register int i, ret;
	string ARRAY arg = Array.String(argc);
	for(i = 0; i < argc; i++)
		arg[i] = argv[i];
	TRY
		ret = func(arg);
	CATCH(GenericException)
		ret = EXIT_FAILURE;
	Array.free(arg);
	return ret;
}
