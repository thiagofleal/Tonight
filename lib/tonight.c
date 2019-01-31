#include "tonight.proto.h"
#include "tonight.objects.h"

#undef main

static char c;
static int i;
static float f;
static double d;
static char str[1001];
static wchar_t wstr[1001];

static int text_color = 7, background_color = 0;

static P_pointer p_malloc = malloc;
static P_pointer p_calloc = calloc;
static P_pointer p_realloc = realloc;
static P_void p_free = free;

#include "tonight.sys.h"

typedef struct{
	size_t size;
	ICollection *collection;
	char data[0];
}MemoryData;

typedef struct{
	int length;
	size_t size;
	ICollection *collection;
	char data[0];
}ArrayData;

/* Functions */

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

static INLINE double TONIGHT decimal(double n){
	return n - (long int)n;
}

static pointer buf_locale = NULL;

static int __category = LC_ALL;
static string __name = "C";

static INLINE string TONIGHT __locale(void){
	return setlocale(__category, __name);
}

static INLINE string __getlocale(int category){
	return setlocale(category, NULL);
}

static INLINE int TONIGHT __getCategory(void){
	return __category;
}

static INLINE void TONIGHT __setCategory(int category){
	__category = category;
}

static INLINE string TONIGHT __getName(void){
	return __name;
}

static INLINE void TONIGHT __setName(string name){
	__name = name;
}

INLINE static pointer __Default_void_function(){
	Throw(NotImplementException, "Function not implemented");
	return NULL;
}

INLINE static void __initRandom(void){
	srand((unsigned int)time(NULL));
}

static INLINE void TONIGHT __enableASCII(file src){
	#ifdef _WIN32
		_setmode(fileno((FILE*)src), _O_TEXT);
	#endif
}

static INLINE void TONIGHT __enableUTF8(file src){
	#ifdef _WIN32
		_setmode(fileno((FILE*)src), _O_U8TEXT);
	#endif
}

static INLINE string TONIGHT __concatString(char dest[], char from[], int length){
	return strncat(dest, from, length - strlen(dest) - 1);
}

static INLINE pstring TONIGHT __wconcatString(wchar_t dest[], wchar_t from[], int length){
	return wcsncat(dest, from, length - wcslen(dest) - 1);
}

static INLINE pstring TONIGHT __concatWString(wchar_t dest[], wchar_t from[], int length){
	return wcsncat(dest, from, length - wcslen(dest) - 1);
}

static INLINE pstring TONIGHT stringToWide(pstring s){
	swprintf(wstr, strlen(s) + 1, L"%hs", s);
	return toWide(wstr);
}

static INLINE pstring TONIGHT wideToString(pstring s){
	sprintf(str, "%ls", (wchar_t*)s);
	return toString(str);
}

INLINE string TONIGHT toString(register pointer __array){
	register unsigned int size = (strlen(__array) + 1) * sizeof(char);
	return memcpy(__new_memory(size), __array, size);
}

INLINE pstring TONIGHT toWide(register pointer __array){
	register unsigned int size = (wcslen(__array) + 1) * sizeof(wchar_t);
	return memcpy(__new_memory(size), __array, size);
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
	char ARRAY s = NULL;
	static string p;
	s = __new_array_char(size + 1);
	*s = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, string))
		strcat(s, p);
	va_end(va);
	p = toString(s);
	Array_free(s);
	return p;
}

pstring TONIGHT wconcat(pstring wrd_1, ...){
	va_list va;
	static wchar_t s[1001];
	static pstring p;
	*s = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, pstring))
		__wconcatString(s, p, sizeof s);
	va_end(va);
	return toWide(s);
}

pstring TONIGHT nwconcat(int size, pstring wrd_1, ...){
	va_list va;
	wchar_t ARRAY s = NULL;
	static pstring p;
	s = __new_array_generic(sizeof(wchar_t), size + 1);
	*s = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, string))
		wcscat(s, p);
	va_end(va);
	p = toWide(s);
	Array_free(s);
	return p;
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

retWideString TONIGHT wretConcat(pstring wrd_1, ...){
	va_list va;
	pstring p;
	static retWideString ret;
	*ret.Text = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, pstring))
		__concatWString(ret.Text, p, sizeof ret);
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
	return *s1 == *s2 ? true : false;
}

string TONIGHT s_cs(char var){
	char c[] = {var, 0};
	return toString(c);
}

string TONIGHT s_bs(bool var){
	return var ? toString("true") : toString("false");
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

INLINE string TONIGHT s_cps(char *p){
	return s_cs(*p);
}

INLINE string TONIGHT s_bps(bool *p){
	return s_bs(*p);
}

INLINE string TONIGHT s_ips(int *p){
	return s_is(*p);
}

INLINE string TONIGHT s_fps(float *p){
	return s_fs(*p);
}

INLINE string TONIGHT s_dps(double *p){
	return s_ds(*p);
}

INLINE string TONIGHT s_fpsf(float *p, int d){
	return s_fsf(*p, d);
}

INLINE string TONIGHT s_dpsf(double *p, int d){
	return s_dsf(*p, d);
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

longRetString TONIGHT longRetConcat(string wrd_1, ...){
	va_list va;
	string p;
	static longRetString ret;
	*ret.Text = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, string))
		__concatString(ret.Text, p, sizeof ret);
	va_end(va);
	return ret;
}

INLINE retString TONIGHT cps(char *p){
	return cs(*p);
}

INLINE retString TONIGHT bps(bool *p){
	return bs(*p);
}

INLINE retString TONIGHT ips(int *p){
	return is(*p);
}

INLINE retString TONIGHT fps(float *p){
	return fs(*p);
}

INLINE retString TONIGHT dps(double *p){
	return ds(*p);
}

INLINE retString TONIGHT fpsf(float *p, int d){
	return fsf(*p, d);
}

INLINE retString TONIGHT dpsf(double *p, int d){
	return dsf(*p, d);
}

longRetString TONIGHT cls(char var){
	register char *s = s_cs(var);
	static longRetString ret;
	strncpy(ret.Text, s, sizeof ret);
	p_free(s);
	return ret;
}

longRetString TONIGHT bls(bool var){
	register char *s = s_bs(var);
	static longRetString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

longRetString TONIGHT ils(int var){
	register char *s = s_is(var);
	static longRetString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

longRetString TONIGHT fls(float var){
	register char *s = s_fs(var);
	static longRetString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

longRetString TONIGHT dls(double var){
	register char *s = s_ds(var);
	static longRetString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

longRetString TONIGHT flsf(float var, int d){
	register char *s = s_fsf(var, d);
	static longRetString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

longRetString TONIGHT dlsf(double var, int d){
	register char *s = s_dsf(var, d);
	static longRetString ret;
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

longRetString TONIGHT longFormated(const string format, ...){
	va_list v;
	longRetString ret;
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
	char* senha = Memory.alloc(sizeof(char) * (nchar + 1));
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
	if(fscanf((FILE*)_file, "%c", &c) != 1)
		throw(InputException, "Impossible to read a \"char\" from the file");
	return c;
}

static int TONIGHT $throws __Scanner_file_nextInt(file _file){
	if(fscanf((FILE*)_file, "%i", &i) != 1)
		throw(InputException, "Impossible to read an \"int\" from the file");
	return i;
}

static float TONIGHT $throws __Scanner_file_nextFloat(file _file){
	if(fscanf((FILE*)_file, "%f", &f) != 1)
		throw(InputException, "Impossible to read a \"float\" from the file");
	return f;
}

static double TONIGHT $throws __Scanner_file_nextDouble(file _file){
	if(fscanf((FILE*)_file, "%lf", &d) != 1)
		throw(InputException, "Impossible to read a \"double\" from the file");
	return d;
}

static string TONIGHT $throws __Scanner_file_next(file _file){
	if(fscanf((FILE*)_file, "%1000s", str) != 1)
		throw(InputException, "Impossible to read a \"string\" from the file");
	return toString(str);
}

static string TONIGHT $throws __Scanner_file_nextLine(file _file){
	if(fscanf((FILE*)_file, " %1000[^\n]s", str) != 1)
		throw(InputException, "Impossible to read a \"string\" from the file");
	return toString(str);
}

static INLINE void TONIGHT __Scanner_file_clear(file _file){
	while(!feof((FILE*)_file))
		if(fgetc((FILE*)_file) == '\n')
			return;
}

static INLINE void TONIGHT __Scanner_file_ignore(file _file){
	fscanf((FILE*)_file, "%*s");
}

static INLINE void TONIGHT __Scanner_file_ignoreChar(file _file){
	fscanf((FILE*)_file, "%*c");
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
	return toString(str);
}

static string TONIGHT $throws __Scanner_string_nextLine(string s){
	if(sscanf(s, " %1000[^\n]s", str) != 1)
		throw(InputException, "Impossible to read a \"string\" from the string");
	return toString(str);
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
	Memory.free(s);
	return c;
}

static int TONIGHT $throws __Scanner_object_nextInt(IScanner iScan, object obj){
	string s = iScan.getString(obj);
	int i = __Scanner_string_nextInt(s);
	Memory.free(s);
	return i;
}

static float TONIGHT $throws __Scanner_object_nextFloat(IScanner iScan, object obj){
	string s = iScan.getString(obj);
	float f = __Scanner_string_nextFloat(s);
	Memory.free(s);
	return f;
}

static double TONIGHT $throws __Scanner_object_nextDouble(IScanner iScan, object obj){
	string s = iScan.getString(obj);
	double d = __Scanner_string_nextDouble(s);
	Memory.free(s);
	return d;
}

static string TONIGHT $throws __Scanner_object_next(IScanner iScan, object obj){
	string s = iScan.getString(obj);
	string str = __Scanner_string_next(s);
	Memory.free(s);
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
	Memory.free(s);
}

static INLINE void TONIGHT __Scanner_object_ignoreChar(IScanner iScan, object obj){
	string s = iScan.getString(obj);
	iScan.setString(obj, ++s);
	Memory.free(s);
}

static INLINE char TONIGHT __Scanner_Error_nextChar(void){
	return (char)errno;
}

static INLINE int TONIGHT __Scanner_Error_nextInt(void){
	return errno;
}

static INLINE float TONIGHT __Scanner_Error_nextFloat(void){
	return (float)errno;
}

static double TONIGHT __Scanner_Error_nextDouble(void){
	return (double)errno;
}

static string TONIGHT $throws __Scanner_Error_next(void){
	return __Scanner_string_next(strerror(errno));
}

static INLINE string TONIGHT $throws __Scanner_Error_nextLine(void){
	return __Scanner_string_nextLine(strerror(errno));
}

/* Functions to Tonight.std.Console.output */
static INLINE void TONIGHT __Screen_text(string txt){
	__Recorder_text((file)stdout, txt);
}

static INLINE void TONIGHT __Screen_textln(string txt){
	__Recorder_textln((file)stdout, txt);
}

static void TONIGHT __Screen_print(string txt, ...){
	va_list t;
	va_start(t, txt);
	__print_args((file)stdout, txt, t);
	va_end(t);
}

static void TONIGHT __Screen_println(string txt, ...){
	va_list t;
	va_start(t, txt);
	__println_args((file)stdout, txt, t);
	va_end(t);
}

static void TONIGHT __Screen_printargln(string txt, ...){
	va_list t;
	va_start(t, txt);
	__printargln_args((file)stdout, txt, t);
	va_end(t);
}

static void TONIGHT __Screen_nl(void){
	putchar('\n');
}

static void TONIGHT __Screen_nls(int qtd){
	while(qtd--)
		putchar('\n');
}

static void TONIGHT __Screen_clear(void){
	if(!fflush(stdout))
		throw(GenericException, strerror(errno));
}

/* Output base functions */
static NORMAL void TONIGHT __print_args(file _file, string first, va_list args){
	string s;
	for(s = first; s; s = va_arg(args, string))
		__Recorder_text(_file, s);
}

static NORMAL void TONIGHT __println_args(file _file, string first, va_list args){
	string s;
	for(s = first; s; s = va_arg(args, string))
		__Recorder_text(_file, s);
	__Recorder_text(_file, "\n");
}

static NORMAL void TONIGHT __printargln_args(file _file, string first, va_list args){
	string s;
	for(s = first; s; s = va_arg(args, string))
		__Recorder_textln(_file, s);
}

/* Functions to Tonight.std.file.output */
static INLINE void TONIGHT __Recorder_text(file _file, string txt){
	fprintf((FILE*)_file, "%s", txt);
}

static INLINE void TONIGHT __Recorder_textln(file _file, string txt){
	fprintf((FILE*)_file, "%s\n", txt);
}

static void TONIGHT __Recorder_print(file _file, string txt, ...){
	va_list t;
	va_start(t, txt);
	__print_args(_file, txt, t);
	va_end(t);
}

static void TONIGHT __Recorder_println(file _file, string txt, ...){
	va_list t;
	va_start(t, txt);
	__println_args(_file, txt, t);
	va_end(t);
}

static void TONIGHT __Recorder_printargln(file _file, string txt, ...){
	va_list t;
	va_start(t, txt);
	__printargln_args(_file, txt, t);
	va_end(t);
}

static INLINE void TONIGHT __Recorder_nl(file __file){
	fputc('\n', (FILE*)__file);
}

static INLINE void TONIGHT __Recorder_nls(file __file, int qtd){
	while(qtd--)
		fputc('\n', (FILE*)__file);
}

static void TONIGHT $throws __Recorder_clear(file __file){
	if(!fflush((FILE*)__file))
		throw(GenericException, strerror(errno));
}

/* Functions to Tonight.std.error */
static void TONIGHT __Error_text(string txt){
	__Recorder_text((file)stderr, txt);
}

static INLINE void TONIGHT __Error_textln(string txt){
	__Recorder_textln((file)stderr, txt);
}

static void TONIGHT __Error_print(string txt, ...){
	va_list t;
	va_start(t, txt);
	__print_args((file)stderr, txt, t);
	va_end(t);
}

static void TONIGHT __Error_println(string txt, ...){
	va_list t;
	va_start(t, txt);
	__println_args((file)stderr, txt, t);
	va_end(t);
}

static void TONIGHT __Error_printargln(string txt, ...){
	va_list t;
	va_start(t, txt);
	__printargln_args((file)stderr, txt, t);
	va_end(t);
}

static INLINE void TONIGHT __Error_nl(void){
	fputc('\n', stderr);
}

static INLINE void TONIGHT __Error_nls(int qtd){
	while(qtd--)
		fputc('\n', stderr);
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
	string s;
	va_list v;
	va_start(v, txt);
	for(s = txt; s; s = va_arg(v, string))
		strcat(str, s);
	strcat(str, "\n");
	va_end(v);
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


/* Functions to Tonight.Wide.Console.input */
static char TONIGHT $throws __Scanner_Wide_nextChar(void){
	if(wscanf(L"%c", &c) != 1)
		throw(InputException, "Impossible to read a \"char\" from the standard input");
	return c;
}

static int TONIGHT $throws __Scanner_Wide_nextInt(void){
	if(wscanf(L"%i", &i) != 1)
		throw(InputException, "Impossible to read an \"int\" from the standard input");
	return i;
}

static float TONIGHT $throws __Scanner_Wide_nextFloat(void){
	if(wscanf(L"%f", &f) != 1)
		throw(InputException, "Impossible to read a \"float\" from the standard input");
	return f;
}

static double TONIGHT $throws __Scanner_Wide_nextDouble(void){
	if(wscanf(L"%lf", &d) != 1)
		throw(InputException, "Impossible to read a \"double\" from the standard input");
	return d;
}

static pstring TONIGHT $throws __Scanner_Wide_next(void){
	if(wscanf(L"%l1000s", wstr) != 1)
		throw(InputException, "Impossible to read a \"string\" from the standard input");
	return toWide(wstr);
}

static pstring TONIGHT $throws __Scanner_Wide_nextLine(void){
	if(wscanf(L" %1000l[^\n]s", wstr) != 1)
		throw(InputException, "Impossible to read a \"string\" from the standard input");
	return toWide(wstr);
}

static INLINE void TONIGHT  __Scanner_Wide_clear(void){
	while(!feof(stdin))
		if(fgetc(stdin) == L'\n')
			return;
}

static INLINE void TONIGHT __Scanner_Wide_ignore(void){
	wscanf(L"%*ls");
}

static INLINE void TONIGHT __Scanner_Wide_ignoreChar(void){
	wscanf(L"%*c");
}

/* Functions to Tonight.Wide.File.Input */
static char TONIGHT $throws __Scanner_Wide_file_nextChar(file _file){
	if(fwscanf((FILE*)_file, L"%c", &c) != 1)
		throw(InputException, "Impossible to read a \"char\" from the file");
	return c;
}

static int TONIGHT $throws __Scanner_Wide_file_nextInt(file _file){
	if(fwscanf((FILE*)_file, L"%i", &i) != 1)
		throw(InputException, "Impossible to read an \"int\" from the file");
	return i;
}

static float TONIGHT $throws __Scanner_Wide_file_nextFloat(file _file){
	if(fwscanf((FILE*)_file, L"%f", &f) != 1)
		throw(InputException, "Impossible to read a \"float\" from the file");
	return f;
}

static double TONIGHT $throws __Scanner_Wide_file_nextDouble(file _file){
	if(fwscanf((FILE*)_file, L"%lf", &d) != 1)
		throw(InputException, "Impossible to read a \"double\" from the file");
	return d;
}

static pstring TONIGHT $throws __Scanner_Wide_file_next(file _file){
	if(fwscanf((FILE*)_file, L"%1000s", wstr) != 1)
		throw(InputException, "Impossible to read a \"string\" from the file");
	return toWide(wstr);
}

static pstring TONIGHT $throws __Scanner_Wide_file_nextLine(file _file){
	if(fwscanf((FILE*)_file, L" %1000[^\n]s", wstr) != 1)
		throw(InputException, "Impossible to read a \"string\" from the file");
	return toWide(wstr);
}

static INLINE void TONIGHT __Scanner_Wide_file_clear(file _file){
	while(!feof((FILE*)_file))
		if(fgetc((FILE*)_file) == L'\n')
			return;
}

static INLINE void TONIGHT __Scanner_Wide_file_ignore(file _file){
	fwscanf((FILE*)_file, L"%*s");
}

static INLINE void TONIGHT __Scanner_Wide_file_ignoreChar(file _file){
	fwscanf((FILE*)_file, L"%*c");
}

/* Functions to Tonight.Wide.String.Input */
static char TONIGHT $throws __Scanner_Wide_string_nextChar(pstring str){
	if(swscanf(str, L"%c", &c) != 1)
		throw(InputException, "Impossible to read a \"char\" from the string");
	return c;
}

static int TONIGHT $throws __Scanner_Wide_string_nextInt(pstring str){
	if(swscanf(str, L"%i", &i) != 1)
		throw(InputException, "Impossible to read an \"int\" from the string");
	return i;
}

static float TONIGHT $throws __Scanner_Wide_string_nextFloat(pstring str){
	if(swscanf(str, L"%f", &f) != 1)
		throw(InputException, "Impossible to read a \"float\" from the string");
	return f;
}

static double TONIGHT $throws __Scanner_Wide_string_nextDouble(pstring str){
	if(swscanf(str, L"%lf", &d) != 1)
		throw(InputException, "Impossible to read a \"double\" from the string");
	return d;
}

static pstring TONIGHT $throws __Scanner_Wide_string_next(pstring s){
	if(swscanf(s, L"%1000ls", wstr) != 1)
		throw(InputException, "Impossible to read a \"string\" from the string");
	return toWide(wstr);
}

static pstring TONIGHT $throws __Scanner_Wide_string_nextLine(pstring s){
	if(swscanf(s, L" %1000l[^\n]s", wstr) != 1)
		throw(InputException, "Impossible to read a \"string\" from the string");
	return toWide(wstr);
}

static void TONIGHT __Scanner_Wide_string_clear(pstring str){
	while(*(wchar_t*)str != L'\n')
		++ str;
}

static void TONIGHT __Scanner_Wide_string_ignore(pstring str){
	swscanf(str, L"%*s");
}

static void TONIGHT __Scanner_Wide_string_ignoreChar(pstring str){
	swscanf(str, L"%*c");
}

/* Functions to Tonight.Wide.Error.Input */
static INLINE char TONIGHT __Scanner_Wide_Error_nextChar(void){
	return (char)errno;
}

static INLINE int TONIGHT __Scanner_Wide_Error_nextInt(void){
	return errno;
}

static INLINE float TONIGHT __Scanner_Wide_Error_nextFloat(void){
	return (float)errno;
}

static double TONIGHT __Scanner_Wide_Error_nextDouble(void){
	return (double)errno;
}

static pstring TONIGHT $throws __Scanner_Wide_Error_next(void){
	return __Scanner_Wide_string_next(strerror(errno));
}

static INLINE pstring TONIGHT $throws __Scanner_Wide_Error_nextLine(void){
	return __Scanner_Wide_string_nextLine(strerror(errno));
}

/* Functions to Tonight.Wide.Console.Output */
static INLINE void TONIGHT __Screen_Wide_text(pstring txt){
	__Recorder_Wide_text((file)stdout, txt);
}

static INLINE void TONIGHT __Screen_Wide_textln(pstring txt){
	__Recorder_Wide_textln((file)stdout, txt);
}

static void TONIGHT __Screen_Wide_print(pstring txt, ...){
	va_list t;
	va_start(t, txt);
	__print_Wide_args((file)stdout, txt, t);
	va_end(t);
}

static void TONIGHT __Screen_Wide_println(pstring txt, ...){
	va_list t;
	va_start(t, txt);
	__println_Wide_args((file)stdout, txt, t);
	va_end(t);
}

static void TONIGHT __Screen_Wide_printargln(pstring txt, ...){
	va_list t;
	va_start(t, txt);
	__printargln_Wide_args((file)stdout, txt, t);
	va_end(t);
}

static void TONIGHT __Screen_Wide_nl(void){
	putchar(L'\n');
}

static void TONIGHT __Screen_Wide_nls(int qtd){
	while(qtd--)
		putchar(L'\n');
}

static void TONIGHT __Screen_Wide_clear(void){
	if(!fflush(stdout))
		throw(GenericException, strerror(errno));
}

/* Output base functions */
static NORMAL void TONIGHT __print_Wide_args(file _file, pstring first, va_list args){
	pstring s;
	for(s = first; s; s = va_arg(args, pstring))
		__Recorder_Wide_text(_file, s);
}

static NORMAL void TONIGHT __println_Wide_args(file _file, pstring first, va_list args){
	pstring s;
	for(s = first; s; s = va_arg(args, pstring))
		__Recorder_Wide_text(_file, s);
	__Recorder_Wide_text(_file, L"\n");
}

static NORMAL void TONIGHT __printargln_Wide_args(file _file, pstring first, va_list args){
	pstring s;
	for(s = first; s; s = va_arg(args, pstring))
		__Recorder_Wide_textln(_file, s);
}

/* Functions to Tonight.std.file.output */
static void TONIGHT __Recorder_Wide_text(file _file, pstring txt){
	fwprintf((FILE*)_file, L"%ls", txt);
}

static INLINE void TONIGHT __Recorder_Wide_textln(file _file, pstring txt){
	fwprintf((FILE*)_file, L"%ls\n", txt);
}

static void TONIGHT __Recorder_Wide_print(file _file, pstring txt, ...){
	va_list t;
	va_start(t, txt);
	__print_Wide_args(_file, txt, t);
	va_end(t);
}

static void TONIGHT __Recorder_Wide_println(file _file, pstring txt, ...){
	va_list t;
	va_start(t, txt);
	__println_Wide_args(_file, txt, t);
	va_end(t);
}

static void TONIGHT __Recorder_Wide_printargln(file _file, pstring txt, ...){
	va_list t;
	va_start(t, txt);
	__printargln_Wide_args(_file, txt, t);
	va_end(t);
}

static INLINE void TONIGHT __Recorder_Wide_nl(file __file){
	fputc(L'\n', (FILE*)__file);
}

static INLINE void TONIGHT __Recorder_Wide_nls(file __file, int qtd){
	while(qtd--)
		fputc(L'\n', (FILE*)__file);
}

static void TONIGHT $throws __Recorder_Wide_clear(file __file){
	if(!fflush((FILE*)__file))
		throw(GenericException, strerror(errno));
}

/* Functions to Tonight.Wide.Error.Output */
static void TONIGHT __Error_Wide_text(pstring txt){
	__Recorder_Wide_text((file)stderr, txt);
}

static INLINE void TONIGHT __Error_Wide_textln(pstring txt){
	__Recorder_Wide_textln((file)stderr, txt);
}

static void TONIGHT __Error_Wide_print(pstring txt, ...){
	va_list t;
	va_start(t, txt);
	__print_Wide_args((file)stderr, txt, t);
	va_end(t);
}

static void TONIGHT __Error_Wide_println(pstring txt, ...){
	va_list t;
	va_start(t, txt);
	__println_Wide_args((file)stderr, txt, t);
	va_end(t);
}

static void TONIGHT __Error_Wide_printargln(pstring txt, ...){
	va_list t;
	va_start(t, txt);
	__printargln_Wide_args((file)stderr, txt, t);
	va_end(t);
}

static INLINE void TONIGHT __Error_Wide_nl(void){
	fputc(L'\n', stderr);
}

static INLINE void TONIGHT __Error_Wide_nls(int qtd){
	while(qtd--)
		fputc(L'\n', stderr);
}

static void TONIGHT $throws __Error_Wide_clear(void){
	if(!fflush(stderr))
		throw(GenericException, strerror(errno));
}

/* Functions to Tonight.Wide.String.Output */
static void TONIGHT __String_Wide_text(wchar_t str[], pstring txt){
	swprintf(str, wcslen(txt), L"%ls", txt);
}

static void TONIGHT __String_Wide_textln(wchar_t str[], pstring txt){
	swprintf(str, wcslen(txt), L"%ls\n", txt);
}

static void TONIGHT __String_Wide_print(wchar_t str[], pstring txt, ...){
	pstring s;
	va_list v;
	va_start(v, txt);
	for(s = txt; s; s = va_arg(v, pstring))
		wcscat(str, s);
	va_end(v);
}

static void TONIGHT __String_Wide_println(wchar_t str[], pstring txt, ...){
	pstring s;
	va_list v;
	va_start(v, txt);
	for(s = txt; s; s = va_arg(v, pstring))
		wcscat(str, s);
	wcscat(str, L"\n");
	va_end(v);
}

static void TONIGHT __String_Wide_printargln(wchar_t str[], pstring txt, ...){
	pstring s;
	va_list v;
	va_start(v, txt);
	for(s = txt; s; s = va_arg(v, pstring))
		wcscat(wcscat(str, s), L"\n");
	va_end(v);
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

/* Functions to Tonight.std.TimeNow */
static Time TONIGHT __time(void){
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

static file TONIGHT $throws __new_File(string fName, FileMode fMode){
	file f = (file)fopen(fName, fMode.value);
	if(!f)
		throw(FileOpenException, concat("Impossible to open the file \"", fName, "\"", $end));
	return f;
}

/* Alloc pointers */
static char* TONIGHT $throws __new_char(char value){
	char* c = Memory.alloc(sizeof(char));
	*c = value;
	return c;
}

static byte* TONIGHT $throws __new_byte(byte value){
	byte* b = Memory.alloc(sizeof(byte));
	*b = value;
	return b;
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

static pstring TONIGHT $throws __new_String(pstring value){
	pstring *s = Memory.alloc(sizeof(pstring));
	*s = value;
	return s;
}

static pointer TONIGHT $throws __new_pointer(pointer value){
	pointer *p = Memory.alloc(sizeof(pointer));
	*p = value;
	return p;
}

static ICollection notImplemented = {
	(pointer)__Default_void_function,
	(pointer)__Default_void_function,
	(pointer)__Default_void_function
};

static pointer TONIGHT $throws __new_memory(size_t q){
	MemoryData *p = p_malloc(sizeof(MemoryData) + q);
	if(!p)
		throw(MemoryAllocException, strerror(errno));
	p->size = q;
	p->collection = &notImplemented;
	return p->data;
}

static pointer TONIGHT $throws __realloc_memory(pointer mem, size_t q){
	MemoryData *p = p_realloc(mem - sizeof(MemoryData), sizeof(MemoryData) + q);
	if(!p)
		throw(MemoryAllocException, strerror(errno));
	p->size = q;
	p->collection = &notImplemented;
	return p->data;
}

static INLINE size_t TONIGHT __memory_size(pointer mem){
	return ((MemoryData*)(mem - sizeof(MemoryData)))->size;
}

static INLINE pointer TONIGHT __memory_copy(pointer mem) {
	register size_t size = __memory_size(mem);
	return memcpy(__new_memory(size), mem, size);
}

static INLINE void TONIGHT __memory_free(pointer mem){
	if(mem) p_free(mem - sizeof(MemoryData));
}

/* Initialize arrays */

static ICollection __Array_collection = {
	.length = Array_length,
	.size = Array_size,
	.access = Array_access
};

static pointer TONIGHT $throws alloc_array(size_t size, int lenght){
	ArrayData *p = p_malloc(sizeof(ArrayData) + size * lenght);
	if(!p)
		throw(MemoryAllocException, strerror(errno));
	p->length = lenght;
	p->size = size;
	p->collection = &__Array_collection;
	return p->data;
}

pointer TONIGHT NO_CALL __create_array(size_t size, int length, pointer array){
	pointer ret = __new_array_generic(size, length);
	register int i;
	for(i=0; i<length; i++)
		memcpy(Array_access(ret, i), array + i * size, size);
	return ret;
}

static INLINE char* TONIGHT $throws __new_array_char(int q){
	return alloc_array(sizeof(char), q);
}

static INLINE byte* TONIGHT $throws __new_array_byte(int q){
	return alloc_array(sizeof(byte), q);
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

/* Functions to Convert */
static char TONIGHT char_fromString(string s){
	char ret = *s;
	if(* ++ s)
		throw(ConvertException, "Impossible to convert the string to a char");
	return ret;
}

static byte TONIGHT $throws byte_fromString(string s){
	byte b;
	string a;
	i = (byte)strtol(s, &a, 0);
	if(*a)
		throw(ConvertException, "Impossible to convert the string to byte");
	return i;
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

static string TONIGHT $throws string_fromDate(Time t){
	static char s[100] = {0};
	if(!strftime(s, sizeof s, "%c", t))
		throw(ConvertException, strerror(errno));
	return toString(s);
}

/* Functions to String */
static string TONIGHT String_formated(const string frmt, ...){
	static char s[1001];
	va_list v;
	va_start(v, frmt);
	vsprintf(s, frmt, v);
	va_end(v);
	return toString(s);
}

static INLINE string TONIGHT String_concatenate(string str1, string str2){
	return concat(str1, str2, $end);
}

static string TONIGHT String_upper(const string str){
	register string s, aux = toString(str);
	for(s = aux; *s; s++){
		toupper(*s);
	}
	return aux;
}

static string TONIGHT String_lower(const string str){
	register string s, aux = toString(str);
	for(s = aux; *s; s++){
		tolower(*s);
	}
	return aux;
}

static INLINE string TONIGHT byte_toString(byte b){
	return s_is((int)b);
}

static string TONIGHT String_sep(register string *stringp, register const string delim){
	register string s;
	register string spanp;
	register int c, sc;
	string tok;
	
	if (!(s = *stringp))
		return NULL;
	for (tok = s;;) {
		c = *s++;
		spanp = delim;
		do {
			if ((sc = *spanp++) == c){
				if (!c)
					s = NULL;
				else
					s[-1] = 0;
				*stringp = s;
				return tok;
			}
		} while (sc != 0);
	}
}

static string ARRAY String_split(string src, string lim)
{
	register int i, ret_len;
	string ARRAY ret = NULL;
	string aux, aux2;
	
	for(aux2 = aux = toString(src), i = 0; String_sep(&aux, lim); i++);
	__memory_free(aux2);
	ret_len = i;
	ret = __new_array_String(ret_len);
	aux = src;
	for(aux2 = aux = toString(src), i = 0; i < ret_len; i++)
		ret[i] = toString(String_sep(&aux, lim));
	__memory_free(aux2);
	return ret;
}

static string String_trim(const string _str){
	string str = toString(_str);
	register string aux = str + strlen(str) - 1;
	while(isspace(*str))
		++str;
	while(isspace(*aux))
		*aux-- = 0;
	return str;
}

/* Functions to WideString */
static pstring TONIGHT WString_formated(const pstring frmt, ...){
	static wchar_t w[1001];
	va_list v;
	va_start(v, frmt);
	vswprintf(w, sizeof w, frmt, v);
	va_end(v);
	return toWide(w);
}

static INLINE pstring TONIGHT WString_concatenate(pstring str1, pstring str2){
	return wconcat(str1, str2, $end);
}

static pstring TONIGHT WString_upper(const pstring str){
	register pstring s, aux = toWide(str);
	for(s = aux; *(wchar_t*)s; s++){
		toupper(*(wchar_t*)s);
	}
	return aux;
}

static pstring TONIGHT WString_lower(const pstring str){
	register pstring s, aux = toWide(str);
	for(s = aux; *(wchar_t*)s; s++){
		tolower(*(wchar_t*)s);
	}
	return aux;
}

static pstring TONIGHT WString_sep(register pstring *stringp, register const pstring delim){
	register wchar_t* s;
	register wchar_t* spanp;
	register int c, sc;
	pstring tok;
	
	if (!(s = *stringp))
		return NULL;
	for (tok = s;;) {
		c = *s++;
		spanp = delim;
		do {
			if ((sc = *spanp++) == c){
				if (!c)
					s = NULL;
				else
					s[-1] = 0;
				*stringp = s;
				return tok;
			}
		} while (sc != 0);
	}
}

static pstring ARRAY WString_split(pstring src, pstring lim)
{
	register int i, ret_len;
	wchar_t* ARRAY ret = NULL;
	pstring aux, aux2;
	
	for(aux2 = aux = toWide(src), i = 0; WString_sep(&aux, lim); i++);
	__memory_free(aux2);
	ret_len = i;
	ret = __new_array_generic(sizeof(wchar_t), ret_len);
	aux = src;
	for(aux2 = aux = toWide(src), i = 0; i < ret_len; i++)
		ret[i] = toWide(WString_sep(&aux, lim));
	__memory_free(aux2);
	return (pstring)ret;
}

static pstring WString_trim(const pstring _str){
	wchar_t* str = toWide(_str);
	register wchar_t* aux = str + wcslen(str) - 1;
	while(isspace(*str))
		++str;
	while(isspace(*aux))
		*aux-- = 0;
	return str;
}

/* Functions to Array */
static INLINE int TONIGHT Array_length(pointer array){
	checkArgumentPointer(array);
	return ((ArrayData*)(array - sizeof(ArrayData)))->length;
}

static INLINE size_t TONIGHT Array_size(pointer array){
	checkArgumentPointer(array);
	return ((ArrayData*)(array - sizeof(ArrayData)))->size;
}

static pointer TONIGHT $throws Array_access(pointer array, int index){
	int lenght = Array_length(array);
	size_t size = Array_size(array);
	if(index < 0 || index >= lenght)
		throw(ArrayIndexBoundException, "Index out of array bounds");
	return array + index * size;
}

static INLINE void TONIGHT Array_free(pointer array){
	if(array) p_free(array - sizeof(ArrayData));
}

static string TONIGHT Array_toString(pointer array, P_retString method, string sep){
	register int i, length = Array_length(array);
	char ARRAY str = __new_array_char((Array_size(array) * 3 + strlen(sep)) * length);
	string ret;
	if(!length)
		return toString("");
	*str = 0;
	checkArgumentPointer(method);
	for(i=0; i<length; i++)
		strcat(strcat(str, getText(method(Array_access(array, i)))), sep);
	str[strlen(str) - strlen(sep)] = 0;
	ret = toString(str);
	Array_free(str);
	return ret;
}

static pointer TONIGHT Array_convert(pointer array, cast casting){
	register int i, length=Array.length(array);
	pointer ret = __new_array_generic(casting.result, length);
	for(i=0;i<length;i++)
		casting.parse(Array_access(array, i), Array_access(ret, i));
	return ret;
}

static pointer TONIGHT $throws Array_select(pointer array, condition where){
	register int i, j, length=Array_length(array);
	size_t size = Array_size(array);
	pointer ret=NULL, aux, arr=__new_array_generic(size, length);
	for(i=0, j=0; i<length; i++){
		aux=Array_access(array, i);
		if(where(aux)){
			memcpy(Array_access(arr, j), aux, size);
			j++;
		}
	}
	ret = __new_array_generic(size, j);
	for(i=0; i<j; i++)
		memcpy(Array_access(ret, i), Array_access(arr, i), size);
	Array_free(arr);
	return ret;
}

static bool TONIGHT $throws Array_contains(pointer array, pointer sub){
	register int array_lenth = Array_length(array);
	register int sub_lenth = Array_length(sub);
	register int array_size = Array_size(array);
	register int sub_size = Array_size(sub);
	register int i, j;
	if(array_size != sub_size)
		return false;
	for(i=0; i<sub_lenth; i++){
		bool part = false;
		for(j=0; j<array_lenth; j++)
			if(!memcmp(Array_access(sub, i), Array_access(array, j), array_size))
				part = true;
		if(!part)
			return false;
	}
	return true;
}

static string ARRAY __args = NULL;

static void onExit(void){
	if(__args){
		Array_free(__args);
		__args = NULL;
	}
}

#pragma weak __main__
extern int __main__();
#pragma weak Main
extern int Main(string*);
#pragma weak Setup
extern void Setup(string*);
#pragma weak Loop
extern bool Loop(void);

static void TONIGHT __Base_TonightMode(register int argc, string argv[]){
	register int i;
	static int f;
	__args = __new_array_String(argc);
	if(f++)
		throw(ApplicationException, "Application previosly initialized");
	for(i = 0; i < argc; i++)
		__args[i] = argv[i];
	atexit(onExit);
}

static int TONIGHT TonightModeDefault(register int argc, string argv[]){
	P_int func = Main;
	__Base_TonightMode(argc, argv);
	try
		if(func)
			return func(__args);
		else
			return EXIT_FAILURE;
	catch(GenericException)
		return EXIT_FAILURE;
}

static int TONIGHT TonightModeLoop(register int argc, string argv[]){
	P_void func = Setup;
	P_bool loop = Loop;
	__Base_TonightMode(argc, argv);
	try
		if(func && loop){
			func(__args);
			while(loop());
			return EXIT_SUCCESS;
		}
		else
			return EXIT_FAILURE;
	catch(GenericException)
		return EXIT_FAILURE;
}

int main(int argc, string argv[]){
	if((pointer)__main__)
		return __main__(argc, argv);
	if((pointer)Main)
		return TonightModeDefault(argc, argv);
	if((pointer)Setup)
		return TonightModeLoop(argc, argv);
}

static INLINE void TONIGHT Exit_WithSuccess(void){
	exit(EXIT_SUCCESS);
}

static INLINE void TONIGHT Exit_WithFail(void){
	exit(EXIT_FAILURE);
}

INLINE ICollection* TONIGHT getICollection(pointer p){
	return *(ICollection**)(p - sizeof(ICollection*));
}

static INLINE int TONIGHT Collection_lenght(pointer p){
	return getICollection(p)->length(p);
}

static INLINE size_t TONIGHT Collection_size(pointer p){
	return getICollection(p)->size(p);
}

static INLINE pointer TONIGHT Collection_access(pointer p, int i){
	return getICollection(p)->access(p, i);
}

INLINE void TONIGHT checkArgumentPointer(pointer arg){
	if(!arg)
		throw(NullArgumentException, "Null argument");
}

static INLINE void TONIGHT File_close(file f){
	if(f) fclose((FILE*)f);
}

static INLINE bool TONIGHT File_end(file f){
	if(f) return feof((FILE*)f) ? true : false;
	return false;
}

static INLINE void TONIGHT File_rewind(file f){
	if(f) rewind((FILE*)f);
}

static INLINE file TONIGHT File_stdInput(void){
	return (file)stdin;
}

static INLINE file TONIGHT File_stdOutput(void){
	return (file)stdout;
}

static INLINE file TONIGHT File_stdError(void){
	return (file)stderr;
}

static INLINE Class TONIGHT Object_getClass(object obj){
	return obj->class_pointer;
}

static INLINE size_t TONIGHT Object_getSize(object obj){
	return obj->class_pointer->size;
}

static object TONIGHT Object_copy(object src){
	object ret = Memory.alloc(sizeof(Intern_Object));
	ret->class_pointer = src->class_pointer;
	ret->data = __memory_copy(src->data);
	return ret;
}

static INLINE void TONIGHT Callback_setMalloc(P_pointer callback){
	p_malloc = callback;
}

static INLINE void TONIGHT Callback_setCalloc(P_pointer callback){
	p_calloc = callback;
}

static INLINE void TONIGHT Callback_setRealloc(P_pointer callback){
	p_realloc = callback;
}

static INLINE void TONIGHT Callback_setFree(P_void callback){
	p_free = callback;
}
