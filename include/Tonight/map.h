/*
*	File: map.h
*	This file includes the Map library, a Tonight-based library to object-oriented threaded list string-mapped.
*
*	Copyright (C)  2019  Thiago Fernandes Leal.
*	Permission is granted to copy, distribute and/or modify this document
*	under the terms of the GNU Free Documentation License, Version 1.3
*	or any later version published by the Free Software Foundation;
*	with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
*	A copy of the license is included in the section entitled "GNU
*	Free Documentation License".
*/

#include "set.h"

#ifndef TONIGHT_MAP_H
#	define	TONIGHT_MAP_H

    EXCEPTION MapException;

    typedef void (* MapItemFreeCallBack)(pointer);

    struct map_item {
        pointer value;
        string index;
    };

    struct map_node {
        struct map_item item;
        struct map_node *next;
    };

	struct Map {
	    struct map_node *list;
	    size_t size;
	    MapItemFreeCallBack freeCallback;
	};

	struct IMap {
	    void (* set)(string, pointer);
	    pointer (* get)(string);
	    bool (* isset)(string);
	    void (* unset)(string);
	    size_t (* size)(void);
	    void (* setFreeCallBack)(MapItemFreeCallBack);
	};

	interface(IMap);
	Class(Map $extends Set $implements IMap);

#endif
