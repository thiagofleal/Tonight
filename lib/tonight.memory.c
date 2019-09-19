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
