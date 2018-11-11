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
