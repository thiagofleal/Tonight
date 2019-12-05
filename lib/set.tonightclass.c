#include "../include/tonight.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/set.h"

/* Set */
static void Set_ICollection_currentValue(pointer collect, pointer var){
	$$(collect $as Set).collection->currentValue(collect, var);
}

static void Set_ICollection_currentKey(pointer collect, pointer var){
	$$(collect $as Set).collection->currentKey(collect, var);
}

static bool Set_ICollection_next(pointer collect){
	return $$(collect $as Set).collection->next(collect);
}

static void Set_ICollection_reset(pointer collect){
	$$(collect $as Set).collection->reset(collect);
}

static ICollection Set_ICollection = {
	.currentValue = Set_ICollection_currentValue,
	.currentKey = Set_ICollection_currentKey,
	.next = Set_ICollection_next,
	.reset = Set_ICollection_reset
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

extern int puts(const string);

static void Set_constructor(pointer args){
	static ICollection _default = $Empty(ICollection);
	construct(superOf(Set));
	$$(this $as Set).collection = Memory.alloc(sizeof _default);
	*$$(this $as Set).collection = _default;
	setInterface(Set, Set_vtble);
	setICollection(this, &Set_ICollection);
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
