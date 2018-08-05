#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <setjmp.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include <errno.h>

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
static EXCEPTION_DEFINE ___FileOpenException = {"File open error", &GenericException};
static EXCEPTION_DEFINE ___InputException = {"Input error", &GenericException};
static EXCEPTION_DEFINE ___ConvertException = {"Convert error", &GenericException};
static EXCEPTION_DEFINE ___NotImplementException = {"Not implemented method error", &GenericException};

EXCEPTION TONIGHT AssertException = &___AssertException;
EXCEPTION TONIGHT ErrnoException = &___ErrnoException;
EXCEPTION TONIGHT MemoryAllocException = &___MemoryAllocException;
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

void TONIGHT THROW(EXCEPTION __exc, String message){
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

INLINE String TONIGHT Error(Exception exc){
	return exc->exception->error_name;
}

INLINE String TONIGHT Message(Exception exc){
	return exc->message;
}

INLINE EXCEPTION TONIGHT ExceptionType(Exception exc){
	return exc->exception;
}

/* Functions */
static bool TONIGHT pressKey(void){
	return kbhit() ? true : false;
}

static int TONIGHT getKey(void){
	DWORD mode;
	INPUT_RECORD inrec = {};
	DWORD count;
	int result;
	HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
	if(hstdin == INVALID_HANDLE_VALUE)
		return 0;
	do
		ReadConsoleInput(hstdin, &inrec, 1, &count);
	while(inrec.EventType != KEY_EVENT || !inrec.Event.KeyEvent.bKeyDown);
	if(inrec.Event.KeyEvent.uChar.AsciiChar)
		result = inrec.Event.KeyEvent.uChar.AsciiChar;
	else
		result = 256 + inrec.Event.KeyEvent.wVirtualKeyCode;
	return result;
}

static void __assert(bool test){
	if(!test)
		throw(AssertException, "Assert test failed");
}

static void __checkErrno(void){
	if(errno)
		throw(ErrnoException, strerror(errno));
}

static INLINE int TONIGHT getKeyEcho(void){
	putchar(c = getKey());
	return c;
}

INLINE void TONIGHT __sleep(unsigned int miliseconds){
	Sleep(miliseconds);
}

static INLINE double TONIGHT decimal(double n){
	return n - (long int)n;
}

INLINE void TONIGHT cursor_position(int x, int y){
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){x, y});
}

INLINE String TONIGHT __locale(void){
	return setlocale(LC_ALL, "");
}

INLINE void TONIGHT __clearScreen(void){
	system("cls");
}

INLINE static pointer __Default_void_function(){
	THROW(NotImplementException, "Function not implemented");
	return NULL;
}

INLINE static void __initRandom(void){
	srand((unsigned int)time(NULL));
}

INLINE String TONIGHT toString(register char ARRAY __array){
	return strcpy(new Memory((strlen(__array) + 1) * sizeof(char)), __array);
}

String TONIGHT concat(String wrd_1, ...){
	va_list va;
	static char s[1001];
	String p;
	*s = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, String))
		strcat(s, p);
	va_end(va);
	return toString(s);
}

retString TONIGHT retConcat(String wrd_1, ...){
	va_list va;
	String p;
	static retString ret;
	*ret.Text = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, String))
		strcat(ret.Text, p);
	va_end(va);
	return ret;
}

bool TONIGHT equal(register String const wrd_1, register String const wrd_2){
	register String s1 = wrd_1, s2 = wrd_2;
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

String TONIGHT s_cs(char var){
	register char *s = (char*)calloc(2, sizeof(char));
	*s = var;
	return (s);
}

String TONIGHT s_bs(bool var){
	return var ? toString("TRUE") : toString("FALSE");
}

String TONIGHT s_is(int var){
	static char s[15];
	sprintf(s, "%i", var);
	return toString(s);
}

String TONIGHT s_fsf(float var, int _decimal){
	static char s[100];
	sprintf(s, "%.*f", _decimal, var);
	return toString(s);
}

String TONIGHT s_dsf(double var, int _decimal){
	static char s[100];
	sprintf(s, "%.*lf", _decimal, var);
	return toString(s);
}

String TONIGHT s_ds(double var){
	double n;
	static char s[100];
	sprintf(s, "%.10g", var);
	return toString(s);
}

INLINE String TONIGHT s_fs(float var){
	return s_ds((double)var);
}

retString TONIGHT cs(char var){
	register char *s = s_cs(var);
	static retString ret;
	strcpy(ret.Text, s);
	free(s);
	return ret;
}

retString TONIGHT bs(bool var){
	register char *s = s_bs(var);
	static retString ret;
	strcpy(ret.Text, s);
	free(s);
	return ret;
}

retString TONIGHT is(int var){
	register char *s = s_is(var);
	static retString ret;
	strcpy(ret.Text, s);
	free(s);
	return ret;
}

retString TONIGHT fsf(float var, int _decimal){
	register char *s = s_fsf(var, _decimal);
	static retString ret;
	strcpy(ret.Text, s);
	free(s);
	return ret;
}

retString TONIGHT dsf(double var, int _decimal){
	register char *s = s_dsf(var, _decimal);
	static retString ret;
	strcpy(ret.Text, s);
	free(s);
	return ret;
}

retString TONIGHT ds(double var){
	register char *s = s_ds(var);
	static retString ret;
	strcpy(ret.Text, s);
	free(s);
	return ret;
}

INLINE retString TONIGHT fs(float var){
	return ds((double)var);
}

/* Functions to Tonight.std.Console.input */
static char TONIGHT throws __Scanner_nextChar(void){
	if(scanf("%c", &c) != 1)
		throw(InputException, "Impossible to read a \"char\" from the standard input");
	return c;
}

static int TONIGHT throws __Scanner_nextInt(void){
	if(scanf("%i", &i) != 1)
		throw(InputException, "Impossible to read an \"int\" from the standard input");
	return i;
}

static float TONIGHT throws __Scanner_nextFloat(void){
	if(scanf("%f", &f) != 1)
		throw(InputException, "Impossible to read a \"float\" from the standard input");
	return f;
}

static double TONIGHT throws __Scanner_nextDouble(void){
	if(scanf("%lf", &d) != 1)
		throw(InputException, "Impossible to read a \"double\" from the standard input");
	return d;
}

static String TONIGHT throws __Scanner_next(void){
	if(scanf("%1000s", str) != 1)
		throw(InputException, "Impossible to read a \"String\" from the standard input");
	return toString(str);
}

static String TONIGHT throws __Scanner_nextLine(void){
	if(scanf(" %1000[^\n]s", str) != 1)
		throw(InputException, "Impossible to read a \"String\" from the standard input");
	return toString(str);
}

static String TONIGHT __Scanner_Password(int nchar){
	int i = 0;
	char* senha = new array.Char(nchar + 1);
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
static char TONIGHT throws __Scanner_file_nextChar(File _file){
	if(fscanf(_file, "%c", &c) != 1)
		throw(InputException, "Impossible to read a \"char\" from the file");
	return c;
}

static int TONIGHT throws __Scanner_file_nextInt(File _file){
	if(fscanf(_file, "%i", &i) != 1)
		throw(InputException, "Impossible to read an \"int\" from the file");
	return i;
}

static float TONIGHT throws __Scanner_file_nextFloat(File _file){
	if(fscanf(_file, "%f", &f) != 1)
		throw(InputException, "Impossible to read a \"float\" from the file");
	return f;
}

static double TONIGHT throws __Scanner_file_nextDouble(File _file){
	if(fscanf(_file, "%lf", &d) != 1)
		throw(InputException, "Impossible to read a \"double\" from the file");
	return d;
}

static String TONIGHT throws __Scanner_file_next(File _file){
	if(fscanf(_file, "%1000s", str) != 1)
		throw(InputException, "Impossible to read a \"String\" from the file");
	return toString(str);
}

static String TONIGHT throws __Scanner_file_nextLine(File _file){
	if(fscanf(_file, " %1000[^\n]s", str) != 1)
		throw(InputException, "Impossible to read a \"String\" from the file");
	return toString(str);
}

static INLINE void TONIGHT __Scanner_file_clear(File _file){
	while(!feof(_file))
		if(fgetc(_file) == '\n')
			return;
}

static INLINE void TONIGHT __Scanner_file_ignore(File _file){
	fscanf(_file, "%*s");
}

static INLINE void TONIGHT __Scanner_file_ignoreChar(File _file){
	fscanf(_file, "%*c");
}

/* Functions to Tonight.std.string.input */
static char TONIGHT throws __Scanner_string_nextChar(String str){
	if(sscanf(str, "%c", &c) != 1)
		throw(InputException, "Impossible to read a \"char\" from the String");
	return c;
}

static int TONIGHT throws __Scanner_string_nextInt(String str){
	if(sscanf(str, "%i", &i) != 1)
		throw(InputException, "Impossible to read an \"int\" from the String");
	return i;
}

static float TONIGHT throws __Scanner_string_nextFloat(String str){
	if(sscanf(str, "%f", &f) != 1)
		throw(InputException, "Impossible to read a \"float\" from the String");
	return f;
}

static double TONIGHT throws __Scanner_string_nextDouble(String str){
	if(sscanf(str, "%lf", &d) != 1)
		throw(InputException, "Impossible to read a \"double\" from the String");
	return d;
}

static String TONIGHT throws __Scanner_string_next(String s){
	if(sscanf(s, "%1000s", str) != 1)
		throw(InputException, "Impossible to read a \"String\" from the String");
	return toString(s);
}

static String TONIGHT throws __Scanner_string_nextLine(String s){
	if(sscanf(s, " %1000[^\n]s", str) != 1)
		throw(InputException, "Impossible to read a \"String\" from the String");
	return toString(s);
}

static void TONIGHT __Scanner_string_clear(String str){
	while(*str != '\n')
		++ str;
}

static void TONIGHT __Scanner_string_ignore(String str){
	sscanf(str, "%*s");
}

static void TONIGHT __Scanner_string_ignoreChar(String str){
	sscanf(str, "%*c");
}

/* Functions to Tonight.std.object.input */
static char TONIGHT throws __Scanner_object_nextChar(IScanner iScan, Object obj){
	String s = iScan.getString(obj);
	char c = __Scanner_string_nextChar(s);
	free(s);
	return c;
}

static int TONIGHT throws __Scanner_object_nextInt(IScanner iScan, Object obj){
	String s = iScan.getString(obj);
	int i = __Scanner_string_nextInt(s);
	free(s);
	return i;
}

static float TONIGHT throws __Scanner_object_nextFloat(IScanner iScan, Object obj){
	String s = iScan.getString(obj);
	float f = __Scanner_string_nextFloat(s);
	free(s);
	return f;
}

static double TONIGHT throws __Scanner_object_nextDouble(IScanner iScan, Object obj){
	String s = iScan.getString(obj);
	double d = __Scanner_string_nextDouble(s);
	free(s);
	return d;
}

static String TONIGHT throws __Scanner_object_next(IScanner iScan, Object obj){
	String s = iScan.getString(obj);
	String str = __Scanner_string_next(s);
	free(s);
	return str;
}

static INLINE String TONIGHT __Scanner_object_nextLine(IScanner iScan, Object obj){
	return iScan.getString(obj);
}

static INLINE void TONIGHT  __Scanner_object_clear(IScanner iScan, Object obj){
	iScan.setString(obj, "");
}

static INLINE void TONIGHT __Scanner_object_ignore(IScanner iScan, Object obj){
	String s = iScan.getString(obj);
	free(s);
}

static INLINE void TONIGHT __Scanner_object_ignoreChar(IScanner iScan, Object obj){
	String s = iScan.getString(obj);
	iScan.setString(obj, ++s);
	free(s);
}

/* Functions to Tonight.std.Console.output */
static void TONIGHT __Recorder_text(File, String);
static INLINE void TONIGHT __Recorder_textln(File, String);

static INLINE void TONIGHT __Screen_text(String txt){
	__Recorder_text(stdout, txt);
}

static INLINE void TONIGHT __Screen_textln(String txt){
	__Recorder_textln(stdout, txt);
}

static void TONIGHT __Screen_print(String txt, ...){
	va_list t;
	register String s;
	va_start(t, txt);
	for(s = txt; s; s = va_arg(t, String))
		__Screen_text(s);
	va_end(t);
}

static void TONIGHT __Screen_println(String txt, ...){
	va_list t;
	register String s;
	va_start(t, txt);
	for(s = txt; s; s = va_arg(t, String))
		printf("%s", s);
	va_end(t);
	putchar('\n');
}

static void TONIGHT __Screen_printargln(String txt, ...){
	va_list t;
	register String s;
	va_start(t, txt);
	for(s = txt; s; s = va_arg(t, String))
		puts(s);
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

/* Functions to Tonight.std.file.output */
static void TONIGHT __Recorder_text(File _file, String txt){
	fprintf(_file, "%s", txt);
}

static INLINE void TONIGHT __Recorder_textln(File _file, String txt){
	fprintf(_file, "%s\n", txt);
}

static void TONIGHT __Recorder_print(File _file, String txt, ...){
	va_list t;
	String s;
	va_start(t, txt);
	for(s = txt; s; s = va_arg(t, String))
		fprintf(_file, "%s", s);
	va_end(t);
}

static void TONIGHT __Recorder_println(File _file, String txt, ...){
	va_list t;
	String s;
	va_start(t, txt);
	for(s = txt; s; s = va_arg(t, String))
		fprintf(_file, "%s", s);
	va_end(t);
	putc('\n', _file);
}

static void TONIGHT __Recorder_printargln(File _file, String txt, ...){
	va_list t;
	String s;
	va_start(t, txt);
	for(s = txt; s; s = va_arg(t, String))
		fprintf(_file, "%s\n", s);
	va_end(t);
}

static INLINE void TONIGHT __Recorder_nl(File __file){
	fputc('\n', __file);
}

static INLINE void TONIGHT __Recorder_nls(File __file, int qtd){
	while(qtd--)
		fputc('\n', __file);
}

static void TONIGHT __Recorder_buffer(File __file){
	setbuf(__file, __buffer);
}

static void TONIGHT throws __Recorder_clear(File __file){
	if(!fflush(__file))
		throw(GenericException, strerror(errno));
}

/* Functions to Tonight.std.error */
static void TONIGHT __Error_text(String txt){
	fprintf(stderr, "%s", txt);
}

static INLINE void TONIGHT __Error_textln(String txt){
	fprintf(stderr, "%s\n", txt);
}

static void TONIGHT __Error_print(String txt, ...){
	va_list t;
	String s;
	va_start(t, txt);
	for(s = txt; s; s = va_arg(t, String))
		fprintf(stderr, "%s", s);
	va_end(t);
}

static void TONIGHT __Error_println(String txt, ...){
	va_list t;
	String s;
	va_start(t, txt);
	for(s = txt; s; s = va_arg(t, String))
		fprintf(stderr, "%s", s);
	va_end(t);
	putc('\n', stderr);
}

static void TONIGHT __Error_printargln(String txt, ...){
	va_list t;
	String s;
	va_start(t, txt);
	for(s = txt; s; s = va_arg(t, String))
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

static void TONIGHT throws __Error_clear(void){
	if(!fflush(stderr))
		throw(GenericException, strerror(errno));
}

/* Functions to Tonight.std.string.output */
static void TONIGHT __String_text(char *str, String txt){
	sprintf(str, "%s", txt);
}

static void TONIGHT __String_textln(char *str, String txt){
	sprintf(str, "%s\n", txt);
}

static void TONIGHT __String_print(char *str, String txt, ...){
	String s;
	va_list v;
	va_start(v, txt);
	for(s = txt; s; s = va_arg(v, String))
		strcat(str, s);
	va_end(v);
}

static void TONIGHT __String_println(char *str, String txt, ...){
	__String_print(str, txt);
	sprintf(str, "%s\n", str);
}

static void TONIGHT __String_printargln(char *str, String txt, ...){
	String s;
	va_list v;
	va_start(v, txt);
	for(s = txt; s; s = va_arg(v, String))
		strcat(str, s);
	va_end(v);
}

/* Functions to Tonight.std.object.output */
static INLINE void TONIGHT __Object_text(IWriter iWrt, Object obj, String txt){
	iWrt.addText(obj, txt);
}

static INLINE void TONIGHT __Object_textln(IWriter iWrt, Object obj, String txt){
	String s = concat(txt, "\n", end);
	iWrt.addText(obj, s);
	free(s);
}

static void TONIGHT __Object_print(IWriter iWrt, Object obj, String txt, ...){
	String a;
	va_list v;
	static char s[1000];
	*s = 0;
	va_start(v, txt);
	for(a = txt; a; a = va_arg(v, String))
		strcat(s, a);
	va_end(v);
	iWrt.addText(obj, &s[0]);
}

static void TONIGHT __Object_println(IWriter iWrt, Object obj, String txt, ...){
	String a;
	va_list v;
	static char s[1000];
	*s = 0;
	va_start(v, txt);
	for(a = txt; a; a = va_arg(v, String))
		strcat(s, a);
	va_end(v);
	strcat(s, "\n");
	iWrt.addText(obj, &s[0]);
}

static void TONIGHT __Object_printargln(IWriter iWrt, Object obj, String txt, ...){
	String a;
	va_list v;
	va_start(v, txt);
	for(a = txt; a; a = va_arg(v, String))
		__Object_println(iWrt, obj, a);
	va_end(v);
}

static void TONIGHT __Object_nl(IWriter iWrt, Object obj){
	iWrt.addText(obj, "\n");
}

static void TONIGHT __Object_nls(IWriter iWrt, Object obj, int qtd){
	while(qtd--)
		iWrt.addText(obj, "\n");
}

static void TONIGHT __Object_clear(IWriter iWrt, Object obj){
	iWrt.clear(obj);
}

/* Functions to Tonight.resources.Box */
static INLINE void __MessageBox_text(String title, String text){
	MessageBox(NULL, text, title, MB_OK);
}

static void __MessageBox_print(String title, String text, ...){
	va_list va;
	static char s[1000];
	register char *p;
	sprintf(s, "\0");
	va_start(va, text);
	for(p = text; p; p = va_arg(va, char*))
		strcat(s, p);
	va_end(va);
	MessageBox(NULL, s, title, MB_OK);
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

static File TONIGHT throws __new_File(String fName, String fMode){
	File f = fopen(fName, fMode);
	if(!f)
		throw(FileOpenException, concat("Impossible to open the file \"", fName, "\"", end));
	return f;
}

static Object TONIGHT __new_Object(Class_Name name, ...){
	va_list v;
	Object _new = new Memory(sizeof(Intern_Object));
	va_start(v, name);
	_new->obj = new Memory(name->size);
	_new->class_pointer = name;
	name->ctor(_new, &v);
	va_end(v);
	return _new;
}

void TONIGHT delete(Object self){
	if(!self)
		return;
	if(self->class_pointer->dtor)
		self->class_pointer->dtor(self);
	free(self);
}

/* Alloc pointers */
static char* TONIGHT throws __new_char(char value){
	char* c = malloc(sizeof(char));
	if(c)
		*c = value;
	else
		throw(MemoryAllocException, "Impossible allocate memory to char");
	return c;
}

static bool* TONIGHT throws __new_bool(bool value){
	bool *b = malloc(sizeof(bool));
	if(b)
		*b = value;
	else
		throw(MemoryAllocException, "Impossible allocate memory to bool");
	return b;
}

static int* TONIGHT throws __new_int(int value){
	int *i = malloc(sizeof(int));
	if(i)
		*i = value;
	else
		throw(MemoryAllocException, "Impossible allocate memory to int");
	return i;
}

static float* TONIGHT throws __new_float(float value){
	float *f = malloc(sizeof(float));
	if(f)
		*f = value;
	else
		throw(MemoryAllocException, "Impossible allocate memory to float");
	return f;
}

static double* TONIGHT throws __new_double(double value){
	double *d = malloc(sizeof(double));
	if(d)
		*d = value;
	else
		throw(MemoryAllocException, "Impossible allocate memory to double");
	return d;
}

static String* TONIGHT throws __new_String(String value){
	String *s = malloc(sizeof(String));
	if(s)
		*s = value;
	else
		throw(MemoryAllocException, "Impossible allocate memory to String");
	return s;
}

static pointer TONIGHT throws __new_pointer(pointer value){
	pointer *p = malloc(sizeof(pointer));
	if(p)
		*p = value;
	else
		throw(MemoryAllocException, "Impossible allocate memory to pointer");
	return p;
}

static pointer TONIGHT throws __new_memory(size_t q){
	pointer *p = malloc(q);
	if(!p)
		throw(MemoryAllocException, "Impossible allocate memory");
	return p;
}

/* Initialize arrays */
static char* TONIGHT throws __new_array_char(int q){
	char* c = malloc(q * sizeof(char));
	if(!c)
		throw(MemoryAllocException, "Impossible allocate memory to char array");
	return c;
}

static bool* TONIGHT throws __new_array_bool(int q){
	bool* b = malloc(q * sizeof(bool));
	if(!b)
		throw(MemoryAllocException, "Impossible allocate memory to bool array");
	return b;
}

static int* TONIGHT throws __new_array_int(int q){
	int* i = malloc(q * sizeof(int));
	if(!i)
		throw(MemoryAllocException, "Impossible allocate memory to int array");
	return i;
}

static float* TONIGHT throws __new_array_float(int q){
	float* f = malloc(q * sizeof(float));
	if(!f)
		throw(MemoryAllocException, "Impossible allocate memory to float array");
	return f;
}

static double* TONIGHT throws __new_array_double(int q){
	double* d = malloc(q * sizeof(double));
	if(!d)
		throw(MemoryAllocException, "Impossible allocate memory to double array");
	return d;
}

static String* TONIGHT throws __new_array_String(int q){
	String* s = malloc(q * sizeof(String));
	if(!s)
		throw(MemoryAllocException, "Impossible allocate memory to String array");
	return s;
}

static Object* TONIGHT throws __new_array_Object(int q){
	Object* o = malloc(q * sizeof(Object));
	if(!o)
		throw(MemoryAllocException, "Impossible allocate memory to Object array");
	return o;
}

static pointer* TONIGHT throws __new_array_pointer(int q){
	pointer *p = malloc(q * sizeof(pointer));
	if(!p)
		throw(MemoryAllocException, "Impossible allocate memory to pointer array");
	return p;
}

/* Initialize matrixes */
static char** TONIGHT throws __new_matrix_char(int l, int c){
	char** m = malloc(l * sizeof(char*));
	register int i;
	if(!m)
		throw(MemoryAllocException, "Impossible allocate memory to char matrix");
	for(i = 0; i < l; i++)
		m[i] = __new_array_char(c);
	return m;
}

static bool** TONIGHT throws __new_matrix_bool(int l, int c){
	bool** m = malloc(l * sizeof(bool*));
	register int i;
	if(!m)
		throw(MemoryAllocException, "Impossible allocate memory to bool matrix");
	for(i = 0; i < l; i++)
		m[i] = __new_array_bool(c);
	return m;
}

static int** TONIGHT throws __new_matrix_int(int l, int c){
	int** m = malloc(l * sizeof(int*));
	register int i;
	if(!m)
		throw(MemoryAllocException, "Impossible allocate memory to int matrix");
	for(i = 0; i < l; i++)
		m[i] = __new_array_int(c);
	return m;
}

static float** TONIGHT throws __new_matrix_float(int l, int c){
	float** m = malloc(l * sizeof(float*));
	register int i;
	if(!m)
		throw(MemoryAllocException, "Impossible allocate memory to float matrix");
	for(i = 0; i < l; i++)
		m[i] = __new_array_float(c);
	return m;
}

static double** TONIGHT throws __new_matrix_double(int l, int c){
	double** m = malloc(l * sizeof(double*));
	register int i;
	if(!m)
		throw(MemoryAllocException, "Impossible allocate memory to double matrix");
	for(i = 0; i < l; i++)
		m[i] = __new_array_double(c);
	return m;
}

static String** TONIGHT throws __new_matrix_String(int l, int c){
	String** m = malloc(l * sizeof(String*));
	register int i;
	if(!m)
		throw(MemoryAllocException, "Impossible allocate memory to String matrix");
	for(i = 0; i < l; i++)
		m[i] = __new_array_String(c);
	return m;
}

static Object** TONIGHT throws __new_matrix_Object(int l, int c){
	Object** m = malloc(l * sizeof(Object*));
	register int i;
	if(!m)
		throw(MemoryAllocException, "Impossible allocate memory to String matrix");
	for(i = 0; i < l; i++)
		m[i] = __new_array_Object(c);
	return m;
}

static pointer** TONIGHT throws __new_matrix_pointer(int l, int c){
	pointer** m = malloc(l * sizeof(pointer*));
	register int i;
	if(!m)
		throw(MemoryAllocException, "Impossible allocate memory to pointer matrix");
	for(i = 0; i < l; i++)
		m[i] = __new_array_pointer(c);
	return m;
}

/* Functions to Convert */
static char TONIGHT char_fromString(String s){
	char ret = *s;
	if(* ++ s)
		throw(ConvertException, "Impossible to convert the string to a char");
	return ret;
}

static bool TONIGHT throws bool_fromString(String s){
	if(equal(s, "true"))
		return true;
	if(equal(s, "false"))
		return false;
	throw(ConvertException, "Impossible to convert the string to a bool");
	return false;
}

static int TONIGHT throws int_fromString(String s){
	int i;
	String a;
	i = (int)strtol(s, &a, 0);
	if(*a)
		throw(ConvertException, "Impossible to convert the string to integer");
	return i;
}

static float TONIGHT throws float_fromString(String s){
	float f;
	String a;
	f = strtof(s, &a);
	if(*a)
		throw(ConvertException, "Impossible to convert the string to float");
	return f;
}

static double TONIGHT throws double_fromString(String s){
	double d;
	String a;
	d = strtod(s, &a);
	if(*a)
		throw(ConvertException, "Impossible to convert the string to double");
	return d;
}

static String TONIGHT String_formated(const String frmt, ...){
	char s[1001];
	va_list v;
	va_start(v, frmt);
	vsprintf(s, frmt, v);
	va_end(v);
	return toString(s);
}

/* Tonight */
const TONIGHT struct Resources Tonight = {
	.std ={
		.console = {
			.input = {
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
			.output = {
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
		.file = {
			.input = {
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
			.output = {
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
		.string = {
			.input = {
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
			.output = {
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
		.object = {
			.input = {
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
			.output = {
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
		.error = {
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
		.random = {
			.simple = {
				__Random_simple_nextChar,
				__Random_simple_nextInt,
				__Random_simple_nextFloat,
				__Random_simple_nextDouble
			},
			.limit = {
				__Random_end_nextChar,
				__Random_end_nextInt,
				__Random_end_nextFloat,
				__Random_end_nextDouble
			},
			.range = {
				__Random_begin_end_nextChar,
				__Random_begin_end_nextInt,
				__Random_begin_end_nextFloat,
				__Random_begin_end_nextDouble
			}
		},
		.clock = {
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
	.resources = {
		.Color = {
			__Colors_text,
			__Colors_background,
			__Colors_textbackground
		},
		.Box = {
			__MessageBox_text,
			__MessageBox_text,
			__MessageBox_print,
			__MessageBox_print,
			__MessageBox_print,
			__Default_void_function,
			__Default_void_function,
			__Default_void_function
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
	__new_File,
	__new_Object,
	
	__new_char,
	__new_bool,
	__new_int,
	__new_float,
	__new_double,
	__new_String,
	__new_pointer,
	__new_memory,
	
	{
		__new_array_char,
		__new_array_bool,
		__new_array_int,
		__new_array_float,
		__new_array_double,
		__new_array_String,
		__new_array_Object,
		__new_array_pointer
	},
	{
		__new_matrix_char,
		__new_matrix_bool,
		__new_matrix_int,
		__new_matrix_float,
		__new_matrix_double,
		__new_matrix_String,
		__new_matrix_Object,
		__new_matrix_pointer
	}
};
