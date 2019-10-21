#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include "../include/tonight.h"
#include "../include/Tonight/exceptions.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/array.h"
#include "../include/Tonight/string.h"

#undef main

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
