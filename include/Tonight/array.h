#ifndef TONIGHT_ARRAY_H
#	define	TONIGHT_ARRAY_H

#include "collection.h"

#	ifdef __cplusplus
		extern "C"{
#	endif

#	define  ARRAY_LENGTH(array)         (sizeof array / sizeof array[0])
#	define  New_Array(type, values...)  __create_array(sizeof(type), COUNT(0, values), (type[]){values})

    extern const struct __Array{
        void (* free)(pointer);
		size_t (* length)(pointer);
		size_t (* size)(pointer);
		pointer (* access)(pointer, int);
		string (* toString)(pointer, string, P_fixString);
		pointer (* convert)(pointer, cast);
		pointer (* where)(pointer, condition);
		bool (* contains)(pointer, pointer);
		void (* sort)(pointer, pointer);
		void (* forEach)(pointer, pointer);

		char* (*Char)(size_t);
		byte* (*Byte)(size_t);
		bool* (*Bool)(size_t);
		wchar_t* (*WideChar)(size_t);
		int* (*Int)(size_t);
		float* (*Float)(size_t);
		double* (*Double)(size_t);
		string* (*String)(size_t);
		wstring* (*WideString)(size_t);
		object* (*Object)(size_t);
		pointer* (*Pointer)(size_t);
		pointer	(*Generic)(size_t, size_t);
    }Array;

    extern INLINE struct ___Array_select_data___{
        void (* free)(void);
		size_t (* length)(void);
		size_t (* size)(void);
		pointer (* access)(int);
		string (* toString)(string, P_fixString);
		pointer (* convert)(cast);
		pointer (* where)(condition);
		bool (* contains)(pointer);
		void (* sort)(pointer);
		void (* forEach)(pointer);
    }___Array_select___(pointer);

    extern pointer TONIGHT NO_CALL __create_array(size_t, size_t, pointer);

#	ifdef __cplusplus
		}
#	endif
#endif
