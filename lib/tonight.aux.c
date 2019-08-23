#include <string.h>

#include "../include/Tonight/tonight.h"

/*
*   forindex
*/
static struct ctxti{
	int value;
	int length;
	pointer collect;
	pointer next;
}*fctxti = NULL;

static void forindex_push(int value, int length, pointer collect){
	struct ctxti *p = Memory.alloc(sizeof(struct ctxti));
	p->value = value;
	p->length = length;
	p->collect = collect;
	p->next = fctxti;
	fctxti = p;
}

static int forindex_pop(void){
	if(fctxti){
		pointer node = fctxti;
		int ret = fctxti->value;
		fctxti = fctxti->next;
		Memory.free(node);
		return ret;
	}
	return 0;
}

INLINE bool TONIGHT initForindex(pointer collect){
	forindex_push(-1, Collection.length(collect), collect);
	return true;
}

bool TONIGHT forindexIterator(pointer var){
	if(++ fctxti->value < fctxti->length){
		Collection.index(fctxti->collect, var, fctxti->value);
		return true;
	}
	else{
		forindex_pop();
		return false;
	}
}

/*
*   foreach
*/
static struct ctxt{
	int value;
	int length;
	size_t size;
	pointer collect;
	pointer next;
}*fctxt = NULL;

static void push(int value, int length, size_t size, pointer collect){
	struct ctxt *p = Memory.alloc(sizeof(struct ctxt));
	p->value = value;
	p->length = length;
	p->size = size;
	p->collect = collect;
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

INLINE bool TONIGHT initForeach(pointer collect){
	push(-1, Collection.length(collect), Collection.size(collect), collect);
	return true;
}

bool TONIGHT foreachIterator(pointer var){
	if(++ fctxt->value < fctxt->length){
		memcpy(var, Collection.access(fctxt->collect, fctxt->value), fctxt->size);
		return true;
	}
	else{
		pop();
		return false;
	}
}

/*
*   using
*/
struct Stack{
	bool ret;
	size_t size;
	pointer current;
	pointer prev;
}*stack = NULL, *stack_with = NULL;

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

/*
*   with
*/
void __create_with_context(pointer point){
	struct Stack *_new = Memory.alloc(sizeof(struct Stack));
	_new->current = point;
	_new->ret = true;
	_new->size = sizeof(pointer);
	_new->prev = stack_with;
	stack_with = _new;
}

bool __function_with(void){
	if(stack_with->ret){
		stack_with->ret = false;
		return true;
	}
	else{
		struct Stack *tmp = stack_with;
		stack_with = stack_with->prev;
		Memory.free(tmp);
		return false;
	}
}

INLINE pointer useContext(void){
    return stack_with->current;
}

/*
*   Objects
*/
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

INLINE void TONIGHT setCurrentObject(const object obj){
	push_object(obj);
}

INLINE object TONIGHT getCurrentObject(void){
	return pop_object();
}

INLINE bool TONIGHT checkCurrentObject(const Class class){
	return isType(get_object(), class);
}

/*
*   Method
*/

struct StackThis {
    object __this;
    bool ret;
    pointer prev;
}*stack_this = NULL;

void __create_this_context(void){
    struct StackThis *_new = Memory.alloc(sizeof(struct StackThis));
    _new->__this = This;
    This = getCurrentObject();
    _new->ret = true;
    _new->prev = stack_this;
    stack_this = _new;
}

bool __function_this(void){
    if(stack_this->ret){
        stack_this->ret = false;
        return true;
    }
    else{
        pointer temp = stack_this;
        This = stack_this->__this;
        stack_this = stack_this->prev;
        Memory.free(temp);
        return false;
    }
}
