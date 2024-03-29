#include "../include/tonight.h"
#include "../include/Tonight/exceptions.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/string.h"
#include "../include/Tonight/list.h"

Define_Exception(IndexException $as "Invalid index" $extends GenericException);

static pointer iterator(struct Node *node){
	struct Node *i;
	for(i = node; i->next; i = i->next);
	return i;
}

static void List_add(pointer value){
    struct Node *node;

    if(!$$(this $as List).list){
        $$(this $as List).list = Memory.alloc(sizeof(struct Node));
        node = $$(this $as List).list;
        node->value = value;
        node->next = NULL;
    }
    else{
        node = iterator($$(this $as List).list);
        node->next = Memory.alloc(sizeof(struct Node));
        node = node->next;
        node->value = value;
        node->next = NULL;
    }
    $$(this $as List).size++;
}

static void List_addPos(pointer value, int index){
	int i;
    struct Node *node = $$(this $as List).list, *newNode;

    if(index > $$(this $as List).size || index < 0){
        string s = String.concat("Impossible to add the index ", $i(index), $end);
        throw(IndexException, s);
        String.free(s);
    }
    if(!index){
        newNode = Memory.alloc(sizeof(struct Node));
        newNode->value = value;
        newNode->next = $$(this $as List).list;
        $$(this $as List).list = newNode;
    }
    else{
        for(i = 2; i <= index && node->next; i++, node = node->next);
        newNode = Memory.alloc(sizeof(struct Node));
        newNode->value = value;
        newNode->next = node->next;
        node->next = newNode;
    }
    $$(this $as List).size++;
}

static void List_remove(int index){
	int i;
    struct Node *node = $$(this $as List).list, *aux;

    if(index >= $$(this $as List).size || index < 0){
        static string error = NULL;

        if(error)	Memory.free(error);
        error = String.concat("Impossible to access the index ", is(index).Text, $end);
        throw(IndexException, error);
    }

    if(!index){
        aux = node;
        node = node->next;
        $$(this $as List).list = node;
    }
    else{
        struct Node **p;
        for(i = 0; i < index - 1 && node->next; i++, node = node->next);
        p = (struct Node**)&node->next;
        aux = *p;
        *p = (*p)->next;
    }

    if($$(this $as List).freeCallBack){
        $$(this $as List).freeCallBack(aux->value);
    }

    Memory.free(aux);
    $$(this $as List).size--;
}

static Private struct Node * List_getNode(object self, int index){
	int i;
	struct Node *node = $$(self $as List).list;

	if(index >= $$(self $as List).size || index < 0){
		throw(IndexException, String.concat("Impossible to access the index ", $i(index), $end));
	}
	for(i = 0; i < index && node->next; i++, node = node->next);
	return node;
}

static pointer List_get(int index){
	return List_getNode(this, index)->value;
}

static unsigned int List_size(void){
	return $$(this $as List).size;
}

static pointer List_toArray(void){
	pointer ARRAY ret;
    register int i;

    ret = Array.Pointer($$(this $as List).size);

    for(i = 0; i < $$(this $as List).size; i++){
        ret[i] = List_get(i);
    }
	return ret;
}

static object List_select(condition where){
	object sel;
    register int i, length = $$(this $as List).size;
    pointer current;

    sel = new(List);

    for(i = 0; i < length; i++){
        current = List_getNode(this, i)->value;

        if(where(&current)){
            $(sel $as List)->add(current);
        }
    }
	return sel;
}

static void List_setStringMethod(P_fixString method){
    $$(this $as List).stringMethod = method;
}

static string List_toString(string sep){
    extern int sprintf(string, const string, ...);
	string ret;
    register int i, length = $$(this $as List).size;
    char ARRAY str = Array.Char((sizeof(fixString) + String.length(sep)) * length);
    P_fixString method = $$(this $as List).stringMethod;
    if(!length)
        return toString("");
    *str = 0;
    for(i=0; i<length; i++)
        sprintf(str, "%s%s%s", str, getText(method(List_getNode(this, i)->value)), sep);
    str[String.length(str) - String.length(sep)] = 0;
    ret = toString(str);
    Array.free(str);
	return ret;
}

static void List_setFreeCallBack(P_freeCallBack freeCallBack){
	$$(this $as List).freeCallBack = freeCallBack;
}

static IList List_vtble = {
	.add = List_add,
	.addPos = List_addPos,
	.remove = List_remove,
	.get = List_get,
	.size = List_size,
	.toArray = List_toArray,
	.where = List_select,
	.setStringMethod = List_setStringMethod,
	.toString = List_toString,
	.setFreeCallBack = List_setFreeCallBack
};

static inline void List_ICollection_currentValue(pointer collect, pointer var){
	*(pointer*)var = $$(collect $as List).current->value;
}

static inline void List_ICollection_currentKey(pointer collect, pointer var){
	*(int*)var = $$(collect $as List).currentKey;
}

static bool List_ICollection_next(pointer collect){
    struct Node **node = &$$(collect $as List).current;
	if(*node){
        *node = (*node)->next;
        ++ $$(collect $as List).currentKey;
	}else{
	    *node = $$(collect $as List).list;
	    $$(collect $as List).currentKey = 0;
	}
	return *node ? true : false;
}

static inline void List_ICollection_reset(pointer collect){
	$$(collect $as List).current = NULL;
	$$(collect $as List).currentKey = -1;
}

static ICollection List_collection = {
	.currentValue = List_ICollection_currentValue,
	.currentKey = List_ICollection_currentKey,
	.next = List_ICollection_next,
	.reset = List_ICollection_reset
};

static void List_constructor(pointer args){
	construct(superOf(List));
	$$(this $as List).list = NULL;
	$$(this $as List).size = 0;
	List_ICollection_reset(this);
	setInterface(List, List_vtble);
	$(this $as Set)->setCollection(List_collection);
	$$(this $as List).freeCallBack = NULL;
}

static void List_destructor(void){
	while($$(this $as List).size){
		$(this $as List)->remove(0);
	}

	destruct(superOf(List));
}

static void IList_add(pointer value){
	Method(List){
        getInterface(List)->add(value);
	}
}

static void IList_addPos(pointer value, int index){
	Method(List){
        getInterface(List)->addPos(value, index);
	}
}

static void IList_remove(int index){
	Method(List){
        getInterface(List)->remove(index);
	}
}

static pointer IList_get(int index){
	pointer ret = $Empty(pointer);
    Method(List){
        ret = getInterface(List)->get(index);
	}
    return ret;
}

static unsigned int IList_size(void){
	unsigned int ret = $Empty(unsigned int);
    Method(List){
        ret = getInterface(List)->size();
	}
    return ret;
}

static pointer IList_toArray(void){
	pointer ret = $Empty(pointer);
    Method(List){
        ret = getInterface(List)->toArray();
	}
    return ret;
}

static object IList_select(condition where){
	object ret = $Empty(object);
    Method(List){
        ret = getInterface(List)->where(where);
	}
    return ret;
}

static void IList_setStringMethod(P_fixString method){
    Method(List){
        getInterface(List)->setStringMethod(method);
    }
}

static string IList_toString(string sep){
	string ret = $Empty(string);
    Method(List){
        ret = getInterface(List)->toString(sep);
	}
    return ret;
}

static void IList_setFreeCallBack(P_freeCallBack freeCallBack){
	Method(List){
        getInterface(List)->setFreeCallBack(freeCallBack);
	}
}

static IList iList = {
	.add = IList_add,
	.addPos = IList_addPos,
	.remove = IList_remove,
	.get = IList_get,
	.size = IList_size,
	.toArray = IList_toArray,
	.where = IList_select,
	.setStringMethod = IList_setStringMethod,
	.toString = IList_toString,
	.setFreeCallBack = IList_setFreeCallBack
};

Constructor(List, List_constructor);
Destructor(List, List_destructor);

Define_Class(List $extends Set $implements IList $with iList);
