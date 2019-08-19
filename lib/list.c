#include "../include/Tonight/tonight.h"
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
        string s = concat("Impossible to add the index ", $i(index), $end);
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
        error = concat("Impossible to access the index ", is(index).Text, $end);
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
		throw(IndexException, concat("Impossible to access the index ", $i(index), $end));
	}
	for(i = 0; i < index && node->next; i++, node = node->next);
	return node;
}

static pointer List_get(int index){
	return List_getNode(this, index)->value;
}

static int List_size(void){
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
            $(sel $as List).add(current);
        }
    }
	return sel;
}

static string List_toString(P_retString method, string sep){
	string ret;
    Writer write = New.Writer(Tonight.Std.String.Output);
    register int i, length = $$(this $as List).size;
    char ARRAY str = Array.Char((sizeof(retString) + String.length(sep)) * length);
    if(!length)
        return toString("");
    *str = 0;
    checkArgumentPointer(method);
    for(i=0; i<length; i++)
        write.print(str, getText(method(List_getNode(this, i)->value)), sep, $end);
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
	.toString = List_toString,
	.setFreeCallBack = List_setFreeCallBack
};

static inline int List_ICollection_length(pointer collect){
	return $(collect $as List).size();
}

static inline size_t List_ICollection_size(pointer collect){
	return sizeof(pointer);
}

static inline pointer List_ICollection_access(pointer collect, int index){
	return List_getNode(collect, index);
}

static inline void List_ICollection_index(pointer collect, pointer var, int index){
	*(int*)var = index;
}

static ICollection List_collection = {
	.length = List_ICollection_length,
	.size = List_ICollection_size,
	.access = List_ICollection_access,
	.index = List_ICollection_index
};

static void List_constructor(){
	construct(superOf(List));
	$$(this $as List).list = NULL;
	$$(this $as List).size = 0;
	$$(this $as List).freeCallBack = NULL;
	setInterface(List, List_vtble);
	$(this $as Set).setCollection(List_collection);
}

static void List_destructor(){
	while($$(this $as List).size){
		$(this $as List).remove(0);
	}

	destruct(superOf(List));
}

static void IList_add(pointer value){
	Method(){
        getInterface(List).add(value);
	}
}

static void IList_addPos(pointer value, int index){
	Method(){
        getInterface(List).addPos(value, index);
	}
}

static void IList_remove(int index){
	Method(){
        getInterface(List).remove(index);
	}
}

static pointer IList_get(int index){
	pointer ret;

    Method(){
        ret = getInterface(List).get(index);
	}

	return ret;
}

static int IList_size(void){
	int ret;

	Method(){
        ret = getInterface(List).size();
	}

	return ret;
}

static pointer IList_toArray(void){
	pointer ret;

	Method(){
        ret = getInterface(List).toArray();
	}

	return ret;
}

static object IList_select(condition where){
	object ret;

	Method(){
        ret = getInterface(List).where(where);
	}

	return ret;
}

static string IList_toString(P_retString method, string sep){
	string ret;

	Method(){
        ret = getInterface(List).toString(method, sep);
	}

	return ret;
}

static void IList_setFreeCallBack(P_freeCallBack freeCallBack){
	Method(){
        getInterface(List).setFreeCallBack(freeCallBack);
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
	.toString = IList_toString,
	.setFreeCallBack = IList_setFreeCallBack
};

Constructor(List, List_constructor);
Destructor(List, List_destructor);

Define_Class(List $extends Set $implements IList $with iList);
