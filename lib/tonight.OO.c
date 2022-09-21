#include <string.h>
#include "../include/tonight.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/collection.h"
#include "../include/Tonight/string.h"
#include "../include/Tonight/wstring.h"

object This = NULL;

object TONIGHT newInstance(const Class class, ...){
    object _new;
	va_list args;
	va_start(args, class);
	_new = Memory.alloc(sizeof(Intern_Object));
	_new->data = Memory.alloc(class->size);
	_new->class_pointer = class;
	class->ctor(_new, args);
	va_end(args);
	return _new;
}

extern void TONIGHT construct(const Class class, ...){
	va_list args;
	va_start(args, class);
	class->ctor(This, args);
	va_end(args);
}

void TONIGHT deleteInstance(object self){
	if(!self) return;
    if(!self->class_pointer) return;
    if(self->class_pointer->dtor) self->class_pointer->dtor(self);
    self->class_pointer = NULL;
	Memory.free(self->data);
	Memory.free(self);
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
	return $(obj $as Object)->copy();
}

bool TONIGHT compare(const object a, const object b){
	return $(a $as Object)->equal(b);
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
	string str = $(this $as Object)->toString();
    memcpy(ret.Text, str, sizeof ret);
    String.free(str);
    return ret;
}

static longFixString Object_toLongFixString(void){
	longFixString ret;
    string str = $(this $as Object)->toString();
    memcpy(ret.Text, str, sizeof ret);
    String.free(str);
    return ret;
}

static fixWideString Object_toFixWideString(void){
	fixWideString ret;
    wstring wstr = $(this $as Object)->toWideString();
    memcpy(ret.Text, wstr, sizeof ret);
    WideString.free(wstr);
    return ret;
}

static longFixWideString Object_toLongFixWideString(void){
	longFixWideString ret;
    wstring wstr = $(this $as Object)->toWideString();
    memcpy(ret.Text, wstr, sizeof ret);
    WideString.free(wstr);
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
        ret = getInterface(Object)->equal(obj);
	}
	return ret;
}

static object IObject_clone(void){
	object ret = $Empty(object);
	Method(Object){
        ret = getInterface(Object)->copy();
	}
	return ret;
}

static string IObject_toString(void){
	string ret = $Empty(string);
    Method(Object){
        ret = getInterface(Object)->toString();
	}
    return ret;
}

static wstring IObject_toWideString(void){
	wstring ret = $Empty(wstring);
    Method(Object){
        ret = getInterface(Object)->toWideString();
	}
    return ret;
}

static fixString IObject_toFixString(void){
	fixString ret = $Empty(fixString);
	Method(Object){
        ret = getInterface(Object)->toFixString();
	}
    return ret;
}

static longFixString IObject_toLongFixString(void){
	longFixString ret = $Empty(longFixString);
	Method(Object){
        ret = getInterface(Object)->toLongFixString();
	}
	return ret;
}

static fixWideString IObject_toFixWideString(void){
	fixWideString ret = $Empty(fixWideString);
	Method(Object){
        ret = getInterface(Object)->toFixWideString();
	}
    return ret;
}

static longFixWideString IObject_toLongFixWideString(void){
	longFixWideString ret = $Empty(longFixWideString);
	Method(Object){
        ret = getInterface(Object)->toLongFixWideString();
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

static Constructor(Object, new_Object);
static Destructor(Object, del_Object);

___def_base___(Object, IObject, iObject);
