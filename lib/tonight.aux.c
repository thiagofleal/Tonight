#include "tonight.proto.h"

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
	if(++ fctxt->value < Array.length(array)){
		*(pointer*)var = *(pointer*)Array.access(array, fctxt->value);
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

bool __function_using(pointer point){
	if(stack->ret){
		stack->ret = false;
		return true;
	}
	else{
		struct Stack *tmp = stack;
		memcpy(point, stack->current, stack->size);
		stack = stack->prev;
		Memory.free(tmp->current);
		Memory.free(tmp);
		return false;
	}
}
