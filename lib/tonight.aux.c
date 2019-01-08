#include <string.h>

#include "../include/Tonight/tonight.h"

static struct ctxt{
	int value;
	pointer next;
}*fctxt = NULL;

static void push(int value){
	struct ctxt *p = Memory.alloc(sizeof(struct ctxt));
	p->value = value;
	p->next = fctxt;
	fctxt = p;
}

static int pop(void){
	if(fctxt){
		pointer node = fctxt;
		int ret = fctxt->value;
		fctxt = fctxt->next;
		Memory.free(node);
		return ret;
	}
	return 0;
}

INLINE void TONIGHT initForeach(void){
	push(-1);
}

bool TONIGHT foreachIterator(pointer var, pointer array){
	if(++ fctxt->value < Collection.length(array)){
		*(pointer*)var = *(pointer*)Collection.access(array, fctxt->value);
		return true;
	}
	else{
		pop();
		return false;
	}
}

struct Stack{
	bool ret;
	size_t size;
	pointer current;
	pointer prev;
}*stack = NULL;

void __create_using_context(size_t size, pointer point){
	struct Stack *_new = Memory.alloc(sizeof(struct Stack));
	_new->current = Memory.alloc(size);
	memcpy(_new->current, point, size);
	_new->ret = true;
	_new->size = size;
	_new->prev = stack;
	stack = _new;
}

bool __function_using(pointer point, P_void destroy){
	if(stack->ret){
		stack->ret = false;
		return true;
	}
	else{
		struct Stack *tmp = stack;
		if(destroy) if(*(pointer*)point) destroy(*(pointer*)point);
		memcpy(point, stack->current, stack->size);
		stack = stack->prev;
		Memory.free(tmp->current);
		Memory.free(tmp);
		return false;
	}
}

static struct object_stack{
	object value;
	pointer next;
}*objstk = NULL;

static void push_object(object value){
	struct object_stack *p = Memory.alloc(sizeof(struct object_stack));
	p->value = value;
	p->next = objstk;
	objstk = p;
}

static object pop_object(void){
	if(objstk){
		pointer node = objstk;
		object ret = objstk->value;
		objstk = objstk->next;
		Memory.free(node);
		return ret;
	}
	return NULL;
}

static object get_object(void){
	if(objstk)
		return objstk->value;
	return NULL;
}

INLINE void TONIGHT setCurrentObject(object obj){
	push_object(obj);
}

INLINE object TONIGHT getCurrentObject(void){
	return pop_object();
}

INLINE object TONIGHT checkCurrentObject(Class class){
	object current = get_object();
	return isType(current, class) ? current : NULL;
}
