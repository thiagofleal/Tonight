#include <string.h>

#include "../include/Tonight/tonight.h"

object TONIGHT new(Class class, ...){
	object _new;
	va_list v;
	va_start(v, class);
	_new = Memory.alloc(sizeof(Intern_Object));
	_new->data = Memory.alloc(class->size);
	_new->class_pointer = class;
	class->ctor(_new, &v);
	va_end(v);
	return _new;
}

void TONIGHT delete(object self){
	if(!self)
		return;
	if(self->class_pointer->dtor)
		self->class_pointer->dtor(self);
	Memory.free(self);
}

INLINE Class TONIGHT classOf(object obj){
	return obj->class_pointer;
}

bool TONIGHT isType(object obj, Class class){
	Class pClass;
	for(pClass = obj->class_pointer; pClass; pClass = pClass->super)
		if(pClass == class)
			return true;
	return false;
}

INLINE size_t TONIGHT sizeOf(object obj){
	return obj->class_pointer->size;
}

INLINE object TONIGHT copy(object obj){
	return Object.select(obj).copy();
}

bool TONIGHT compare(object a, object b){
	return Object.select(a).equal(b);
}

/* Object class */

static bool Object_equal(object obj){
	CLASS(Object);
	return self == obj ? true : false;
}

static object Object_clone(void){
	CLASS(Object);
	object ret = Memory.copy(self);
	ret->data = Memory.copy(self->data);
	return ret;
}

static string Object_toString(void){
	CLASS(Object);
	return String.formated("%s at 0x%p", self->class_pointer->name, self);
}

static retString Object_toRetString(void){
	CLASS(Object);
	retString ret;
	memcpy(ret.Text, Object.select(self).toString(), sizeof ret);
	return ret;
}

static longRetString Object_toLongRetString(void){
	CLASS(Object);
	longRetString ret;
	memcpy(ret.Text, Object.select(self).toString(), sizeof ret);
	return ret;
}

static IObject Object_vtble = {
	.equal = Object_equal,
	.copy = Object_clone,
	.toString = Object_toString,
	.toRetString = Object_toRetString,
	.toLongRetString = Object_toLongRetString
};

static bool IObject_equal(object obj){
	CLASS(Object);
	return callInterface.equal(obj);
}

static object IObject_clone(void){
	CLASS(Object);
	return callInterface.copy();
}

static string IObject_toString(void){
	CLASS(Object);
	return callInterface.toString();
}

static retString IObject_toRetString(void){
	CLASS(Object);
	return callInterface.toRetString();
}

static longRetString IObject_toLongRetString(void){
	CLASS(Object);
	return callInterface.toLongRetString();
}

static IObject iObject = {
	.equal = IObject_equal,
	.copy = IObject_clone,
	.toString = IObject_toString,
	.toRetString = IObject_toRetString,
	.toLongRetString = IObject_toLongRetString
};

static void new_Object(pointer args){
	CLASS(Object);
	setInterface(Object_vtble);
}

static void del_Object(void){
	CLASS(Object);
}

static INLINE IObject Object_select(object obj){
	setCurrentObject(obj);
	return *Object.implement.__interface;
}

static INLINE Class_Object* Object_cast(object obj){
	return obj->data;
}

static void Object_ctor(object obj, pointer args){
	setCurrentObject(obj);
	new_Object(args);
}

static void Object_dtor(object obj){
	setCurrentObject(obj);
	del_Object();
}

const struct Interface_Object Object = {
	._ = (const struct str_Class){
		.name = "Object",
		.super = NULL,
		.size = sizeof(Class_Object),
		.ctor = Object_ctor,
		.dtor = Object_dtor
	},
	.class = (Class)&Object,
	.implement = (const Class_Object){
		.__interface = &iObject
	},
	.select = Object_select,
	.cast = Object_cast
};
