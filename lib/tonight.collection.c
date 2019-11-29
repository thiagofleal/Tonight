#include <string.h>
#include "../include/tonight.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/collection.h"

INLINE ICollection* TONIGHT getICollection(pointer p){
	return *(ICollection**)(p - sizeof(ICollection*));
}

INLINE void TONIGHT setICollection(pointer p, ICollection *value){
	*(ICollection**)(p - sizeof(ICollection*)) = value;
}

static INLINE size_t TONIGHT Collection_lenght(pointer p){
	return getICollection(p)->length(p);
}

static INLINE size_t TONIGHT Collection_size(pointer p){
	return getICollection(p)->size(p);
}

static INLINE pointer TONIGHT Collection_access(pointer p, int i){
	return getICollection(p)->access(p, i);
}

static INLINE void TONIGHT Collection_index(pointer p, pointer v, int i){
	getICollection(p)->index(p, v, i);
}

/* Collection */
const ICollection Collection = {
	.length = Collection_lenght,
	.size = Collection_size,
	.access = Collection_access,
	.index = Collection_index
};

static INLINE size_t TONIGHT Collection_select_lenght(void){
	return Collection_lenght(getCurrentObject());
}

static INLINE size_t TONIGHT Collection_select_size(void){
	return Collection_size(getCurrentObject());
}

static INLINE pointer TONIGHT Collection_select_access(int i){
	return Collection_access(getCurrentObject(), i);
}

static INLINE void TONIGHT Collection_select_index(pointer v, int i){
	Collection_index(getCurrentObject(), v, i);
}

/* $(<obj> $as Collection) */
static const struct ___Collection_select_data___ data = {
	.length = Collection_select_lenght,
	.size = Collection_select_size,
	.access = Collection_select_access,
	.index = Collection_select_index
};

INLINE struct ___Collection_select_data___ ___Collection_select___(pointer collection){
    setCurrentObject(collection);
    return data;
};

/*
*   foreachkey
*/
static struct fek_str{
	int value;
	size_t length;
	pointer collect;
	pointer next;
}*fek_ctxt = NULL;

static void foreachkey_push(int value, size_t length, pointer collect){
	struct fek_str *p = Memory.alloc(sizeof(struct fek_str));
	p->value = value;
	p->length = length;
	p->collect = collect;
	p->next = fek_ctxt;
	fek_ctxt = p;
}

static int foreachkey_pop(void){
	if(fek_ctxt){
		pointer node = fek_ctxt;
		int ret = fek_ctxt->value;
		fek_ctxt = fek_ctxt->next;
		Memory.free(node);
		return ret;
	}
	return 0;
}

INLINE bool TONIGHT initForeachkey(pointer collect){
	foreachkey_push(-1, Collection.length(collect), collect);
	return true;
}

bool TONIGHT foreachkeyIterator(pointer var){
	if(++ fek_ctxt->value < fek_ctxt->length){
		Collection.index(fek_ctxt->collect, var, fek_ctxt->value);
		return true;
	}
	else{
		foreachkey_pop();
		return false;
	}
}

/*
*   foreach
*/
static struct fe_str{
	int value;
	size_t length;
	size_t size;
	pointer collect;
	pointer next;
}*fe_ctxt = NULL;

static void push(int value, size_t length, size_t size, pointer collect){
	struct fe_str *p = Memory.alloc(sizeof(struct fe_str));
	p->value = value;
	p->length = length;
	p->size = size;
	p->collect = collect;
	p->next = fe_ctxt;
	fe_ctxt = p;
}

static int pop(void){
	if(fe_ctxt){
		pointer node = fe_ctxt;
		int ret = fe_ctxt->value;
		fe_ctxt = fe_ctxt->next;
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
	if(++ fe_ctxt->value < fe_ctxt->length){
		memcpy(var, Collection.access(fe_ctxt->collect, fe_ctxt->value), fe_ctxt->size);
		return true;
	}
	else{
		pop();
		return false;
	}
}
