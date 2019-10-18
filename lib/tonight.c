#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include "../include/tonight.h"
#include "../include/Tonight/exceptions.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/array.h"
#include "../include/Tonight/string.h"

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

INLINE wstring TONIGHT toWide(register pointer __array){
	register size_t size = (wcslen(__array) + 1) * sizeof(wchar_t);
	return memcpy(Memory.alloc(size), __array, size);
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

fixWideString TONIGHT wretConcat(wstring wrd_1, ...){
	va_list va;
	wstring p;
	static fixWideString ret;
	*ret.Text = 0;
	va_start(va, wrd_1);
	for (p = wrd_1; p; p = va_arg(va, wstring))
		__concatWString(ret.Text, p, sizeof ret);
	va_end(va);
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
static INLINE string TONIGHT byte_toString(byte b){
	return s_is((int)b);
}

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
	if(String.equal(s, "true"))
		return true;
	if(String.equal(s, "false"))
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
//	.toString = (pointer)wideToString,
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
