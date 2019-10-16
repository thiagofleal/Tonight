#include <string.h>

#include "../include/tonight.h"
#include "../include/Tonight/exceptions.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/string.h"

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

INLINE void TONIGHT setCurrentObject(const object obj){
	push_object(obj);
}

INLINE object TONIGHT getCurrentObject(void){
	return pop_object();
}

object TONIGHT getCurrentObjectChecked(const Class class, P_void onError, ...){
	object self = pop_object();
	if(!isType(self, class)){
	    va_list v;
        va_start(v, onError);
        onError(self, v);
        va_end(v);
        return NULL;
	}
	return self;
}

/*
*   Method
*/

struct StackThis {
    object __this;
    bool ret;
    pointer prev;
}*stack_this = NULL;

static void classThisError(object obj, pointer args){
    $va_set(args, { Class obj_class; });
    static string error_str = NULL;
    if(error_str) String.free(error_str);
    error_str = concat(
        "The class \"",
        (obj->class_pointer ? obj->class_pointer->name : "(undefined)"),
        "\" not extends \"",
        $va_get.obj_class->name,
        "\"",
        $end
    );
    Throw(IllegalAccessException, error_str);
}

void __create_this_context(const Class class){
    struct StackThis *_new = Memory.alloc(sizeof(struct StackThis));
    _new->__this = This;
    This = getCurrentObjectChecked(class, classThisError, class);
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
