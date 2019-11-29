#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/tonight.h"
#include "../include/Tonight/exceptions.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/array.h"
#include "../include/Tonight/string.h"
#include "../include/Tonight/test.h"

typedef struct{
	size_t length;
	size_t size;
	ICollection *collection;
	byte data[0];
}ArrayData;

static NORMAL pointer TONIGHT $throws alloc_array(size_t, size_t);
static INLINE char* TONIGHT $throws __new_array_char(size_t);
static INLINE byte* TONIGHT $throws __new_array_byte(size_t);
static INLINE bool* TONIGHT $throws __new_array_bool(size_t);
static INLINE int* TONIGHT $throws __new_array_int(size_t);
static INLINE float* TONIGHT $throws __new_array_float(size_t);
static INLINE double* TONIGHT $throws __new_array_double(size_t);
static INLINE string* TONIGHT $throws __new_array_String(size_t);
static INLINE object* TONIGHT $throws __new_array_Object(size_t);
static INLINE pointer* TONIGHT $throws __new_array_pointer(size_t);
static INLINE pointer TONIGHT $throws __new_array_generic(size_t, size_t);

/* Functions to Array */
static INLINE size_t TONIGHT Array_length(pointer array){
	Test.checkPointer(array);
	return ((ArrayData*)(array - sizeof(ArrayData)))->length;
}

static INLINE size_t TONIGHT Array_size(pointer array){
	Test.checkPointer(array);
	return ((ArrayData*)(array - sizeof(ArrayData)))->size;
}

static INLINE pointer TONIGHT $throws Array_access(pointer array, int index){
	if(index < 0 || index >= Array_length(array))
        throw(ArrayIndexBoundException, "Index out of array bounds");
	return array + index * Array_size(array);
}

static INLINE void TONIGHT Array_index(pointer array, pointer var, int index){
	*(int*)var = index;
}

static INLINE void TONIGHT Array_free(pointer array){
	if(array) Memory.Callback.free(array - sizeof(ArrayData));
}

static string TONIGHT Array_toString(pointer array, string sep, P_fixString method){
	register int i, length = Array_length(array);
	char ARRAY str = __new_array_char((Array_size(array) * 3 + strlen(sep)) * length);
	string ret;
	if(!length)
		return toString("");
	*str = 0;
	for(i=0; i<length; i++)
		strcat(strcat(str, getText(method(Array_access(array, i)))), sep);
	str[strlen(str) - strlen(sep)] = 0;
	ret = toString(str);
	Array_free(str);
	return ret;
}

static pointer TONIGHT Array_convert(pointer array, cast casting){
	register int i, length=Array_length(array);
	pointer ret = __new_array_generic(casting.result, length);
	for(i=0;i<length;i++)
		casting.parse(Array_access(array, i), Array_access(ret, i));
	return ret;
}

static pointer TONIGHT $throws Array_where(pointer array, condition where){
	register size_t i, j, length=Array_length(array), size=Array_size(array);
	pointer ret=NULL, aux, arr=__new_array_generic(size,length);
	for(i=0, j=0; i<length; i++){
		aux=Array_access(array,i);
		if(where(aux)){
			memcpy(Array_access(arr,j), aux, size);
			j++;
		}
	}
	ret = __new_array_generic(size,j);
	for(i=0; i<j; i++)
		memcpy(Array_access(ret,i),Array_access(arr,i),size);
	Array_free(arr);
	return ret;
}

static bool TONIGHT $throws Array_contains(pointer array, pointer sub){
	register size_t array_lenth=Array_length(array);
	register size_t sub_lenth=Array_length(sub);
	register size_t array_size=Array_size(array);
	register size_t sub_size=Array_size(sub);
	register size_t i,j;
	if(array_size!=sub_size)
		return false;
	for(i=0;i<sub_lenth;i++){
		bool part=false;
		for(j=0;j<array_lenth;j++)
			if(!memcmp(Array_access(sub,i),Array_access(array,j),array_size))
				part=true;
		if(!part)
			return false;
	}
	return true;
}

static void TONIGHT $throws Array_sort(pointer array, pointer function){
    register size_t size = Array_size(array),length = Array_length(array);
    qsort(array, length, size, function);
}

static void TONIGHT $throws Array_forEach(pointer array, pointer function){
    register size_t i, length = Array_length(array);
    for(i=0;i<length;i++){
        ((P_void)function)(Array_access(array,i));
    }
}

/* Initialize arrays */
static ICollection __Array_collection = {
	.length = Array_length,
	.size = Array_size,
	.access = Array_access,
	.index = Array_index
};

static pointer TONIGHT $throws alloc_array(size_t size, size_t lenght){
	ArrayData *p = Memory.Callback.malloc(sizeof(ArrayData) + size * lenght);
	if(!p)
		throw(MemoryAllocException, strerror(errno));
	p->length = lenght;
	p->size = size;
	p->collection = &__Array_collection;
	return p->data;
}

pointer TONIGHT NO_CALL __create_array(size_t size, size_t length, pointer array){
	pointer ret = __new_array_generic(size, length);
	register int i;
	for(i=0; i<length; i++)
		memcpy(Array_access(ret, i), array + i * size, size);
	return ret;
}

static INLINE char* TONIGHT $throws __new_array_char(size_t q){
	return alloc_array(sizeof(char), q);
}

static INLINE byte* TONIGHT $throws __new_array_byte(size_t q){
	return alloc_array(sizeof(byte), q);
}

static INLINE bool* TONIGHT $throws __new_array_bool(size_t q){
	return alloc_array(sizeof(bool), q);
}

static INLINE wchar_t* TONIGHT $throws __new_array_wchar(size_t q){
	return alloc_array(sizeof(wchar_t), q);
}

static INLINE int* TONIGHT $throws __new_array_int(size_t q){
	return alloc_array(sizeof(int), q);
}

static INLINE float* TONIGHT $throws __new_array_float(size_t q){
	return alloc_array(sizeof(float), q);
}

static INLINE double* TONIGHT $throws __new_array_double(size_t q){
	return alloc_array(sizeof(double), q);
}

static INLINE string* TONIGHT $throws __new_array_String(size_t q){
	return alloc_array(sizeof(string), q);
}

static INLINE wstring* TONIGHT $throws __new_array_Wstring(size_t q){
	return alloc_array(sizeof(wstring), q);
}

static INLINE object* TONIGHT $throws __new_array_Object(size_t q){
	return alloc_array(sizeof(object), q);
}

static INLINE pointer* TONIGHT $throws __new_array_pointer(size_t q){
	return alloc_array(sizeof(pointer), q);
}

static INLINE pointer TONIGHT $throws __new_array_generic(size_t size, size_t q){
	return alloc_array(size, q);
}

/* Array */
const struct __Array Array = {
	.length = Array_length,
	.size = Array_size,
	.access = Array_access,
	.free = Array_free,
	.toString = Array_toString,
	.convert = Array_convert,
	.where = Array_where,
	.contains = Array_contains,
	.sort = Array_sort,
    .forEach = Array_forEach,

	.Char = __new_array_char,
	.Byte = __new_array_byte,
	.Bool = __new_array_bool,
	.WideChar = __new_array_wchar,
	.Int = __new_array_int,
	.Float = __new_array_float,
	.Double = __new_array_double,
	.String = __new_array_String,
	.WideString = __new_array_Wstring,
	.Object = __new_array_Object,
	.Pointer = __new_array_pointer,
	.Generic = __new_array_generic
};

/* $(<array> $as Array) */
static INLINE size_t TONIGHT Array_select_length(void){
	return Array_length(getCurrentObject());
}

static INLINE size_t TONIGHT Array_select_size(void){
	return Array_size(getCurrentObject());
}

static INLINE pointer TONIGHT $throws Array_select_access(int index){
	return Array_access(getCurrentObject(), index);
}

static INLINE void TONIGHT Array_select_free(void){
	Array_free(getCurrentObject());
}

static INLINE string TONIGHT Array_select_toString(string sep, P_fixString method){
	return Array_toString(getCurrentObject(), sep, method);
}

static INLINE pointer TONIGHT Array_select_convert(cast casting){
	return Array_convert(getCurrentObject(), casting);
}

static INLINE pointer TONIGHT $throws Array_select_where(condition where){
	return Array_where(getCurrentObject(), where);
}

static INLINE bool TONIGHT $throws Array_select_contains(pointer sub){
	return Array_contains(getCurrentObject(), sub);
}

static INLINE void TONIGHT $throws Array_select_sort(pointer function){
    Array_sort(getCurrentObject(), function);
}

static INLINE void TONIGHT $throws Array_select_forEach(pointer function){
    Array_forEach(getCurrentObject(), function);
}

/* ___Array_select___ */
$_interface(Array, {
	.length = Array_select_length,
	.size = Array_select_size,
	.access = Array_select_access,
	.free = Array_select_free,
	.toString = Array_select_toString,
	.convert = Array_select_convert,
	.where = Array_select_where,
	.contains = Array_select_contains,
	.sort = Array_select_sort,
    .forEach = Array_select_forEach
});
