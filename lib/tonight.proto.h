#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <setjmp.h>
#include <locale.h>
#include <errno.h>
#include <stdarg.h>
#include <fcntl.h>

#ifdef _WIN32
#	include <io.h>
#endif

#include "../include/Tonight/tonight.h"

static INLINE void TONIGHT $throws __assert(bool test);
static INLINE void TONIGHT $throws __checkErrno(void);
static INLINE pointer TONIGHT $throws __Default_void_function();
static NORMAL bool TONIGHT pressKey(void);
static NORMAL int TONIGHT getKey(void);
static INLINE void TONIGHT __sleep(unsigned int);
static INLINE void TONIGHT cursor_position(int, int);
static INLINE void TONIGHT __clearScreen(void);

static NORMAL int TONIGHT TonightModeDefault(register int, string[]);
static NORMAL int TONIGHT TonightModeLoop(register int, string[]);

static INLINE string TONIGHT __locale(void);
static INLINE string TONIGHT __getlocale(int);
static INLINE int TONIGHT __getCategory(void);
static INLINE void TONIGHT __setCategory(int);
static INLINE string TONIGHT __getName(void);
static INLINE void TONIGHT __setName(string);
static INLINE int TONIGHT getKeyEcho(void);
static INLINE void TONIGHT __initRandom(void);
static INLINE void TONIGHT __enableASCII(file);
static INLINE void TONIGHT __enableUTF8(file);
static INLINE string TONIGHT $throws __concatString(char[], char[], int);
static INLINE pstring TONIGHT $throws __concatWString(wchar_t[], wchar_t[], int);
static INLINE pstring TONIGHT stringToWide(pstring);
static INLINE pstring TONIGHT wideToString(pstring);

static NORMAL char TONIGHT $throws __Scanner_nextChar(void);
static NORMAL int TONIGHT $throws __Scanner_nextInt(void);
static NORMAL float TONIGHT $throws __Scanner_nextFloat(void);
static NORMAL double TONIGHT $throws __Scanner_nextDouble(void);
static NORMAL string TONIGHT $throws __Scanner_next(void);
static NORMAL string TONIGHT $throws __Scanner_nextLine(void);
static NORMAL string TONIGHT $throws __Scanner_Password(int);
static INLINE void TONIGHT __Scanner_clear(void);
static INLINE void TONIGHT __Scanner_ignore(void);
static INLINE void TONIGHT __Scanner_ignoreChar(void);

static NORMAL char TONIGHT $throws __Scanner_file_nextChar(file);
static NORMAL int TONIGHT $throws __Scanner_file_nextInt(file);
static NORMAL float TONIGHT $throws __Scanner_file_nextFloat(file);
static NORMAL double TONIGHT $throws __Scanner_file_nextDouble(file);
static NORMAL string TONIGHT $throws __Scanner_file_next(file);
static NORMAL string TONIGHT $throws __Scanner_file_nextLine(file);
static INLINE void TONIGHT $throws __Scanner_file_clear(file);
static INLINE void TONIGHT __Scanner_file_ignore(file);
static INLINE void TONIGHT __Scanner_file_ignoreChar(file);

static NORMAL char TONIGHT $throws __Scanner_string_nextChar(string);
static NORMAL int TONIGHT $throws __Scanner_string_nextInt(string);
static NORMAL float TONIGHT $throws __Scanner_string_nextFloat(string);
static NORMAL double TONIGHT $throws __Scanner_string_nextDouble(string);
static NORMAL string TONIGHT $throws __Scanner_string_next(string);
static NORMAL string TONIGHT $throws __Scanner_string_nextLine(string);
static NORMAL void TONIGHT $throws __Scanner_string_clear(string);
static NORMAL void TONIGHT __Scanner_string_ignore(string);
static NORMAL void TONIGHT __Scanner_string_ignoreChar(string);

static NORMAL char TONIGHT $throws __Scanner_object_nextChar(IScanner, object);
static NORMAL int TONIGHT $throws __Scanner_object_nextInt(IScanner, object);
static NORMAL float TONIGHT $throws __Scanner_object_nextFloat(IScanner, object);
static NORMAL double TONIGHT $throws __Scanner_object_nextDouble(IScanner, object);
static NORMAL string TONIGHT $throws __Scanner_object_next(IScanner, object);
static INLINE string TONIGHT $throws __Scanner_object_nextLine(IScanner, object);
static INLINE void TONIGHT $throws __Scanner_object_clear(IScanner, object);
static INLINE void TONIGHT $throws __Scanner_object_ignore(IScanner, object);
static INLINE void TONIGHT $throws __Scanner_object_ignoreChar(IScanner, object);

static INLINE char TONIGHT __Scanner_Error_nextChar(void);
static INLINE int TONIGHT __Scanner_Error_nextInt(void);
static INLINE float TONIGHT __Scanner_Error_nextFloat(void);
static INLINE double TONIGHT __Scanner_Error_nextDouble(void);
static INLINE string TONIGHT $throws __Scanner_Error_next(void);
static INLINE string TONIGHT $throws __Scanner_Error_nextLine(void);

static INLINE void TONIGHT __Screen_text(string);
static INLINE void TONIGHT __Screen_textln(string);
static NORMAL void TONIGHT __Screen_print(string, ...);
static NORMAL void TONIGHT __Screen_println(string, ...);
static NORMAL void TONIGHT __Screen_printargln(string, ...);
static NORMAL void TONIGHT __Screen_nl(void);
static NORMAL void TONIGHT __Screen_nls(int);
static NORMAL void TONIGHT __Screen_clear(void);

static NORMAL void TONIGHT __print_args(file, string, va_list);
static NORMAL void TONIGHT __println_args(file, string, va_list);
static NORMAL void TONIGHT __printargln_args(file, string, va_list);

static INLINE void TONIGHT __Recorder_text(file, string);
static INLINE void TONIGHT __Recorder_textln(file, string);
static NORMAL void TONIGHT __Recorder_print(file, string, ...);
static NORMAL void TONIGHT __Recorder_println(file, string, ...);
static NORMAL void TONIGHT __Recorder_printargln(file, string, ...);
static INLINE void TONIGHT __Recorder_nl(file);
static INLINE void TONIGHT __Recorder_nls(file, int);
static NORMAL void TONIGHT __Recorder_clear(file);

static NORMAL void TONIGHT __Error_text(string);
static INLINE void TONIGHT __Error_textln(string);
static NORMAL void TONIGHT __Error_print(string, ...);
static NORMAL void TONIGHT __Error_println(string, ...);
static NORMAL void TONIGHT __Error_printargln(string, ...);
static INLINE void TONIGHT __Error_nl(void);
static INLINE void TONIGHT __Error_nls(int);
static NORMAL void TONIGHT __Error_clear(void);

static NORMAL void TONIGHT __String_text(char*, string);
static NORMAL void TONIGHT __String_textln(char*, string);
static NORMAL void TONIGHT __String_print(char*, string, ...);
static NORMAL void TONIGHT __String_println(char*, string, ...);
static NORMAL void TONIGHT __String_printargln(char*, string, ...);

static INLINE void TONIGHT __Object_text(IWriter, object, string);
static INLINE void TONIGHT __Object_textln(IWriter, object, string);
static NORMAL void TONIGHT __Object_print(IWriter, object, string, ...);
static NORMAL void TONIGHT __Object_println(IWriter, object, string, ...);
static NORMAL void TONIGHT __Object_printargln(IWriter, object, string, ...);
static INLINE void TONIGHT __Object_nl(IWriter, object);
static INLINE void TONIGHT __Object_nls(IWriter, object, int);
static NORMAL void TONIGHT __Object_clear(IWriter, object);

static NORMAL char TONIGHT $throws __Scanner_Wide_nextChar(void);
static NORMAL int TONIGHT $throws __Scanner_Wide_nextInt(void);
static NORMAL float TONIGHT $throws __Scanner_Wide_nextFloat(void);
static NORMAL double TONIGHT $throws __Scanner_Wide_nextDouble(void);
static NORMAL pstring TONIGHT $throws __Scanner_Wide_next(void);
static NORMAL pstring TONIGHT $throws __Scanner_Wide_nextLine(void);
static INLINE void TONIGHT __Scanner_Wide_clear(void);
static INLINE void TONIGHT __Scanner_Wide_ignore(void);
static INLINE void TONIGHT __Scanner_Wide_ignoreChar(void);

static NORMAL char TONIGHT $throws __Scanner_Wide_file_nextChar(file);
static NORMAL int TONIGHT $throws __Scanner_Wide_file_nextInt(file);
static NORMAL float TONIGHT $throws __Scanner_Wide_file_nextFloat(file);
static NORMAL double TONIGHT $throws __Scanner_Wide_file_nextDouble(file);
static NORMAL pstring TONIGHT $throws __Scanner_Wide_file_next(file);
static NORMAL pstring TONIGHT $throws __Scanner_Wide_file_nextLine(file);
static INLINE void TONIGHT $throws __Scanner_Wide_file_clear(file);
static INLINE void TONIGHT __Scanner_Wide_file_ignore(file);
static INLINE void TONIGHT __Scanner_Wide_file_ignoreChar(file);

static NORMAL char TONIGHT $throws __Scanner_Wide_string_nextChar(pstring);
static NORMAL int TONIGHT $throws __Scanner_Wide_string_nextInt(pstring);
static NORMAL float TONIGHT $throws __Scanner_Wide_string_nextFloat(pstring);
static NORMAL double TONIGHT $throws __Scanner_Wide_string_nextDouble(pstring);
static NORMAL pstring TONIGHT $throws __Scanner_Wide_string_next(pstring);
static NORMAL pstring TONIGHT $throws __Scanner_Wide_string_nextLine(pstring);
static NORMAL void TONIGHT $throws __Scanner_Wide_string_clear(pstring);
static NORMAL void TONIGHT __Scanner_Wide_string_ignore(pstring);
static NORMAL void TONIGHT __Scanner_Wide_string_ignoreChar(pstring);

static INLINE char TONIGHT __Scanner_Wide_Error_nextChar(void);
static INLINE int TONIGHT __Scanner_Wide_Error_nextInt(void);
static INLINE float TONIGHT __Scanner_Wide_Error_nextFloat(void);
static INLINE double TONIGHT __Scanner_Wide_Error_nextDouble(void);
static INLINE pstring TONIGHT $throws __Scanner_Wide_Error_next(void);
static INLINE pstring TONIGHT $throws __Scanner_Wide_Error_nextLine(void);

static INLINE void TONIGHT __Screen_Wide_text(pstring);
static INLINE void TONIGHT __Screen_Wide_textln(pstring);
static NORMAL void TONIGHT __Screen_Wide_print(pstring, ...);
static NORMAL void TONIGHT __Screen_Wide_println(pstring, ...);
static NORMAL void TONIGHT __Screen_Wide_printargln(pstring, ...);
static NORMAL void TONIGHT __Screen_Wide_nl(void);
static NORMAL void TONIGHT __Screen_Wide_nls(int);
static NORMAL void TONIGHT __Screen_Wide_clear(void);

static NORMAL void TONIGHT __print_Wide_args(file, pstring, va_list);
static NORMAL void TONIGHT __println_Wide_args(file, pstring, va_list);
static NORMAL void TONIGHT __printargln_Wide_args(file, pstring, va_list);

static INLINE void TONIGHT __Recorder_Wide_text(file, pstring);
static INLINE void TONIGHT __Recorder_Wide_textln(file, pstring);
static NORMAL void TONIGHT __Recorder_Wide_print(file, pstring, ...);
static NORMAL void TONIGHT __Recorder_Wide_println(file, pstring, ...);
static NORMAL void TONIGHT __Recorder_Wide_printargln(file, pstring, ...);
static INLINE void TONIGHT __Recorder_Wide_nl(file);
static INLINE void TONIGHT __Recorder_Wide_nls(file, int);
static NORMAL void TONIGHT __Recorder_Wide_clear(file);

static NORMAL void TONIGHT __Error_Wide_text(pstring);
static INLINE void TONIGHT __Error_Wide_textln(pstring);
static NORMAL void TONIGHT __Error_Wide_print(pstring, ...);
static NORMAL void TONIGHT __Error_Wide_println(pstring, ...);
static NORMAL void TONIGHT __Error_Wide_printargln(pstring, ...);
static INLINE void TONIGHT __Error_Wide_nl(void);
static INLINE void TONIGHT __Error_Wide_nls(int qtd);
static NORMAL void TONIGHT __Error_Wide_clear(void);

static NORMAL void TONIGHT __String_Wide_text(wchar_t[], pstring);
static NORMAL void TONIGHT __String_Wide_textln(wchar_t[], pstring);
static NORMAL void TONIGHT __String_Wide_print(wchar_t[], pstring, ...);
static NORMAL void TONIGHT __String_Wide_println(wchar_t[], pstring, ...);
static NORMAL void TONIGHT __String_Wide_printargln(wchar_t[], pstring, ...);

static NORMAL char TONIGHT __Random_simple_nextChar(void);
static INLINE int TONIGHT __Random_simple_nextInt(void);
static INLINE double TONIGHT __Random_simple_nextDouble(int);
static INLINE float TONIGHT __Random_simple_nextFloat(int);
static INLINE char TONIGHT __Random_end_nextChar(char);
static INLINE int TONIGHT __Random_end_nextInt(int);
static INLINE double TONIGHT __Random_end_nextDouble(double, int);
static INLINE float TONIGHT __Random_end_nextFloat(float, int);
static INLINE char TONIGHT __Random_begin_end_nextChar(char, char);
static INLINE int TONIGHT __Random_begin_end_nextInt(int, int);
static INLINE double TONIGHT __Random_begin_end_nextDouble(double, double, int);
static INLINE float TONIGHT __Random_begin_end_nextFloat(float, float, int);

static NORMAL Time TONIGHT __time(void);
static INLINE int TONIGHT __Time_hours(void);
static INLINE int TONIGHT __Time_minutes(void);
static INLINE int TONIGHT __Time_seconds(void);
static INLINE int TONIGHT __Time_day_week(void);
static INLINE int TONIGHT __Time_day_month(void);
static INLINE int TONIGHT __Time_day_year(void);
static INLINE int TONIGHT __Time_month(void);
static INLINE int TONIGHT __Time_year(void);

static INLINE void TONIGHT __Colors_textbackground(int, int);
static INLINE void TONIGHT __Colors_text(int);
static INLINE void TONIGHT __Colors_background(int);

static INLINE Scanner TONIGHT __new_Scanner(Input);
static INLINE Writer TONIGHT __new_Writer(Output);
static INLINE Random TONIGHT __new_Random(RandomicMaker);
static INLINE Timer TONIGHT __new_Timer(TimerCreate);
static INLINE Painter TONIGHT __new_Painter(ColorCreate);
static NORMAL file TONIGHT $throws __new_File(string, FileMode);

static NORMAL char* TONIGHT $throws __new_char(char);
static NORMAL byte* TONIGHT $throws __new_byte(byte);
static NORMAL bool* TONIGHT $throws __new_bool(bool);
static NORMAL int* TONIGHT $throws __new_int(int);
static NORMAL float* TONIGHT $throws __new_float(float);
static NORMAL double* TONIGHT $throws __new_double(double);
static NORMAL pstring TONIGHT $throws __new_String(pstring);
static NORMAL pointer TONIGHT $throws __new_pointer(pointer);

static NORMAL pointer TONIGHT $throws __new_memory(size_t);
static NORMAL pointer TONIGHT $throws __realloc_memory(pointer, size_t);
static INLINE size_t TONIGHT __memory_size(pointer);
static INLINE pointer TONIGHT $throws __memory_copy(pointer);
static INLINE void TONIGHT __memory_free(pointer);

static NORMAL pointer TONIGHT $throws alloc_array(size_t, int, P_retString);
static INLINE char* TONIGHT $throws __new_array_char(int);
static INLINE byte* TONIGHT $throws __new_array_byte(int);
static INLINE bool* TONIGHT $throws __new_array_bool(int);
static INLINE int* TONIGHT $throws __new_array_int(int);
static INLINE float* TONIGHT $throws __new_array_float(int);
static INLINE double* TONIGHT $throws __new_array_double(int);
static INLINE string* TONIGHT $throws __new_array_String(int);
static INLINE object* TONIGHT $throws __new_array_Object(int);
static INLINE pointer* TONIGHT $throws __new_array_pointer(int);
static INLINE pointer TONIGHT $throws __new_array_generic(size_t, int);

static NORMAL char TONIGHT char_fromString(string);
static NORMAL byte TONIGHT $throws byte_fromString(string);
static NORMAL bool TONIGHT $throws bool_fromString(string);
static NORMAL int TONIGHT $throws int_fromString(string);
static NORMAL float TONIGHT $throws float_fromString(string);
static NORMAL double TONIGHT $throws double_fromString(string);
static INLINE string TONIGHT byte_toString(byte);
static NORMAL string TONIGHT $throws string_fromDate(Time);

static NORMAL string TONIGHT String_formated(const string, ...);
static INLINE string TONIGHT String_concatenate(string, string);
static NORMAL string TONIGHT String_upper(const string);
static NORMAL string TONIGHT String_lower(const string);
static NORMAL string* TONIGHT String_split(const string, const string);
static NORMAL string TONIGHT String_trim(const string);
static NORMAL string TONIGHT String_sep(register string*, register const string);

static NORMAL pstring TONIGHT WString_formated(const pstring, ...);
static INLINE pstring TONIGHT WString_concatenate(pstring, pstring);
static NORMAL pstring TONIGHT WString_upper(const pstring);
static NORMAL pstring TONIGHT WString_lower(const pstring);
static NORMAL pstring* TONIGHT WString_split(const pstring, const pstring);
static NORMAL pstring TONIGHT WString_trim(const pstring);
static NORMAL pstring TONIGHT WString_sep(register pstring*, register const pstring);

static INLINE void TONIGHT File_close(file);
static INLINE bool TONIGHT File_end(file);
static INLINE void TONIGHT File_rewind(file);
static INLINE file TONIGHT File_stdInput(void);
static INLINE file TONIGHT File_stdOutput(void);
static INLINE file TONIGHT File_stdError(void);

static INLINE int TONIGHT Array_length(pointer);
static INLINE size_t TONIGHT Array_size(pointer);
static NORMAL pointer TONIGHT $throws Array_access(pointer, int);
static INLINE void TONIGHT Array_index(pointer, pointer, int);
static INLINE void TONIGHT Array_free(pointer);
static INLINE void TONIGHT Array_setStringMethod(pointer, P_retString);
static NORMAL string TONIGHT $throws Array_toString(pointer, string);
static NORMAL pointer TONIGHT $throws Array_convert(pointer, cast);
static NORMAL pointer TONIGHT $throws Array_where(pointer, condition);
static NORMAL bool TONIGHT $throws Array_contains(pointer, pointer);
static NORMAL void TONIGHT $throws Array_sort(pointer, pointer);
static NORMAL void TONIGHT $throws Array_forEach(pointer, pointer);

static INLINE void TONIGHT Exit_WithSuccess(void);
static INLINE void TONIGHT Exit_WithFail(void);

static INLINE int TONIGHT Collection_lenght(pointer);
static INLINE size_t TONIGHT Collection_size(pointer);
static INLINE pointer TONIGHT Collection_access(pointer, int);
static INLINE void TONIGHT Collection_index(pointer, pointer, int);

static INLINE void TONIGHT Callback_setMalloc(P_pointer);
static INLINE void TONIGHT Callback_setCalloc(P_pointer);
static INLINE void TONIGHT Callback_setRealloc(P_pointer);
static INLINE void TONIGHT Callback_setFree(P_void);

static INLINE void TONIGHT __Shared_close(pointer);
static INLINE pointer TONIGHT __Shared_open(string path);
static INLINE pointer TONIGHT __Shared_get(pointer, string);

static __ArrayInterface Array_select(pointer);
static __StringInteface String_select(pstring);
static __StringInteface WString_select(pstring);
static __FileInterface File_select(file);
