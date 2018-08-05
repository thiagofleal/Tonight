/*
*	This file is part of the Tonight library
*	
*	File: tonightOO.h
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
#		error "Include the Tonight library (tonight.h)"
#	endif

#	ifndef __cplusplus

/*	Declare classes and interfaces	*/

#		ifdef Define_Class
#			undef Define_Class
#		endif
#		ifdef class
#			undef class
#		endif
#		ifdef interface
#			undef interface
#		endif

#		define Define_Class(_Class)	struct str_Class class_##_Class = {sizeof(struct _Class), __new_##_Class, __del_##_Class};Class_Name _Class = &class_##_Class
#		define class(_Class)	Class_Name _Class
#		define interface(_int)	typedef struct _int _int

/*	Access modifiers	*/

#		ifdef private
#			undef private
#		endif
#		ifdef protected
#			undef protected
#		endif
#		ifdef public
#			undef public
#		endif

#		define private
#		define	protected
#		define	public

/*	Inheritance	*/

#		ifdef extend
#			undef extend
#		endif
#		ifdef implement
#			undef implement
#		endif

#		define extend(_father)	struct _father __super
#		define implement(_int)	_int *__Int_##_int

/*	Methods	*/

#		ifdef INTERN_METHOD
#			undef INTERN_METHOD
#		endif
#		ifdef CLASS
#			undef CLASS
#		endif
#		ifdef this
#			undef this
#		endif
#		ifdef nextConstrArg
#			undef nextConstrArg
#		endif
#		ifdef setInterface
#			undef setInterface
#		endif
#		ifdef getInterface
#			undef getInterface
#		endif

#		define INTERN_METHOD	Intern_Object *self
#		define CLASS(_Class)	struct _Class *This = self->obj
#		define this	(*This)
#		define nextConstrArg(type)	(__builtin_va_arg(*__construct_args, type))
#		define setInterface(_int, _value)	This->__Int_##_int = &_value
#		define getInterface(_int)	(*This->__Int_##_int)

/*	Constructor and destructor	*/

#		ifdef Constructor
#			undef Constructor
#		endif
#		ifdef Destructor
#			undef Destructor
#		endif

#		define Constructor(Class)	void __new_##Class(Intern_Object *self, __builtin_va_list *__construct_args)
#		define Destructor(Class)	void __del_##Class(Intern_Object *self)

/*	Superclass' access	*/

#		ifdef super
#			undef super
#		endif
#		ifdef super_init
#			undef super_init
#		endif
#		ifdef super_delete
#			undef super_delete
#		endif
#		ifdef super_getInterface
#			undef super_getInterface
#		endif
#		ifdef super_setInterface
#			undef super_setInterface
#		endif

#		define super	This->__super
#		define	super_init(_super)	_super->ctor(self, __construct_args)
#		define	super_delete(_super)	_super->dtor(self)
#		define	super_getInterface(_super, _int)	(*((struct _super*)This)->__Int_##_int)
#		define	super_setInterface(_super, _int, _new)	(((struct _super*)This)->__Int_##_int = &_new)

/*	delete(obj)	*/

void delete(Object);

#	endif	// ifndef __cplusplus
#endif	// ifndef TONIGHT_OO_MACROS
