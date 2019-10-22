#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../include/tonight.h"
#include "../include/Tonight/exceptions.h"
#include "../include/Tonight/memory.h"

static P_pointer p_malloc = malloc;
static P_pointer p_calloc = calloc;
static P_pointer p_realloc = realloc;
static P_void p_free = free;

typedef struct{
	size_t size;
	byte data[0];
}MemoryData;

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

static INLINE pointer TONIGHT Callback_malloc(size_t size){
	return p_malloc(size);
}

static INLINE pointer TONIGHT Callback_calloc(size_t size, size_t length){
	return p_calloc(size, length);
}

static INLINE pointer TONIGHT Callback_realloc(pointer mem, size_t size){
	return p_realloc(mem, size);
}

static INLINE void TONIGHT Callback_free(pointer mem){
	p_free(mem);
}

static pointer TONIGHT $throws __new_memory(size_t q){
	MemoryData *p = p_malloc(sizeof(MemoryData) + q);
	if(!p)
		throw(MemoryAllocException, strerror(errno));
	p->size = q;
	return p->data;
}

static pointer TONIGHT $throws __realloc_memory(pointer mem, size_t q){
	MemoryData *p = p_realloc(mem - sizeof(MemoryData), sizeof(MemoryData) + q);
	if(!p)
		throw(MemoryAllocException, strerror(errno));
	p->size = q;
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

/* Memory */
const struct __Memory Memory = {
	.alloc = __new_memory,
	.realloc = __realloc_memory,
	.size = __memory_size,
	.copy = __memory_copy,
	.free = __memory_free,
	.Callback = {
        .setMalloc = Callback_setMalloc,
        .setCalloc = Callback_setCalloc,
        .setRealloc = Callback_setRealloc,
        .setFree = Callback_setFree,
        .malloc = Callback_malloc,
        .calloc = Callback_calloc,
        .realloc = Callback_realloc,
        .free = Callback_free
    }
};

static char* TONIGHT $throws __new_char(char value){
	char* c = __new_memory(sizeof(char));
	*c = value;
	return c;
}

static byte* TONIGHT $throws __new_byte(byte value){
	byte* b = __new_memory(sizeof(byte));
	*b = value;
	return b;
}

static bool* TONIGHT $throws __new_bool(bool value){
	bool *b = __new_memory(sizeof(bool));
	*b = value;
	return b;
}

static wchar_t* TONIGHT $throws __new_wchar_t(wchar_t value){
	wchar_t* c = __new_memory(sizeof(wchar_t));
	*c = value;
	return c;
}

static int* TONIGHT $throws __new_int(int value){
	int *i = __new_memory(sizeof(int));
	*i = value;
	return i;
}

static float* TONIGHT $throws __new_float(float value){
	float *f = __new_memory(sizeof(float));
	*f = value;
	return f;
}

static double* TONIGHT $throws __new_double(double value){
	double *d = __new_memory(sizeof(double));
	*d = value;
	return d;
}

static string* TONIGHT $throws __new_string(string value){
	string *s = __new_memory(sizeof(string));
	*s = value;
	return s;
}

static wstring* TONIGHT $throws __new_wstring(wstring value){
	wstring *w = __new_memory(sizeof(wstring));
	*w = value;
	return w;
}

static pointer TONIGHT $throws __new_pointer(pointer value){
	pointer *p = __new_memory(sizeof(pointer));
	*p = value;
	return p;
}

const struct __InstanceOf InstanceOf = {
    .Char = __new_char,
    .Byte = __new_byte,
    .Bool = __new_bool,
    .WideChar = __new_wchar_t,
    .Int = __new_int,
    .Float = __new_float,
    .Double = __new_double,
    .String = __new_string,
    .WideString = __new_wstring,
    .Pointer = __new_pointer
};
