/*
*	File: set.h
*	This file includes the Set class.
*
*	Copyright (C)  2018  Thiago Fernandes Leal.
*	Permission is granted to copy, distribute and/or modify this document
*	under the terms of the GNU Free Documentation License, Version 1.3
*	or any later version published by the Free Software Foundation;
*	with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
*	A copy of the license is included in the section entitled "GNU
*	Free Documentation License".
*/

#ifndef TONIGHT_SET_H
#	define	TONIGHT_SET_H

#   include "collection.h"

    struct ISet{
        ICollection * (* getCollection)(void);
        void (* setCollection)(ICollection);
    };

    interface(ISet);

    struct Set{
        ICollection *collection;
    };

    Class(Set $extends Object $implements ISet);

#endif
