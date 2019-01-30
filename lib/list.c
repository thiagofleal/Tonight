#include "../include/Tonight/tonight.h"
#include "../include/Tonight/list.h"

Define_Exception(IndexException $as "Invalid index" $extends GenericException);

static pointer iterator(struct Node *node){
	struct Node *i;
	for(i = node; i->next; i = i->next);
	return i;
}

static void List_add(pointer value)
{
	CLASS(List);
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

static void List_addPos(pointer value, int index)
{
	CLASS(List);
	int i;
	struct Node *node = this.list, *newNode;
	
	if(index > this.size || index < 0){
		throw(IndexException, concat("Impossible to add the index ", is(index), $end));
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

static void List_remove(int index)
{
	CLASS(List);
	int i;
	struct Node *node = this.list, *aux;
	
	if(index >= this.size || index < 0){
		static string error = NULL;
		
		if(error)	Memory.free(error);
		error = concat("Impossible to access the index ", is(index), $end);
		throw(IndexException, error);
	}
	
	if(this.freeCallBack){
		this.freeCallBack($(self $as List).get(index));
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
	Memory.free(aux);
	this.size--;
}

static private struct Node * List_getNode(Class_List *This, int index)
{
	int i;
	struct Node *node = this.list;
	
	if(index >= this.size || index < 0){
		throw(IndexException, concat("Impossible to access the index ", is(index), $end));
	}
	for(i = 0; i < index && node->next; i++, node = node->next);
	return node;
}

static pointer List_get(int index)
{
	CLASS(List);
	return List_getNode(self->data, index)->value;
}

static int List_size(void)
{
	CLASS(List);
	return this.size;
}

static pointer List_toArray(void)
{
	CLASS(List);
	int i;
	pointer ARRAY ret = Array.Pointer(this.size);
	
	for(i = 0; i < this.size; i++)
	{
		ret[i] = $(self $as List).get(i);
	}
	return ret;
}

static object List_select(condition where)
{
	CLASS(List);
	object sel = new(List.class);
	register int i, length = $(self $as List).size();
	pointer current;
	
	for(i = 0; i < length; i++)
	{
		current = $(self $as List).get(i);
		
		if(where(current))
		{
			$(sel $as List).add(current);
		}
	}
	
	return sel;
}

static void List_setFreeCallBack(P_freeCallBack freeCallBack)
{
	CLASS(List);
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
	.setFreeCallBack = List_setFreeCallBack
};

static int List_ICollection_length(pointer collect)
{
	return $(collect $as List).size();
}

static size_t List_ICollection_size(pointer collect)
{
	return sizeof(pointer);
}

static pointer List_ICollection_access(pointer collect, int index)
{
	return &List_getNode(((object)collect)->data, index)->value;
}

static ICollection List_collection = {
	.length = List_ICollection_length,
	.size = List_ICollection_size,
	.access = List_ICollection_access
};

static Constructor(List)
{
	CLASS(List);
	
	construct(super());
	this.list = NULL;
	this.size = 0;
	this.freeCallBack = NULL;
	setInterface(List_vtble);
	$(self $as Set).setCollection(List_collection);
}

static Destructor(List)
{
	CLASS(List);
	
	while(this.size)
	{
		$(self $as List).remove(0);
	}
	
	destruct(super());
}

static void IList_add(pointer value)
{
	CHECK_CLASS(List);
	getInterface.add(value);
}

static void IList_addPos(pointer value, int index)
{
	CHECK_CLASS(List);
	getInterface.addPos(value, index);
}

static void IList_remove(int index)
{
	CHECK_CLASS(List);
	getInterface.remove(index);
}

static pointer IList_get(int index)
{
	CHECK_CLASS(List);
	return getInterface.get(index);
}

static int IList_size(void)
{
	CHECK_CLASS(List);
	return getInterface.size();
}

static pointer IList_toArray(void)
{
	CHECK_CLASS(List);
	return getInterface.toArray();
}

static object IList_select(condition where)
{
	CHECK_CLASS(List);
	return getInterface.select(where);
}

static void IList_setFreeCallBack(P_freeCallBack freeCallBack)
{
	CHECK_CLASS(List);
	return getInterface.setFreeCallBack(freeCallBack);
}

static IList iList = {
	.add = IList_add,
	.addPos = IList_addPos,
	.remove = IList_remove,
	.get = IList_get,
	.size = IList_size,
	.toArray = IList_toArray,
	.select = IList_select,
	.setFreeCallBack = IList_setFreeCallBack
};

Define_Class(List $extends Set $implements IList $with iList);
