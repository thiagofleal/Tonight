/*
*	File: list.h
*	This file includes the List library, a Tonight-based library to object-oriented threaded list.
*
*	Copyright (C)  2018  Thiago Fernandes Leal.
*	Permission is granted to copy, distribute and/or modify this document
*	under the terms of the GNU Free Documentation License, Version 1.3
*	or any later version published by the Free Software Foundation;
*	with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
*	A copy of the license is included in the section entitled "GNU
*	Free Documentation License".
*/

#ifndef TONIGHT_LIST_H
#	define	TONIGHT_LIST_H

	EXCEPTION IndexException;

	struct Node{
		pointer value;
		pointer next;
	};

	typedef void (* P_freeCallBack)(pointer);

	struct IList{
		void (* add)(pointer value);
		void (* addPos)(pointer value, int index);
		void (* remove)(int index);
		pointer (* get)(int index);
		int (* size)(void);
		pointer (* toArray)(void);
		object (* select)(condition);
		string (* toString)(P_retString, string);
		void (* setFreeCallBack)(P_freeCallBack);
	};

	interface(IList);

	struct List{
		struct Node *list;
		int size;
		P_freeCallBack freeCallBack;
	};

	Class(List $extends Set $implements IList);

#endif
