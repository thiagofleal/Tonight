#include "../include/tonight.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/collection.h"

INLINE ICollection* TONIGHT getICollection(pointer p){
	return *(ICollection**)(p - sizeof(ICollection*));
}

INLINE void TONIGHT setICollection(pointer p, ICollection *value){
	*(ICollection**)(p - sizeof(ICollection*)) = value;
}

static INLINE void TONIGHT Collection_currentValue(pointer p, pointer var){
    getICollection(p)->currentValue(p, var);
}

static INLINE void TONIGHT Collection_currentKey(pointer p, pointer var){
    getICollection(p)->currentKey(p, var);
}

static INLINE bool TONIGHT Collection_next(pointer p){
    return getICollection(p)->next(p);
}

static INLINE void TONIGHT Collection_reset(pointer p){
    getICollection(p)->reset(p);
}

/* Collection */
const ICollection Collection = {
	.currentValue = Collection_currentValue,
	.currentKey = Collection_currentKey,
	.next = Collection_next,
	.reset = Collection_reset
};

/*
*   foreachkey
*/
static struct fek_str{
	pointer collect;
	pointer next;
}*fek_ctxt = NULL;

static void foreachkey_push(pointer collect){
	struct fek_str *p = Memory.alloc(sizeof(struct fek_str));
	p->collect = collect;
	p->next = fek_ctxt;
	fek_ctxt = p;
}

static bool foreachkey_pop(void){
	if(fek_ctxt){
		pointer node = fek_ctxt;
		fek_ctxt = fek_ctxt->next;
		Memory.free(node);
		return true;
	}
	return false;
}

INLINE bool TONIGHT initForeachkey(pointer collect){
	foreachkey_push(collect);
	return true;
}

bool TONIGHT foreachkeyIterator(pointer var){
    pointer p = fek_ctxt->collect;
	if(Collection.next(p)){
		Collection.currentKey(p, var);
		return true;
	}
	else{
		Collection.reset(p);
		foreachkey_pop();
		return false;
	}
}

/*
*   foreach
*/
static struct fe_str{
	pointer collect;
	pointer next;
}*fe_ctxt = NULL;

static void foreach_push(pointer collect){
	struct fe_str *p = Memory.alloc(sizeof(struct fe_str));
	p->collect = collect;
	p->next = fe_ctxt;
	fe_ctxt = p;
}

static bool foreach_pop(void){
	if(fe_ctxt){
		pointer node = fe_ctxt;
		fe_ctxt = fe_ctxt->next;
		Memory.free(node);
		return true;
	}
	return false;
}

INLINE bool TONIGHT initForeach(pointer collect){
	foreach_push(collect);
	return true;
}

bool TONIGHT foreachIterator(pointer var){
    pointer p = fe_ctxt->collect;
	if(Collection.next(p)){
		Collection.currentValue(p, var);
		return true;
	}
	else{
		Collection.reset(p);
		foreach_pop();
		return false;
	}
}
