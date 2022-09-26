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

typedef struct mheader_t{
    pointer type;
    pointer value;
}mheader_t;

typedef struct{
    mheader_t *headers;
    size_t count;
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
	if (mem == NULL) Throw(NullArgumentException, "Expected non null argument");
	p_free(mem);
}

static pointer TONIGHT __new_memory(size_t q){
	MemoryData *p = p_malloc(sizeof(MemoryData) + q);
	if(!p)
		throw(MemoryAllocException, strerror(errno));
	p->size = q;
	p->headers = NULL;
	p->count = 0;
	return p->data;
}

static pointer TONIGHT __realloc_memory(pointer mem, size_t q){
	if (mem == NULL) Throw(NullArgumentException, "Expected non null argument");
	MemoryData *p = p_realloc(mem - sizeof(MemoryData), sizeof(MemoryData) + q);
	if(!p)
		throw(MemoryAllocException, strerror(errno));
	p->size = q;
	return p->data;
}

static INLINE size_t TONIGHT __memory_size(pointer mem){
	if (mem == NULL) Throw(NullArgumentException, "Expected non null argument");
	return ((MemoryData*)(mem - sizeof(MemoryData)))->size;
}

static INLINE void TONIGHT __memory_free(pointer mem){
	if(mem){
        MemoryData *md = mem - sizeof(MemoryData);
        p_free(md->headers);
        p_free(md);
	}
}

static void __memory_addHeader(pointer mem, pointer head, pointer value){
	if(mem){
        MemoryData *md = mem - sizeof(MemoryData);
        md->headers = p_realloc(md->headers, (md->count + 1) * sizeof(mheader_t));
        if(!md->headers) throw(MemoryAllocException, strerror(errno));
        md->headers[md->count ++] = (mheader_t){head, value};
	}
}

static pointer TONIGHT __memory_copy(pointer mem) {
	register size_t size = __memory_size(mem);
	register int i;
	pointer cp = __new_memory(size);
	MemoryData *d;
	if (mem == NULL) Throw(NullArgumentException, "Expected non null argument");
	d = mem - sizeof(MemoryData);
	memcpy(cp, mem, size);
	for(i = 0; i < d->count; i++)
        __memory_addHeader(cp, d->headers[i].type, d->headers[i].value);
	return cp;
}

static void __memory_removeHeader(pointer mem, pointer head){
	if(mem){
        MemoryData *md = mem - sizeof(MemoryData);
        register size_t i, j;
        for(i = 0; i < md->count; i++){
            if(md->headers[i].type == head){
                for(j = i; j < md->count - 1; j++)
                    md->headers[j] = md->headers[j + 1];
                md->count--;
            }
        }
	}
}

static pointer __memory_getHeader(pointer mem, pointer head){
	if(mem){
        MemoryData *md = mem - sizeof(MemoryData);
        register size_t i;
        for(i = 0; i < md->count; i++){
            if(md->headers[i].type == head){
                return md->headers[i].value;
            }
        }
	}
	return NULL;
}

/* Memory */
const struct __Memory Memory = {
	.alloc = __new_memory,
	.realloc = __realloc_memory,
	.size = __memory_size,
	.copy = __memory_copy,
	.free = __memory_free,
    .addHeader = __memory_addHeader,
    .removeHeader = __memory_removeHeader,
    .getHeader = __memory_getHeader,
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

static INLINE void TONIGHT Memory_select_free(void){
    __memory_free(getCurrentObject());
}

static INLINE pointer TONIGHT Memory_select_realloc(size_t q){
    return __realloc_memory(getCurrentObject(), q);
}

static INLINE size_t TONIGHT Memory_select_size(void){
    return __memory_size(getCurrentObject());
}

static INLINE pointer TONIGHT Memory_select_copy(void){
    return __memory_copy(getCurrentObject());
}

static INLINE void TONIGHT Memory_select_addHeader(pointer head, pointer value){
    return __memory_addHeader(getCurrentObject(), head, value);
}

static INLINE void TONIGHT Memory_select_removeHeader(pointer head){
    return __memory_removeHeader(getCurrentObject(), head);
}

static INLINE pointer TONIGHT Memory_select_getHeader(pointer head){
    return __memory_getHeader(getCurrentObject(), head);
}

$_interface(Memory, {
    .free = Memory_select_free,
    .realloc = Memory_select_realloc,
    .size = Memory_select_size,
    .copy = Memory_select_copy,
    .addHeader = Memory_select_addHeader,
    .removeHeader = Memory_select_removeHeader,
    .getHeader = Memory_select_getHeader
});

static char* TONIGHT __new_char(char value){
	char* c = __new_memory(sizeof(char));
	*c = value;
	return c;
}

static byte* TONIGHT __new_byte(byte value){
	byte* b = __new_memory(sizeof(byte));
	*b = value;
	return b;
}

static bool* TONIGHT __new_bool(bool value){
	bool *b = __new_memory(sizeof(bool));
	*b = value;
	return b;
}

static wchar_t* TONIGHT __new_wchar_t(wchar_t value){
	wchar_t* c = __new_memory(sizeof(wchar_t));
	*c = value;
	return c;
}

static int* TONIGHT __new_int(int value){
	int *i = __new_memory(sizeof(int));
	*i = value;
	return i;
}

static float* TONIGHT __new_float(float value){
	float *f = __new_memory(sizeof(float));
	*f = value;
	return f;
}

static double* TONIGHT __new_double(double value){
	double *d = __new_memory(sizeof(double));
	*d = value;
	return d;
}

static string* TONIGHT __new_string(string value){
	string *s = __new_memory(sizeof(string));
	*s = value;
	return s;
}

static wstring* TONIGHT __new_wstring(wstring value){
	wstring *w = __new_memory(sizeof(wstring));
	*w = value;
	return w;
}

static pointer TONIGHT __new_pointer(pointer value){
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
