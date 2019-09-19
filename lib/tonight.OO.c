#include <string.h>

#include "../include/tonight.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/collection.h"

object This = NULL;

struct objectAdditionalData{
    ICollection *collection;
};

object TONIGHT newInstance(const Class class, ...){
    object _new = Memory.alloc(sizeof(struct objectAdditionalData) + sizeof(Intern_Object));
	va_list args;
	va_start(args, class);
	((struct objectAdditionalData*)_new)->collection = NULL;
	_new = (pointer)_new + sizeof(struct objectAdditionalData);
	_new->data = Memory.alloc(class->size);
	_new->class_pointer = class;
	class->ctor(_new, args);
	va_end(args);
	return _new;
}

extern void TONIGHT construct(const Class class, ...){
	va_list args;
	va_start(args, class);
	class->ctor(this, args);
	va_end(args);
}

void TONIGHT deleteInstance(object self){
	if(!self) return;
    if(!self->class_pointer) return;
    if(self->class_pointer->dtor) self->class_pointer->dtor(self);
    self->class_pointer = NULL;
	Memory.free((pointer)self - sizeof(struct objectAdditionalData));
}

void TONIGHT destruct(const Class class){
	if(!This) return;
	class->dtor(This);
}

INLINE Class TONIGHT classOf(object obj){
	return (obj ? obj->class_pointer : NULL);
}

bool TONIGHT isType(const object obj, const Class class){
	Class pClass;
	for(pClass = obj->class_pointer; pClass; pClass = pClass->super)
		if(pClass == class) return true;
	return false;
}

INLINE size_t TONIGHT sizeOf(const object obj){
	return obj->class_pointer->size;
}

INLINE object TONIGHT copy(const object obj){
	return $(obj $as Object).copy();
}

bool TONIGHT compare(const object a, const object b){
	return $(a $as Object).equal(b);
}

/* Object class */

static bool Object_equal(const object obj){
	return this == obj ? true : false;
}

static object Object_clone(void){
	object ret = Memory.copy(this);
    ret->data = Memory.copy(this->data);
    ret->class_pointer = this->class_pointer;
	return ret;
}

static string Object_toString(void){
	return String.formated("%s at 0x%p", this->class_pointer->name, this);
}

static retString Object_toRetString(void){
	retString ret;
    memcpy(ret.Text, $(this $as Object).toString(), sizeof ret);
    return ret;
}

static longRetString Object_toLongRetString(void){
	longRetString ret;
    memcpy(ret.Text, $(this $as Object).toString(), sizeof ret);
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
	bool ret = $Empty(bool);
	Method(Object){
        ret = getInterface(Object).equal(obj);
	}
	return ret;
}

static object IObject_clone(void){
	object ret = $Empty(object);
	Method(Object){
        ret = getInterface(Object).copy();
	}
	return ret;
}

static string IObject_toString(void){
	string ret = $Empty(string);
    Method(Object){
        ret = getInterface(Object).toString();
	}
    return ret;
}

static retString IObject_toRetString(void){
	retString ret = $Empty(retString);
	Method(Object){
        ret = getInterface(Object).toRetString();
	}
    return ret;
}

static longRetString IObject_toLongRetString(void){
	longRetString ret = $Empty(longRetString);
	Method(Object){
        ret = getInterface(Object).toLongRetString();
	}
	return ret;
}

static IObject iObject = {
	.equal = IObject_equal,
	.copy = IObject_clone,
	.toString = IObject_toString,
	.toRetString = IObject_toRetString,
	.toLongRetString = IObject_toLongRetString
};

static void new_Object(pointer args){
    setInterface(Object, Object_vtble);
}

static void del_Object(void){
}

INLINE IObject ___Object_select___(object obj){
	setCurrentObject(obj);
	return *___Object___.implement.__interface;
}

static void Object_ctor(object obj, pointer args){
	setCurrentObject(obj);
	Method(Object){
        new_Object(args);
	}
}

static void Object_dtor(object obj){
	setCurrentObject(obj);
	Method(Object){
        del_Object();
	}
}

const struct Interface_Object ___Object___ = {
	._ = (const struct str_Class){
		.name = "Object",
		.super = NULL,
		.size = sizeof(Class_Object),
		.ctor = Object_ctor,
		.dtor = Object_dtor
	},
	.__class__ = (Class)&Object,
	.implement = (const Class_Object){
		.__interface = &iObject
	}
};

const Class Object = (const Class)&___Object___;
