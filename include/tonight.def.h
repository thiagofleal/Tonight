/*
*	This file is part of the Tonight library
*
*	File: tonight.def.h
*	This file defines the types and data structures.
*
*	Copyright (C)  2018  Thiago Fernandes Leal.
*	Permission is granted to copy, distribute and/or modify this document
*	under the terms of the GNU Free Documentation License, Version 1.3
*	or any later version published by the Free Software Foundation;
*	with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
*	A copy of the license is included in the section entitled "GNU
*	Free Documentation License".
*/

#ifndef TONIGHT_DEFINITIONS
#	define TONIGHT_DEFINITIONS

#	ifndef TONIGHT_LIBRARY
#		error "Include the Tonight library with #include<Tonight/tonight.h>"
#	endif

#	define	TONIGHT
#	define	NO_CALL

/* Definitions */
#	ifdef _WIN32
#		define key_right	295
#		define key_left		293
#		define key_up		294
#		define key_down		296
#		define key_ESC		27
#		define key_ENTER	13
#		define key_SPACE	32
#		define key_BS		8
#	else
#		define key_right	185
#		define key_left		186
#		define key_up		183
#		define key_down		184
#		define key_ESC		27
#		define key_ENTER	10
#		define key_SPACE	32
#		define key_BS		127
#	endif

#	define main	__main__

#	define  ARRAY    *
#	define  $Empty(Type)	((Type){0})
#	define  $end			((string)0)
#	define  getText(str) ((string)&((str).Text)[0])

#	ifndef __cplusplus
#		define and      &&
#		define or       ||
#		define using	Using
#       define with     With
#	endif

#	if (defined __GNUC_GNU_INLINE__ || defined __cplusplus)
#		define INLINE	inline
#	else
#		define INLINE
#		define inline
#	endif

#	define NORMAL

#	define SELECT(_ind, values...)	((int[]){values})[_ind]

#	define DOWN_10	10,  9,  8,  7,  6,  5,  4,  3,  2,  1, 0
#	define DOWN_20	20, 19, 18, 17, 16, 15, 14, 13, 12, 11, DOWN_10
#	define DOWN_30	30, 29, 28, 27, 26, 25, 24, 23, 22, 21, DOWN_20
#	define DOWN_40	40, 39, 38, 37, 36, 35, 34, 33, 32, 31, DOWN_30
#	define DOWN_50	50, 49, 48, 47, 46, 45, 44, 43, 42, 41, DOWN_40

#	define COUNT(arg, args...)          SELECT(50 + arg, args, DOWN_50)

#	ifdef __cplusplus
#		define OptionalArgs	...
#	else
#		define OptionalArgs
#	endif

#   define first(a, b...)          a
#   define second(a, b, c...)      b
#   define third(a, b, c, d...)    c
#   define __import__(name, space...)  __##name##_set second(space, name) = first(space)->name
#   define import(args...) __import__(args)

#	define	__using__(var, from, iFree...)	__create_using_context(sizeof var, &var);\
											var = from;\
											while(__function_using(&var, ((IFree){iFree}).free))
#	define Using(_arg_)						__using__(_arg_)

#	define	With(var)	__create_with_context(var);\
                        while(__function_with())

#	define __DefineCast__(_cast, typeFrom, typeTo, _arg...)	static void _cast##_##cast\
															(pointer from, pointer to){\
																*(typeTo*)to = (typeTo)(*(typeFrom*)from);\
															}\
															_arg cast _cast = (cast){\
																sizeof(typeFrom),\
																sizeof(typeTo),\
																_cast##_##cast\
															}
#	define DefineCast(__args__)	__DefineCast__(__args__)

#	define __DefineCastPointer__(_cast, typeFrom, typeTo, _arg...)	static void _cast##_##cast\
																	(pointer from, pointer to){\
																		*(typeTo*)to = (typeTo)(**(typeFrom*)from);\
																	}\
																	_arg cast _cast = (cast){\
																		sizeof(typeFrom),\
																		sizeof(typeTo),\
																		_cast##_##cast\
																	}
#	define DefineCastPointer(__args__)	__DefineCastPointer__(__args__)

#	define	__Cast__(typeFrom, typeTo)	(cast)({\
											void _cast(pointer from, pointer to){\
												*(typeTo*)to = (typeTo)(*(typeFrom*)from);\
											}\
											(cast){\
												sizeof(typeFrom),\
												sizeof(typeTo),\
												_cast\
											};\
										})
#	define	Cast(args)	__Cast__(args)

#	define	__CastPointer__(typeFrom, typeTo)	(cast)({\
													void _cast(pointer from, pointer to){\
														*(typeTo*)to = (typeTo)(**(typeFrom*)from);\
													}\
													(cast){\
														sizeof(typeFrom),\
														sizeof(typeTo),\
														_cast\
													};\
												})
#	define	CastPointer(args)	__CastPointer__(args)

#	define __CONDITION__(_name, _arg, _type, _cond)	inline bool _name(pointer __arg__){\
														_type _arg = *(_type*)__arg__;\
														return _cond ? true : false;\
													}
#	define DeclareCondition(args)	__CONDITION__(args)

#	define __Condition__(arg, type, cond)	(condition)({\
												bool __cond__(pointer __arg__){\
													type arg = *(type*)__arg__;\
													return cond ? true : false;\
												}\
												__cond__;\
											})
#	define Condition(args)	__Condition__(args)

#	define $in			,
#	define $as			,
#	define $with		,
#	define $where		,
#	define $from		,
#	define $extends		,
#	define $implements	,

#   define $va_set(var, __data__)   struct __data__ *__args__ = (pointer)var
#   define $va_get                  (*__args__)

/* data types definitions */
#	ifndef __cplusplus
		typedef unsigned char bool;
#		define true	0x1
#		define false	0x0
#	endif
	typedef unsigned char uchar, byte;
	typedef	char *string;
	typedef	wchar_t *wstring;
	typedef void *pointer;
	typedef struct __file__ *file;
	typedef struct str_Intern_Object	Intern_Object, *object;
	typedef void (*P_void)	(OptionalArgs);
	typedef char (*P_char)	(OptionalArgs);
	typedef bool (*P_bool)	(OptionalArgs);
	typedef int (*P_int)	(OptionalArgs);
	typedef float (*P_float)	(OptionalArgs);
	typedef double (*P_double)	(OptionalArgs);
	typedef char* (*P_string)	(OptionalArgs);
	typedef void* (*P_pointer)(OptionalArgs);
	typedef object (*P_object)	(OptionalArgs);

	typedef struct{
		char Text[101];
	}fixString;

	typedef struct{
		char Text[1001];
	}longFixString;

	typedef struct{
		wchar_t Text[101];
	}fixWideString;

	typedef struct{
		wchar_t Text[1001];
	}longFixWideString;

	typedef fixString (*P_fixString)(OptionalArgs);
	typedef longFixString (*P_longFixString)(OptionalArgs);

	typedef fixWideString (*P_fixWideString)(OptionalArgs);
	typedef longFixWideString (*P_longFixWideString)(OptionalArgs);

	typedef struct tm* Time;
	typedef Time (*P_Time)(OptionalArgs);

	/* Objects structs */
	typedef struct str_Class *Class;

	struct str_Class{
		const string name;
		const Class super;
		const size_t size;
		void (* ctor)(object, pointer);
		void (* dtor)(object);
	};

	struct str_Intern_Object{
		pointer data;
		Class class_pointer;
	};

	/* cast */
	typedef struct{
		size_t original;
		size_t result;
		void (* parse)(pointer, pointer);
	}cast, (* P_cast)(OptionalArgs);

	typedef bool (* condition)(pointer);

	/* Class Timer */
	typedef struct Timer{
		Time (*getTime)(OptionalArgs);
		int (*hours)(OptionalArgs);
		int (*minutes)(OptionalArgs);
		int (*seconds)(OptionalArgs);
		int (*month)(OptionalArgs);
		int (*day_month)(OptionalArgs);
		int (*day_week)(OptionalArgs);
		int (*day_year)(OptionalArgs);
		int (*year)(OptionalArgs);
	}Timer;

	/* Conversor */
	typedef struct __Conversor_set{
		char (*toChar)(string);
		byte (*toByte)(string);
		bool (*toBool)(string);
		int (*toInt)(string);
		float (*toFloat)(string);
		double (*toDouble)(string);
		string (*fromChar)(char);
		string (*fromByte)(byte);
		string (*fromBool)(bool);
		string (*fromInt)(int);
		string (*fromFloat)(float);
		string (*fromDouble)(double);
		string (*fromTime)(Time);
	}*__Conversor_set;

	typedef struct{
		void (* free)(OptionalArgs);
	}IFree;

	struct __WideString{
		void (* free)(wstring);
		wstring (* formated)(const wstring, ...);
		wstring (* copy)(wstring);
		wstring (* concatenate)(wstring, wstring);
		wstring (* upper)(const wstring);
		wstring (* lower)(const wstring);
		wstring (* trim)(const wstring);
		wstring (* sep)(wstring*, const wstring);
		wstring* (* split)(const wstring, const wstring);
		size_t (* length)(const wstring);
		int (* compare)(const wstring, const wstring);
		string (* toString)(const wstring);
		wstring (* toWide)(const wstring);
	};

	/* Keys */
	struct __Key{
		int Right;
		int Left;
		int Up;
		int Down;
		int Escape;
		int Enter;
		int Space;
		int BackSpace;
	};

	/* Exit codes */
	struct __Exit{
		int Success;
		int Failure;
		void (* With)(int);
		void (* WithSuccess)(void);
		void (* WithFail)(void);
	};

	/* Constructors */
	struct __New{
		object (*Object)(Class, ...);

		char* (*Char)(char);
		byte* (*Byte)(byte);
		bool* (*Bool)(bool);
		int* (*Int)(int);
		float* (*Float)(float);
		double* (*Double)(double);
		string* (*String)(string);
		pointer (*Pointer)(pointer);
	};

#endif
