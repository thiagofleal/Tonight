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

static pointer List_get(int index)
{
	CLASS(List);
	int i;
	struct Node *node = this.list;
	
	if(index >= this.size || index < 0){
		throw(IndexException, concat("Impossible to access the index ", is(index), $end));
	}
	for(i = 0; i < index && node->next; i++, node = node->next);
	return node->value;
}

static int List_size(INTERN_METHOD)
{
	CLASS(List);
	return this.size;
}

static pointer List_toArray(INTERN_METHOD)
{
	CLASS(List);
	int i;
	pointer ARRAY ret = Array.Pointer(this.size);
	IList iL = getInterface;
	for(i = 0; i < this.size; i++)
	{
		ret[i] = $(self $as List).get(i);
	}
	return ret;
}

static void List_setFreeCallBack(P_freeCallBack freeCallBack)
{
	CLASS(List);
	this.freeCallBack = freeCallBack;
}

static IList List_vtble = {
	List_add,
	List_addPos,
	List_remove,
	List_get,
	List_size,
	List_toArray,
	List_setFreeCallBack
};

static ICollection List_collection = {};

static Constructor(List)
{
	CLASS(List);
	
	super(construct);
	this.list = NULL;
	this.size = 0;
	this.freeCallBack = NULL;
	setInterface(List_vtble);
}

static Destructor(List)
{
	CLASS(List);
	
	while(this.size)
	{
		$(self $as List).remove(0);
	}
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

static void IList_setFreeCallBack(P_freeCallBack freeCallBack)
{
	CHECK_CLASS(List);
	return getInterface.setFreeCallBack(freeCallBack);
}

static IList iList = {
	IList_add,
	IList_addPos,
	IList_remove,
	IList_get,
	IList_size,
	IList_toArray,
	IList_setFreeCallBack
};

Define_Class(List $extends Object $implements IList $with iList);
