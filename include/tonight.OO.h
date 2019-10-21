/*
*	This file is part of the Tonight library
*
*	File: tonight.OO.h
*	This file defines the macros to use object-oriented-like programming.
*
*	Copyright (C)  2018  Thiago Fernandes Leal.
*	Permission is granted to copy, distribute and/or modify this document
*	under the terms of the GNU Free Documentation License, Version 1.3
*	or any later version published by the Free Software Foundation;
*	with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
*	A copy of the license is included in the section entitled "GNU
*	Free Documentation License".
*/

#ifndef TONIGHT_OO_MACROS
#	define	TONIGHT_OO_MACROS

#	ifndef TONIGHT_LIBRARY
#		error "Include the Tonight library"
#	endif

/*	Declare classes and interfaces	*/

#   ifdef __Define_Class__
#       undef __Define_Class__
#   endif
#	define __Define_Class__(_Class, _super, _int, _intVal)	INLINE _int ___##_Class##_select___(object obj){\
                                                                setCurrentObject(obj);\
                                                                return *___##_Class##___.implement.__interface;\
                                                            }\
                                                            static void _Class##_ctor(object obj, pointer args){\
                                                                setCurrentObject(obj);\
                                                                Method(_Class){\
                                                                    __new_##_Class(args);\
                                                                }\
                                                            }\
                                                            static INLINE void _Class##_dtor(object obj){\
                                                                setCurrentObject(obj);\
                                                                Method(_Class){\
                                                                    __del_##_Class();\
                                                                }\
                                                            }\
                                                            const struct Interface_##_Class ___##_Class##___ = {\
                                                                ._ = (const struct str_Class){\
                                                                    .name = #_Class,\
                                                                    .super = (const Class)&___##_super##___,\
                                                                    .size = sizeof(Class_##_Class),\
                                                                    .ctor = _Class##_ctor,\
                                                                    .dtor = _Class##_dtor\
                                                                },\
                                                                .__class__ = (Class)&___##_Class##___,\
                                                                .implement = (const Class_##_Class){\
                                                                    .__interface = &_intVal\
                                                                }\
                                                            };\
                                                            const Class _Class = (const Class)&___##_Class##___
#   ifdef ___class___
#       undef ___class___
#   endif
#	define ___class___(_Class, _super, _int)		typedef struct{\
                                                        Class_##_super __super;\
                                                        _int *__interface;\
                                                        struct _Class __self;\
                                                    }Class_##_Class;\
                                                    extern const struct Interface_##_Class{\
                                                        const struct str_Class _;\
                                                        const Class __class__;\
                                                        const Class_##_Class implement;\
                                                    }___##_Class##___;\
                                                    extern _int ___##_Class##_select___(object);\
                                                    extern const Class _Class
#   ifdef Class
#       undef Class
#   endif
#   ifdef Define_Class
#       undef Define_Class
#   endif
#	define Class(__args__)          ___class___(__args__)
#	define Define_Class(__args__)	__Define_Class__(__args__)

#   ifdef interface
#       undef interface
#   endif
#   ifdef __select__
#       undef __select__
#   endif
#   ifdef __structure__
#       undef __structure__
#   endif
#   ifdef $
#       undef $
#   endif
#   ifdef $$
#       undef $$
#   endif
#	define  interface(_int)			    typedef struct _int _int
#	define  __select__(_obj, _Class)	___##_Class##_select___(_obj)
#   define  __structure__(_obj, _Class) ((Class_##_Class*)((object)_obj)->data)->__self
#	define  $(_args_)				    __select__(_args_)
#	define  $$(_args_)				    __structure__(_args_)

/*	Access modifiers	*/
#   ifdef __cplusplus
#		define	Private     private
#		define	Protected   protected
#		define	Public      public
#   else
#		define	Private
#       define  private
#		define	Protected
#		define	protected
#		define	Public
#		define	public
#   endif // __cplusplus

/*	Methods	*/

#   define  Method(_class_)             __create_this_context(_class_);while(__function_this())
#   define  setInterface(_class, _int_) (((Class_##_class*)this->data)->__interface = &_int_)
#   define  getInterface(_class)        (*((Class_##_class*)this->data)->__interface)

/*	Constructor and destructor	*/

#	define Constructor(_Class, _func)	void (* __new_##_Class)(pointer) = (pointer)_func
#	define Destructor(_Class, _func)	pointer (* __del_##_Class)(void) = (pointer)_func

/*	Superclass' access	*/

#	define	superOf(_Class) 	        _Class->super
#	define	cast_super(_super)  	    (((Class_##_super*)self)->__self)

#   ifndef __cplusplus
#       define class(__args__)  ___class___(__args__)
#       define this             This
#       define new(_args...)    newInstance(_args)
#       define delete           deleteInstance
#   endif // __cplusplus

extern object This;

/* Base class */

struct IObject{
	bool (* equal)(object);
	object (* copy)(void);
	string (* toString)(void);
	wstring (* toWideString)(void);
	fixString (* toFixString)(void);
	longFixString (* toLongFixString)(void);
	fixWideString (* toFixWideString)(void);
	longFixWideString (* toLongFixWideString)(void);
};

interface(IObject);

struct Object{};

typedef struct{
	IObject *__interface;
	struct Object __self;
}Class_Object;

extern const struct Interface_Object{
	const struct str_Class _;
	const Class __class__;
	const Class_Object implement;
}___Object___;

extern IObject ___Object_select___(object);
extern const Class Object;

#endif	// ifndef TONIGHT_OO_MACROS
