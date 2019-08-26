#include <string.h>

#include "../include/Tonight/tonight.h"

object This = NULL;

object TONIGHT newInstance(const Class class, ...){
	object _new = Memory.alloc(sizeof(Intern_Object));
	va_list args;
	va_start(args, class);
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

static INLINE IObject Object_select(object obj){
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
	},
	.select = Object_select
};

const Class Object = (const Class)&___Object___;

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

static void Set_ICollection_index(pointer collect, pointer var, int index){
	$(collect $as Set).getCollection()->index(collect, var, index);
}

static ICollection Set_ICollection = {
	.length = Set_ICollection_length,
	.size = Set_ICollection_size,
	.access = Set_ICollection_access,
	.index = Set_ICollection_index
};

static ICollection * Set_getCollection(void){
	return $$(this $as Set).collection;
}

static void Set_setCollection(ICollection value){
	*$$(this $as Set).collection = value;
}

static ISet Set_vtble = {
	.getCollection = Set_getCollection,
	.setCollection = Set_setCollection
};

static void Set_constructor(pointer args){
	static ICollection _default;
	construct(superOf(Set));
	_default = *getICollection(this);
	$$(this $as Set).collection = Memory.alloc(sizeof _default);
	*$$(this $as Set).collection = _default;
	setInterface(Set, Set_vtble);
	*getICollection(this) = Set_ICollection;
}

static void Set_destructor(void){
	Memory.free($$(this $as Set).collection);
	destruct(superOf(Set));
}

static ICollection * ISet_getCollection(void){
	ICollection *ret = $Empty(ICollection*);
	Method(Set){
	    ret = getInterface(Set).getCollection();
	}
	return ret;
}

static void ISet_setCollection(ICollection value){
	Method(Set){
	    getInterface(Set).setCollection(value);
	}
}

static ISet iSet = {
	.getCollection = ISet_getCollection,
	.setCollection = ISet_setCollection
};

Constructor(Set, Set_constructor);
Destructor(Set, Set_destructor);

Define_Class(Set $extends Object $implements ISet $as iSet);
