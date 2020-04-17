#include "../include/tonight.h"
#include "../include/Tonight/exceptions.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/collection.h"
#include "../include/Tonight/string.h"
#include "../include/Tonight/map.h"

Define_Exception(MapException $as "Map exception" $extends GenericException);

static pointer iterator(struct map_node *node){
	struct map_node *i;
	for(i = node; i->next; i = i->next);
	return i;
}

static struct map_item new_map_item(string index, pointer value){
    return (struct map_item){.index = index, .value = value};
}

static struct map_node * new_map_node(struct map_item value){
    struct map_node *node = Memory.alloc(sizeof(struct map_node));
    node->item = value;
    node->next = NULL;
    return node;
}

static void Map_add_node(object self, string index, pointer value){
    struct map_node *node;
    if( $$(self $as Map).size ){
        node = iterator( $$(self $as Map).list );
        node->next = new_map_node(new_map_item(index, value));
    }
    else{
        $$(self $as Map).list = new_map_node(new_map_item(index, value));
    }
    $$(self $as Map).size++;
}

static void Map_remove(object self, int index){
	int i;
    struct map_node *node = $$(self $as Map).list, *aux;

    if(index >= $$(self $as Map).size || index < 0){
        static string error = NULL;
        if(error)	Memory.free(error);
        error = String.concat("Impossible to remove the index ", is(index).Text, $end);
        throw(MapException, error);
    }

    if(!index){
        aux = node;
        node = node->next;
        $$(self $as Map).list = node;
    }
    else{
        struct map_node **p;
        for(i = 0; i < index - 1 && node->next; i++, node = node->next);
        p = (struct map_node**)&node->next;
        aux = *p;
        *p = (*p)->next;
    }

    if($$(self $as Map).freeCallback){
        String.free(aux->item.index);
        $$(self $as Map).freeCallback(aux->item.value);
    }

    Memory.free(aux);
    $$(self $as Map).size--;
}

extern int strcmp(const string, const string);

static bool Map_isset(string index){
    struct map_node *node;
    for(node = $$(this $as Map).list; node; node = node->next){
        if(!strcmp(index, node->item.index)){
            return true;
        }
    }
    return false;
}

static void Map_set(string index, pointer value){
    struct map_node *node;
    for(node = $$(this $as Map).list; node; node = node->next){
        if(!strcmp(index, node->item.index)){
            node->item.value = value;
            return;
        }
    }
    Map_add_node(this, toString(index), value);
}

static void Map_unset(string index){
    struct map_node *node;
    register unsigned int i = 0;
    for(node = $$(this $as Map).list; node; node = node->next){
        if(!strcmp(index, node->item.index)){
            Map_remove(this, i);
            return;
        }
        i++;
    }
}

static pointer Map_get(string index){
    struct map_node *node;
    for(node = $$(this $as Map).list; node; node = node->next){
        if(!strcmp(index, node->item.index)){
            return node->item.value;
        }
    }
    return NULL;
}

static unsigned int Map_size(void){
    return $$(this $as Map).size;
}

static void Map_setFreeCallBack(MapItemFreeCallBack callback){
    $$(this $as Map).freeCallback = callback;
}

static IMap Map_vtble = {
    .set = Map_set,
    .get = Map_get,
    .isset = Map_isset,
    .unset = Map_unset,
    .size = Map_size,
    .setFreeCallBack = Map_setFreeCallBack
};

static inline void Map_ICollection_currentValue(pointer collect, pointer var){
	*(pointer*)var = $$(collect $as Map).current->item.value;
}

static inline void Map_ICollection_currentKey(pointer collect, pointer var){
	*(string*)var = $$(collect $as Map).current->item.index;
}

static bool Map_ICollection_next(pointer collect){
    struct map_node **node = &$$(collect $as Map).current;
	if(*node){
        *node = (*node)->next;
	}else{
	    *node = $$(collect $as Map).list;
	}
	return *node ? true : false;
}

static inline void Map_ICollection_reset(pointer collect){
    $$(collect $as Map).current = NULL;
}

static ICollection Map_collection = {
	.currentValue = Map_ICollection_currentValue,
	.currentKey = Map_ICollection_currentKey,
	.next = Map_ICollection_next,
	.reset = Map_ICollection_reset
};

static void Map_constructor(pointer args){
	construct(superOf(Map));
	$$(this $as Map).list = NULL;
	$$(this $as Map).size = 0;
	setInterface(Map, Map_vtble);
	$(this $as Set)->setCollection(Map_collection);
	Map_ICollection_reset(this);
}

static void Map_destructor(void){
	while($$(this $as Map).size){
		Map_remove(this, 0);
	}

	destruct(superOf(Map));
}

static void IMap_set(string index, pointer value){
    Method(Map){
        getInterface(Map)->set(index, value);
    }
}

static pointer IMap_get(string index){
    pointer ret = $Empty(pointer);
    Method(Map){
        ret = getInterface(Map)->get(index);
    }
    return ret;
}

static bool IMap_isset(string index){
    bool ret = $Empty(bool);
    Method(Map){
        ret = getInterface(Map)->isset(index);
    }
    return ret;
}

static void IMap_unset(string index){
    Method(Map){
        getInterface(Map)->unset(index);
    }
}

static unsigned int IMap_size(void){
    unsigned int ret = $Empty(unsigned int);
    Method(Map){
        ret = getInterface(Map)->size();
    }
    return ret;
}

static void IMap_setFreeCallBack(MapItemFreeCallBack callback){
    Method(Map){
        getInterface(Map)->setFreeCallBack(callback);
    }
}

static IMap iMap = {
    .set = IMap_set,
    .get = IMap_get,
    .isset = IMap_isset,
    .unset = IMap_unset,
    .size = IMap_size,
    .setFreeCallBack = IMap_setFreeCallBack,
};

Constructor(Map, Map_constructor);
Destructor(Map, Map_destructor);

Define_Class(Map $extends Set $implements IMap $with iMap);
