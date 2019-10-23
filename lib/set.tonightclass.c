#include "../include/tonight.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/set.h"

/* Set */
static size_t Set_ICollection_length(pointer collect){
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
