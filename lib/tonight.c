#include "tonight.proto.h"
#include "tonight.objects.h"

static char c;
static int i;
static float f;
static double d;
static char str[1001];

static char __buffer[1024];
static int text_color = 7, background_color = 0;

#include "tonight.sys.h"

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

static INLINE string TONIGHT __locale(void){
	return setlocale(Locale.category, Locale.name);
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

INLINE string TONIGHT toString(register pointer __array){
	return (string)strcpy(Memory.alloc((strlen(__array) + 1) * sizeof(char)), __array);
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
			if(ASCII_isUpper(*s1))
				if(ASCII_toLower(*s1) != *s2)
					return false;
			if(ASCII_isLower(*s1))
				if(ASCII_toUpper(*s1) != *s2)
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
	va_start(t, txt);
	for(s = txt; s; s = va_arg(t, string))
		__Screen_text(s);
	va_end(t);
	__Screen_text("\n");
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

/* Functions to Tonight.std.file.output */
static INLINE void TONIGHT __Recorder_text(file _file, string txt){
	for(;*txt;++txt)
		fputc(*txt, _file);
}

static INLINE void TONIGHT __Recorder_textln(file _file, string txt){
	__Recorder_text(_file, txt);
	__Recorder_text(_file, "\n");
}

static void TONIGHT __Recorder_print(file _file, string txt, ...){
	va_list t;
	string s;
	va_start(t, txt);
	for(s = txt; s; s = va_arg(t, string))
		__Recorder_text(_file, s);
	va_end(t);
}

static void TONIGHT __Recorder_println(file _file, string txt, ...){
	va_list t;
	string s;
	va_start(t, txt);
	for(s = txt; s; s = va_arg(t, string))
		__Recorder_text(_file, s);
	va_end(t);
	__Recorder_text(_file, "\n");
}

static void TONIGHT __Recorder_printargln(file _file, string txt, ...){
	va_list t;
	string s;
	va_start(t, txt);
	for(s = txt; s; s = va_arg(t, string))
		__Recorder_textln(_file, s);
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

static object TONIGHT __new_Object(Class_Data name, ...){
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

static pointer TONIGHT $throws __realloc_memory(pointer mem, size_t q){
	pointer p = realloc(mem, q + sizeof(size_t));
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

/* Initialize matrixes */
static char** TONIGHT $throws __new_matrix_char(int l, int c){
	char** m = alloc_array(sizeof(char*), l);
	register int i;
	for(i = 0; i < l; i++)
		m[i] = __new_array_char(c);
	return m;
}

static byte** TONIGHT $throws __new_matrix_byte(int l, int c){
	byte** m = alloc_array(sizeof(byte*), l);
	register int i;
	for(i = 0; i < l; i++)
		m[i] = __new_array_byte(c);
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
		ASCII_toUpper(*s);
	}
	return aux;
}

static string TONIGHT String_lower(const string str){
	register string s, aux = toString(str);
	for(s = aux; *s; s++){
		ASCII_toLower(*s);
	}
	return aux;
}

static INLINE string TONIGHT byte_toString(byte b){
	return s_is((int)b);
}

/* Functions to Array */
static INLINE int TONIGHT Array_length(pointer array){
	checkArgumentPointer(array);
	return *(int*)(array - sizeof(size_t) - sizeof(int));
}

static INLINE size_t TONIGHT Array_size(pointer array){
	checkArgumentPointer(array);
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
	checkArgumentPointer(array);
	free(array - sizeof(int) - sizeof(size_t));
}

static string TONIGHT Array_toString(pointer array, P_retString method){
	static char ARRAY str = NULL;
	register int i, length = Array.length(array);
	if(str)
		Array.free(str);
	str = Array.Char((Array.size(array) * 3 + 2) * Array.length(array));
	*str = 0;
	checkArgumentPointer(method);
	strcat(str, "[");
	for(i=0;i<length;i++)
		strcat(strcat(str, getText(method(Array_access(array, i)))), ", ");
	str[strlen(str) - 2] = ']';
	return toString(str);
}

static pointer TONIGHT Array_convert(pointer array, cast casting){
	register int i, length = Array.length(array);
	pointer ret = Array.Generic(casting.result, length);
	size_t size_array = Array.size(array);
	for(i=0;i<length;i++){
		casting.parse(Array.access(array, i), Array.access(ret, i));
	}
	return ret;
}

static string ARRAY __args = NULL;

static void onExit(void){
	if(__args){
		Array.free(__args);
		__args = NULL;
	}
}

int TONIGHT TonightMode(P_int func, register int argc, string argv[]){
	register int i;
	static int f;
	string ARRAY arg = __args = Array.String(argc);
	if(f++)
		throw(ApplicationException, "Application previosly initialized");
	for(i = 0; i < argc; i++)
		arg[i] = argv[i];
	atexit(onExit);
	try
		return func(arg);
	catch(GenericException)
		return EXIT_FAILURE;
}

static INLINE void TONIGHT Exit_WithSuccess(void){
	exit(EXIT_SUCCESS);
}

static INLINE void TONIGHT Exit_WithFail(void){
	exit(EXIT_FAILURE);
}

INLINE void TONIGHT checkArgumentPointer(pointer arg){
	if(!arg)
		throw(NullArgumentException, "Null argument");
}


#define CR(_case, _return)	case _case: return _return
#define RC(_return, _case)	case _case: return _return

static unsigned char ASCII_normalizeChar(int input){
	switch(input){
		CR('Ç', 128);CR('ü', 129);
		CR('é', 130);CR('â', 131);
		CR('ä', 132);CR('à', 133);
		CR('å', 134);CR('ç', 135);
		CR('ê', 136);CR('ë', 137);
		CR('è', 138);CR('ï', 139);
		CR('î', 140);CR('ì', 141);
		CR('Ä', 142);CR('Å', 143);
		CR('É', 144);CR('æ', 145);
		CR('Æ', 146);CR('ô', 147);
		CR('ö', 148);CR('ò', 149);
		CR('û', 150);CR('ù', 151);
		CR('ÿ', 152);CR('Ö', 153);
		CR('Ü', 154);CR('ø', 155);
		CR('£', 156);CR('Ø', 157);
		CR('×', 158);CR('ƒ', 159);
		CR('á', 160);CR('í', 161);
		CR('ó', 162);CR('ú', 163);
		CR('ñ', 164);CR('Ñ', 165);
		CR('ª', 166);CR('º', 167);
		CR('¿', 168);CR('®', 169);
		CR('¬', 170);CR('½', 171);
		CR('¼', 172);CR('¡', 173);
		CR('«', 174);CR('»', 175);
		CR('Á', 181);
		CR('Â', 182);CR('À', 183);
		CR('©', 184);
		CR('¢', 189);
		CR('¥', 190);
		CR('ã', 198);CR('Ã', 199);
		CR('¤', 207);
		CR('ð', 208);CR('Ð', 209);
		CR('Ê', 210);CR('Ë', 211);
		CR('È', 212);
		CR('Í', 214);CR('Î', 215);
		CR('Ï', 216);
		CR('Ì', 222);
		CR('Ó', 224);CR('ß', 225);
		CR('Ô', 226);CR('Ò', 227);
		CR('õ', 228);CR('Õ', 229);
		CR('µ', 230);CR('þ', 231);
		CR('Þ', 232);CR('Ú', 233);
		CR('Û', 234);CR('Ù', 235);
		CR('ý', 236);CR('Ý', 237);
		CR('´', 239);
		CR('±', 241);
		CR('¾', 243);
		CR('¶', 244);CR('§', 245);
		CR('÷', 246);
		CR('°', 248);CR('¨', 249);
		CR('¹', 251);
		CR('³', 252);CR('²', 253);
		CR(' ', 255);
		default: return input;
	}
}

static string ASCII_normalizeString(string input){
	register string aux;
	for(aux = input; *aux; aux++)
		*aux = ASCII_normalizeChar(*aux);
	return input;
}

#define UP_LOWER_FUNC(TMP, func, _in) \
	switch(_in){\
		TMP('ü', 'Ü');\
		TMP('é', 'É');\
		TMP('â', 'Â');\
		TMP('ä', 'Ä');\
		TMP('à', 'À');\
		TMP('å', 'Å');\
		TMP('ç', 'Ç');\
		TMP('ê', 'Ê');\
		TMP('ë', 'Ë');\
		TMP('è', 'È');\
		TMP('ï', 'Ï');\
		TMP('î', 'Î');\
		TMP('ì', 'Ì');\
		TMP('ô', 'Ô');\
		TMP('ö', 'Ö');\
		TMP('ò', 'Ò');\
		TMP('û', 'Û');\
		TMP('ù', 'Ù');\
		TMP('á', 'Á');\
		TMP('í', 'Í');\
		TMP('ó', 'Ó');\
		TMP('ú', 'Ú');\
		TMP('ñ', 'Ñ');\
		TMP('ã', 'Ã');\
		TMP('õ', 'Õ');\
		TMP('ý', 'Ý');\
		default:\
			if(input <= 127) return func(input);\
			else return input;\
	}

static u_char TONIGHT ASCII_toUpper(int input){
	UP_LOWER_FUNC(CR, toupper, input)
}

static u_char TONIGHT ASCII_toLower(int input){
	UP_LOWER_FUNC(RC, tolower, input)
}

#define	CT(_case, _null)	case _case: return true
#define	TC(_null, _case)	case _case: return true

static bool TONIGHT ASCII_isUpper(int input){
	UP_LOWER_FUNC(TC, isupper, input)
}

static bool TONIGHT ASCII_isLower(int input){
	UP_LOWER_FUNC(CT, islower, input)
}
