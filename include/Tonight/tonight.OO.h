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
#		error "Include the Tonight library with #include<Tonight/tonight.h>"
#	endif

#	ifndef __cplusplus

/*	Declare classes and interfaces	*/

#		define __Define_Class__(_Class, _super, _int, _intVal)	static INLINE _int _Class##_select(object obj){\
																	setCurrentObject(obj);\
																	return *_Class.implement.__interface;\
																}\
																static INLINE void _Class##_ctor(object obj, pointer args){\
																	setCurrentObject(obj);\
																	__new_##_Class(args);\
																}\
																static INLINE void _Class##_dtor(object obj){\
																	setCurrentObject(obj);\
																	__del_##_Class();\
																}\
																const struct Interface_##_Class _Class = {\
																	._ = (const struct str_Class){\
																		.name = #_Class,\
																		.super = (const Class)&_super,\
																		.size = sizeof(Class_##_Class),\
																		.ctor = _Class##_ctor,\
																		.dtor = _Class##_dtor\
																	},\
																	.class = (Class)&_Class,\
																	.implement = (const Class_##_Class){\
																		.__interface = &_intVal\
																	},\
																	.select = _Class##_select\
																}
#		define __class__(_Class, _super, _int)			typedef struct{\
															Class_##_super __super;\
															_int *__interface;\
															struct _Class __self;\
														}Class_##_Class;\
														extern const struct Interface_##_Class{\
															const struct str_Class _;\
															const Class class;\
															const Class_##_Class implement;\
															_int (*select)(object);\
														}_Class

#		define class(__args__)	__class__(__args__)
#		define Define_Class(__args__)	__Define_Class__(__args__)

#		define interface(_int)			typedef struct _int _int
#		define __select__(_obj, _Class)	_Class.select(_obj)
#		define $(_args_)				__select__(_args_)

/*	Access modifiers	*/

#		define	private
#		define	protected
#		define	public

/*	Methods	*/

#		define CLASS(_Class)	object self=getCurrentObject();\
								Class_##_Class *This = self->data
#		define CHECK_CLASS(_Class)	object self=checkCurrentObject(_Class.class);\
									checkArgumentPointer(self);\
									Class_##_Class *This = self->data
#		define this							(This->__self)
#		define constructArg(type)			(va_arg(__construct_args->list, type))
#		define getInterface							(*This->__interface)
#		define setInterface(_new)					(This->__interface = &_new)
#		define getClassInterface(_class)			(*((Class_##_class*)self)->__interface)
#		define setClassInterface(_class, _new)		(((Class_##_class*)self)->__interface = &new)
#		define cast(_super)							(((Class_##_class*)self)->__self)

/*	Constructor and destructor	*/

#		define Constructor(_Class)	void __new_##_Class(ConstructArgs __construct_args)
#		define Destructor(_Class)	void __del_##_Class(void)

/*	Superclass' access	*/

#		define	super(_act_)						super_##_act_(self->class_pointer->super)
#		define	super_construct(_super)				(_super)->ctor(self, __construct_args)
#		define	super_delete(_super)				(_super)->dtor(self)

typedef struct ConstructArgs{
	va_list list;
}*ConstructArgs;

/*	new and delete	*/
extern object TONIGHT new(Class, ...);
extern void TONIGHT delete(object);

extern Class TONIGHT classOf(object);
extern bool TONIGHT isType(object, Class);
extern size_t TONIGHT sizeOf(object);
extern object TONIGHT copy(object);
extern bool TONIGHT compare(object, object);

/* Base class */

struct IObject{
	bool (* equal)(object);
	object (* copy)(void);
	string (* toString)(void);
	retString (* toRetString)(void);
	longRetString (* toLongRetString)(void);
};

interface(IObject);

struct Object{};

typedef struct{
	IObject *__interface;
	struct Object __self;
}Class_Object;

extern const struct Interface_Object{
	const struct str_Class _;
	const Class class;
	const Class_Object implement;
	IObject (*select)(object);
}Object;

INLINE void TONIGHT setCurrentObject(object);
INLINE object TONIGHT getCurrentObject(void);
INLINE object TONIGHT checkCurrentObject(Class);

#	endif	// ifndef __cplusplus
#endif	// ifndef TONIGHT_OO_MACROS
