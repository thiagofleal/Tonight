/*
*	This file is part of the Tonight library
*
*	File: tonight.def.h
*	This file defines the types and data structures.
*
*	Copyright (C)  2019  Thiago Fernandes Leal.
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
#		error "Include the Tonight library"
#	endif

#	define	TONIGHT
#	define	NO_CALL

/* Definitions */
#	define main	__main__

#	define  ARRAY    *
#	define  $Empty(Type)	((Type){0})
#	define  $end			((string)0)
#	define  getText(str)    &(((str).Text)[0])

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

#	define SELECT(_ind, values...)	((int)((pointer[]){values})[_ind])

#   define _P_(arg) (pointer)arg
#	define DOWN_10	_P_(10), _P_( 9), _P_( 8), _P_( 7), _P_( 6), _P_( 5), _P_( 4), _P_( 3), _P_( 2), _P_( 1), 0
#	define DOWN_20	_P_(20), _P_(19), _P_(18), _P_(17), _P_(16), _P_(15), _P_(14), _P_(13), _P_(12), _P_(11), DOWN_10
#	define DOWN_30	_P_(30), _P_(29), _P_(28), _P_(27), _P_(26), _P_(25), _P_(24), _P_(23), _P_(22), _P_(21), DOWN_20
#	define DOWN_40	_P_(40), _P_(39), _P_(38), _P_(37), _P_(36), _P_(35), _P_(34), _P_(33), _P_(32), _P_(31), DOWN_30
#	define DOWN_50	_P_(50), _P_(49), _P_(48), _P_(47), _P_(46), _P_(45), _P_(44), _P_(43), _P_(42), _P_(41), DOWN_40

#	define COUNT(arg, args...)          SELECT(50 + arg, args, DOWN_50)

#	ifdef __cplusplus
#		define OptionalArgs	...
#	else
#		define OptionalArgs
#	endif

#   define first(a, b...)               a
#   define second(a, b, c...)           b
#   define third(a, b, c, d...)         c
#   define fourth(a, b, c, d, e...)     d
#   define fifth(a, b, c, d, e, f...)   e

#	define	__using__(var, args...)         __create_using_context(sizeof var, &var);\
											var = first(args);\
											while(__function_using(&var, second(args, NULL)))
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
																		*(typeTo*)to = (typeTo)(*(typeFrom*)from);\
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

#   define $_add(_Class, _int)          extern INLINE struct ___##_Class##_select_data___ _int* ___##_Class##_select___(pointer)
#   define $_interface(_Class, _int...) static struct ___##_Class##_select_data___ __##_Class_##_data = _int;\
                                        INLINE struct ___##_Class##_select_data___* ___##_Class##_select___(pointer instance){\
                                            setCurrentObject(instance);\
                                            return &__##_Class_##_data;\
                                        };
#define function(ret, body)   (ret(*)())({ret __f__ body __f__;})

#ifndef FIX_LENGTH
#   define FIX_LENGTH 100
#endif
#ifndef LONG_FIX_LENGTH
#   define LONG_FIX_LENGTH 1000
#endif

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
		char Text[FIX_LENGTH + 1];
	}fixString;

	typedef struct{
		char Text[LONG_FIX_LENGTH + 1];
	}longFixString;

	typedef struct{
		wchar_t Text[FIX_LENGTH + 1];
	}fixWideString;

	typedef struct{
		wchar_t Text[LONG_FIX_LENGTH + 1];
	}longFixWideString;

	typedef fixString (*P_fixString)(OptionalArgs);
	typedef longFixString (*P_longFixString)(OptionalArgs);

	typedef fixWideString (*P_fixWideString)(OptionalArgs);
	typedef longFixWideString (*P_longFixWideString)(OptionalArgs);

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

#endif
