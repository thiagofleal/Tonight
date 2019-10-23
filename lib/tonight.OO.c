#include <string.h>
#include "../include/tonight.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/collection.h"
#include "../include/Tonight/string.h"
#include "../include/Tonight/wstring.h"

object This = NULL;

struct objectAdditionalData{
    ICollection *collection;
    byte obj[0];
};

object TONIGHT newInstance(const Class class, ...){
    struct objectAdditionalData* data = Memory.alloc(sizeof(struct objectAdditionalData) + sizeof(Intern_Object));
    object _new;
	va_list args;
	va_start(args, class);
	data->collection = NULL;
	_new = (object)data->obj;
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

static wstring Object_toWideString(void){
	return WideString.formated(L"%s at 0x%p", this->class_pointer->name, this);
}

static fixString Object_toFixString(void){
	fixString ret;
    memcpy(ret.Text, $(this $as Object).toString(), sizeof ret);
    return ret;
}

static longFixString Object_toLongFixString(void){
	longFixString ret;
    memcpy(ret.Text, $(this $as Object).toString(), sizeof ret);
	return ret;
}

static fixWideString Object_toFixWideString(void){
	fixWideString ret;
    memcpy(ret.Text, $(this $as Object).toWideString(), sizeof ret);
    return ret;
}

static longFixWideString Object_toLongFixWideString(void){
	longFixWideString ret;
    memcpy(ret.Text, $(this $as Object).toWideString(), sizeof ret);
	return ret;
}

static IObject Object_vtble = {
	.equal = Object_equal,
	.copy = Object_clone,
	.toString = Object_toString,
	.toWideString = Object_toWideString,
	.toFixString = Object_toFixString,
	.toLongFixString = Object_toLongFixString,
	.toFixWideString = Object_toFixWideString,
	.toLongFixWideString = Object_toLongFixWideString
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

static wstring IObject_toWideString(void){
	wstring ret = $Empty(wstring);
    Method(Object){
        ret = getInterface(Object).toWideString();
	}
    return ret;
}

static fixString IObject_toFixString(void){
	fixString ret = $Empty(fixString);
	Method(Object){
        ret = getInterface(Object).toFixString();
	}
    return ret;
}

static longFixString IObject_toLongFixString(void){
	longFixString ret = $Empty(longFixString);
	Method(Object){
        ret = getInterface(Object).toLongFixString();
	}
	return ret;
}

static fixWideString IObject_toFixWideString(void){
	fixWideString ret = $Empty(fixWideString);
	Method(Object){
        ret = getInterface(Object).toFixWideString();
	}
    return ret;
}

static longFixWideString IObject_toLongFixWideString(void){
	longFixWideString ret = $Empty(longFixWideString);
	Method(Object){
        ret = getInterface(Object).toLongFixWideString();
	}
	return ret;
}

static IObject iObject = {
	.equal = IObject_equal,
	.copy = IObject_clone,
	.toString = IObject_toString,
	.toWideString = IObject_toWideString,
	.toFixString = IObject_toFixString,
	.toLongFixString = IObject_toLongFixString,
	.toFixWideString = IObject_toFixWideString,
	.toLongFixWideString = IObject_toLongFixWideString
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
