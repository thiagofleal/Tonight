#include <string.h>

#include "../include/Tonight/tonight.h"

object TONIGHT new(Class class, ...){
	object _new;
	va_list args;
	va_start(args, class);
	_new = Memory.alloc(sizeof(Intern_Object));
	_new->data = Memory.alloc(class->size);
	_new->class_pointer = class;
	class->ctor(_new, &args);
	va_end(args);
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
	CHECK_CLASS(Object);
	return getInterface.equal(obj);
}

static object IObject_clone(void){
	CHECK_CLASS(Object);
	return getInterface.copy();
}

static string IObject_toString(void){
	CHECK_CLASS(Object);
	return getInterface.toString();
}

static retString IObject_toRetString(void){
	CHECK_CLASS(Object);
	return getInterface.toRetString();
}

static longRetString IObject_toLongRetString(void){
	CHECK_CLASS(Object);
	return getInterface.toLongRetString();
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
	.select = Object_select
};

/* Set */

static int Set_ICollection_length(pointer collect){
	return $(collect $as Set).getCollection()->length(collect);
}

static size_t Set_ICollection_size(pointer collect){
	return $(collect $as Set).getCollection()->size(collect);
}

static pointer Set_ICollection_access(pointer collect, int index){
	return $(collect $as Set).getCollection()->access(collect, index);
}

static ICollection Set_ICollection = {
	.length = Set_ICollection_length,
	.size = Set_ICollection_size,
	.access = Set_ICollection_access
};

static ICollection * Set_getCollection(void){
	CLASS(Set);
	return this.collection;
}

static void Set_setCollection(ICollection value){
	CLASS(Set);
	*this.collection = value;
}

static ISet Set_vtble = {
	.getCollection = Set_getCollection,
	.setCollection = Set_setCollection
};

static Constructor(Set){
	CLASS(Set);
	static ICollection _default;
	construct(super());
	_default = *getICollection(self);
	this.collection = Memory.alloc(sizeof _default);
	*this.collection = _default;
	setInterface(Set_vtble);
	*getICollection(self) = Set_ICollection;
}

static Destructor(Set){
	CLASS(Set);
	Memory.free(this.collection);
}

static ICollection * ISet_getCollection(void){
	CHECK_CLASS(Set);
	return getInterface.getCollection();
}

static void ISet_setCollection(ICollection value){
	CHECK_CLASS(Set);
	getInterface.setCollection(value);
}

static ISet iSet = {
	.getCollection = ISet_getCollection,
	.setCollection = ISet_setCollection
};

Define_Class(Set $extends Object $implements ISet $as iSet);
