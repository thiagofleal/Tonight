#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include "../include/tonight.h"
#include "../include/Tonight/exceptions.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/array.h"

#undef main

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
		//_setmode(fileno((FILE*)src), _O_TEXT);
	#endif
}

static INLINE void TONIGHT __enableUTF8(file src){
	#ifdef _WIN32
		//_setmode(fileno((FILE*)src), _O_U8TEXT);
	#endif
}

static INLINE string TONIGHT __concatString(char dest[], char from[], size_t length){
	return strncat(dest, from, length - strlen(dest) - 1);
}

static INLINE wstring TONIGHT __wconcatString(wchar_t dest[], wchar_t from[], size_t length){
	return wcsncat(dest, from, length - wcslen(dest) - 1);
}

static INLINE wstring TONIGHT __concatWString(wchar_t dest[], wchar_t from[], size_t length){
	return wcsncat(dest, from, length - wcslen(dest) - 1);
}

static wstring TONIGHT stringToWide(string s){
    wchar_t wstr[1001];
	snwprintf(wstr, ARRAY_LENGTH(wstr) - 1, L"%hs", s);
	return toWide(wstr);
}

static string TONIGHT wideToString(wstring s){
    char str[1001];
	snprintf(str, ARRAY_LENGTH(str) - 1, "%ls", s);
	return toString(str);
}

INLINE string TONIGHT toString(register pointer __array){
	register size_t size = (strlen(__array) + 1) * sizeof(char);
	return memcpy(Memory.alloc(size), __array, size);
}

INLINE wstring TONIGHT toWide(register pointer __array){
	register size_t size = (wcslen(__array) + 1) * sizeof(wchar_t);
	return memcpy(Memory.alloc(size), __array, size);
}

string TONIGHT concat(string wrd_1, ...){
	va_list va;
	static char s[10001];
	static string p;
	*s = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, string))
		__concatString(s, p, sizeof s);
	va_end(va);
	return toString(s);
}

string TONIGHT nconcat(size_t size, string wrd_1, ...){
	va_list va;
	char ARRAY s = NULL;
	static string p;
	s = Array.Char(size + 1);
	*s = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, string))
		strcat(s, p);
	va_end(va);
	p = toString(s);
	Array.free(s);
	return p;
}

wstring TONIGHT wconcat(wstring wrd_1, ...){
	va_list va;
	static wchar_t s[10001];
	static wstring p;
	*s = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, wstring))
		__wconcatString(s, p, sizeof s);
	va_end(va);
	return toWide(s);
}

wstring TONIGHT nwconcat(size_t size, wstring wrd_1, ...){
	va_list va;
	wchar_t ARRAY s = NULL;
	static wstring p;
	s = Array.Generic(sizeof(wchar_t), size + 1);
	*s = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, wstring))
		wcscat(s, p);
	va_end(va);
	p = toWide(s);
	Array.free(s);
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

retWideString TONIGHT wretConcat(wstring wrd_1, ...){
	va_list va;
	wstring p;
	static retWideString ret;
	*ret.Text = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, wstring))
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
	static char s[100];
	snprintf(s, sizeof s, "%.10g", var);
	return toString(s);
}

string TONIGHT s_ps(pointer var){
	static char s[100];
	snprintf(s, sizeof s, "%p", var);
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

retString TONIGHT fs(float var){
	register char *s = s_fs(var);
	static retString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
}

INLINE retString TONIGHT ps(pointer var){
	register char *s = s_ps(var);
	static retString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.free(s);
	return ret;
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

INLINE retString TONIGHT pps(pointer *p){
	return ps(*p);
}

longRetString TONIGHT cls(char var){
	register char *s = s_cs(var);
	static longRetString ret;
	strncpy(ret.Text, s, sizeof ret);
	Memory.Callback.free(s);
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

/* Functions to Convert */
static char TONIGHT char_fromString(string s){
	char ret = *s;
	if(* ++ s)
		throw(ConvertException, "Impossible to convert the string to a char");
	return ret;
}

static byte TONIGHT $throws byte_fromString(string s){
	string a;
	byte b = (byte)strtol(s, &a, 0);
	if(*a)
		throw(ConvertException, "Impossible to convert the string to byte");
	return b;
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
		*s = toupper(*s);
	}
	return aux;
}

static string TONIGHT String_lower(const string str){
	register string s, aux = toString(str);
	for(s = aux; *s; s++){
		*s = tolower(*s);
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

static string ARRAY String_split(string src, string lim){
	register int i, ret_len;
	string ARRAY ret = NULL;
	string aux, aux2;
	for(aux2 = aux = toString(src), i = 0; String_sep(&aux, lim); i++);
	Memory.free(aux2);
	ret_len = i;
	ret = Array.String(ret_len);
	aux = src;
	for(aux2 = aux = toString(src), i = 0; i < ret_len; i++)
		ret[i] = toString(String_sep(&aux, lim));
	Memory.free(aux2);
	return ret;
}

static string String_trim(const string _str){
    register string str = _str;
	register string aux = str + strlen(str) - 1;
	while(isspace(*str))
		++str;
	while(isspace(*aux))
		*aux-- = 0;
	return toString(str);
}

/* Functions to WideString */
static wstring TONIGHT WString_formated(const wstring frmt, ...){
	static wchar_t w[1001];
	va_list v;
	va_start(v, frmt);
	vswprintf(w, (wstring)frmt, v);
	va_end(v);
	return toWide(w);
}

static INLINE wstring TONIGHT WString_concatenate(wstring str1, wstring str2){
	return wconcat(str1, str2, $end);
}

static wstring TONIGHT WString_upper(const wstring str){
	register wstring s, aux = toWide(str);
	for(s = aux; *(wchar_t*)s; s++){
		*(wchar_t*)s = toupper(*(wchar_t*)s);
	}
	return aux;
}

static wstring TONIGHT WString_lower(const wstring str){
	register wstring s, aux = toWide(str);
	for(s = aux; *(wchar_t*)s; s++){
		*(wchar_t*)s = tolower(*(wchar_t*)s);
	}
	return aux;
}

static wstring TONIGHT WString_sep(register wstring *stringp, register const wstring delim){
	register wchar_t* s;
	register wchar_t* spanp;
	register int c, sc;
	wstring tok;

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

static wstring ARRAY WString_split(wstring src, wstring lim){
	register int i, ret_len;
	wstring ARRAY ret = NULL;
	wstring aux, aux2;
	for(aux2 = aux = toWide(src), i = 0; WString_sep(&aux, lim); i++);
	Memory.free(aux2);
	ret_len = i;
	ret = Array.Generic(sizeof(wstring), ret_len);
	aux = src;
	for(aux2 = aux = toWide(src), i = 0; i < ret_len; i++)
		ret[i] = toWide(WString_sep(&aux, lim));
	Memory.free(aux2);
	return ret;
}

static wstring WString_trim(const wstring _str){
	register wstring str = _str;
	register wstring aux = str + wcslen(str) - 1;
	while(isspace(*str))
		++str;
	while(isspace(*aux))
		*aux-- = 0;
	return toWide(str);
}

static string ARRAY __args = NULL;

static void onExit(void){
	if(__args){
        register int lenth = Array.length(__args);
        register int i = 0;
        for(;i<lenth;i++) free(__args[i]);
		Array.free(__args);
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
	__args = Array.String(argc);
	if(f++)
		throw(ApplicationException, "Application previosly initialized");
	for(i = 0; i < argc; i++)
		__args[i] = toString(argv[i]);
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
	catch(GenericException);
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
	catch(GenericException);
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

INLINE void TONIGHT checkArgumentPointer(pointer arg){
	if(!arg)
		throw(NullArgumentException, "Null argument");
}

/* New */
const TONIGHT struct __New New = {
	.Object = (pointer)newInstance,

	.Char = __new_char,
	.Byte = __new_byte,
	.Bool = __new_bool,
	.Int = __new_int,
	.Float = __new_float,
	.Double = __new_double,
	.String = __new_String,
	.Pointer = __new_pointer
};

/* String */
const struct __String String = {
	.formated = (pointer)String_formated,
	.copy = (pointer)toString,
	.concatenate = (pointer)String_concatenate,
	.upper = (pointer)String_upper,
	.lower = (pointer)String_lower,
	.length = (pointer)strlen,
	.compare = (pointer)strcmp,
	.sep = (pointer)String_sep,
	.split = (pointer)String_split,
	.trim = (pointer)String_trim,
//	.free = (pointer)__memory_free,
	.toString = (pointer)toString,
	.toWide = stringToWide
};

const struct __WideString WideString = {
	.formated = (pointer)WString_formated,
	.copy = (pointer)toWide,
	.concatenate = (pointer)WString_concatenate,
	.upper = (pointer)WString_upper,
	.lower = (pointer)WString_lower,
	.length = (pointer)wcslen,
	.compare = (pointer)wcscmp,
	.sep = (pointer)WString_sep,
	.split = (pointer)WString_split,
	.trim = (pointer)WString_trim,
//	.free = (pointer)__memory_free,
	.toString = (pointer)wideToString,
	.toWide = (pointer)toWide
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
	.With = exit,
	.WithSuccess = Exit_WithSuccess,
	.WithFail = Exit_WithFail
};
