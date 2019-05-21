#include "../include/Tonight/tonight.h"
#include "../include/Tonight/list.h"

Define_Exception(IndexException $as "Invalid index" $extends GenericException);

static pointer iterator(struct Node *node){
	struct Node *i;
	for(i = node; i->next; i = i->next);
	return i;
}

static void List_add(pointer value){
    object self = useContext();

    This(List, self);
    struct Node *node;

    if(!this.list){
        this.list = Memory.alloc(sizeof(struct Node));
        node = this.list;
        node->value = value;
        node->next = NULL;
    }
    else{
        node = iterator(this.list);
        node->next = Memory.alloc(sizeof(struct Node));
        node = node->next;
        node->value = value;
        node->next = NULL;
    }
    this.size++;
}

static void List_addPos(pointer value, int index){
	object self = useContext();
    This(List, self);
    int i;
    struct Node *node = this.list, *newNode;

    if(index > this.size || index < 0){
        string s = concat("Impossible to add the index ", $i(index), $end);
        throw(IndexException, s);
        String.free(s);
    }
    if(!index){
        newNode = Memory.alloc(sizeof(struct Node));
        newNode->value = value;
        newNode->next = this.list;
        this.list = newNode;
    }
    else{
        for(i = 2; i <= index && node->next; i++, node = node->next);
        newNode = Memory.alloc(sizeof(struct Node));
        newNode->value = value;
        newNode->next = node->next;
        node->next = newNode;
    }
    this.size++;
}

static void List_remove(int index){
	object self = useContext();
    This(List, self);
    int i;
    struct Node *node = this.list, *aux;

    if(index >= this.size || index < 0){
        static string error = NULL;

        if(error)	Memory.free(error);
        error = concat("Impossible to access the index ", is(index), $end);
        throw(IndexException, error);
    }

    if(!index){
        aux = node;
        node = node->next;
        this.list = node;
    }
    else{
        struct Node **p;
        for(i = 0; i < index - 1 && node->next; i++, node = node->next);
        p = (struct Node**)&node->next;
        aux = *p;
        *p = (*p)->next;
    }

    if(this.freeCallBack){
        this.freeCallBack(aux->value);
    }

    Memory.free(aux);
    this.size--;
}

static private struct Node * List_getNode(object self, int index){
	int i;
	Class_List *This = self->data;
	struct Node *node = this.list;

	if(index >= this.size || index < 0){
		throw(IndexException, concat("Impossible to access the index ", $i(index), $end));
	}
	for(i = 0; i < index && node->next; i++, node = node->next);
	return node;
}

static pointer List_get(int index){
	object self = useContext();
    return List_getNode(self, index)->value;
}

static int List_size(void){
	object self = useContext();
    This(List, self);
    return this.size;
}

static pointer List_toArray(void){
	object self = useContext();
	This(List, self);
    pointer ARRAY ret;
    register int i;

    ret = Array.Pointer(this.size);

    for(i = 0; i < this.size; i++){
        ret[i] = List_get(i);
    }
	return ret;
}

static object List_select(condition where){
	object self = useContext();
	object sel;
    This(List, self);
    register int i, length = this.size;
    pointer current;

    sel = new(List.class);

    for(i = 0; i < length; i++){
        current = List_getNode(self, i)->value;

        if(where(&current)){
            $(sel $as List).add(current);
        }
    }
	return sel;
}

static string List_toString(P_retString method, string sep){
	object self = useContext();
	string ret;
    This(List, self);
    Writer write = Writer(Tonight.Std.String.Output);
    register int i, length = this.size;
    char ARRAY str = Array.Char((sizeof(retString) + String.length(sep)) * length);
    if(!length)
        return toString("");
    *str = 0;
    checkArgumentPointer(method);
    for(i=0; i<length; i++)
        write.print(str, getText(method(List_getNode(self, i)->value)), sep, $end);
    str[String.length(str) - String.length(sep)] = 0;
    ret = toString(str);
    Array.free(str);
	return ret;
}

static void List_setFreeCallBack(P_freeCallBack freeCallBack){
	object self = useContext();
    This(List, self);
    this.freeCallBack = freeCallBack;
}

static IList List_vtble = {
	.add = List_add,
	.addPos = List_addPos,
	.remove = List_remove,
	.get = List_get,
	.size = List_size,
	.toArray = List_toArray,
	.select = List_select,
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
	return &List_getNode(collect, index)->value;
}

static ICollection List_collection = {
	.length = List_ICollection_length,
	.size = List_ICollection_size,
	.access = List_ICollection_access
};

static Constructor(List){
	object self = getCurrentObject();
	This(List, self);
	construct(superOf(List), self);
	this.list = NULL;
	this.size = 0;
	this.freeCallBack = NULL;
	setInterface(List_vtble);
	$(self $as Set).setCollection(List_collection);
}

static Destructor(List){
	object self = getCurrentObject();
	This(List, self);

	while(this.size){
		$(self $as List).remove(0);
	}

	destruct(superOf(List), self);
}

static void IList_add(pointer value){
	object self = getCurrentObject();
	This(List, self);

	with(self){
        getInterface.add(value);
	}
}

static void IList_addPos(pointer value, int index){
	object self = getCurrentObject();
	This(List, self);

	with(self){
        getInterface.addPos(value, index);
	}
}

static void IList_remove(int index){
	object self = getCurrentObject();
	This(List, self);

	with(self){
        getInterface.remove(index);
	}
}

static pointer IList_get(int index){
	object self = getCurrentObject();
	This(List, self);
	pointer ret;

	with(self){
        ret = getInterface.get(index);
	}

	return ret;
}

static int IList_size(void){
	object self = getCurrentObject();
	This(List, self);
	int ret;

	with(self){
        ret = getInterface.size();
	}

	return ret;
}

static pointer IList_toArray(void){
	object self = getCurrentObject();
	This(List, self);
	pointer ret;

	with(self){
        ret = getInterface.toArray();
	}

	return ret;
}

static object IList_select(condition where){
	object self = getCurrentObject();
	This(List, self);
	object ret;

	with(self){
        ret = getInterface.select(where);
	}

	return ret;
}

static string IList_toString(P_retString method, string sep){
	object self = getCurrentObject();
	This(List, self);
	string ret;

	with(self){
        ret = getInterface.toString(method, sep);
	}

	return ret;
}

static void IList_setFreeCallBack(P_freeCallBack freeCallBack){
	object self = getCurrentObject();
	This(List, self);

	with(self){
        getInterface.setFreeCallBack(freeCallBack);
	}
}

static IList iList = {
	.add = IList_add,
	.addPos = IList_addPos,
	.remove = IList_remove,
	.get = IList_get,
	.size = IList_size,
	.toArray = IList_toArray,
	.select = IList_select,
	.toString = IList_toString,
	.setFreeCallBack = IList_setFreeCallBack
};

Define_Class(List $extends Set $implements IList $with iList);
