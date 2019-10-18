/*
*	This file is part of the Tonight library
*
*	File: tonight.h
*	This file includes the Tonight library.
*
*	Copyright   (C)   2019  Thiago Fernandes Leal.
*	Permission is granted to copy, distribute and/or modify this document
*	under the terms of the GNU Free Documentation License, Version 1.3
*	or any later version published by the Free Software Foundation;
*	with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
*	A copy of the license is included in the section entitled "GNU
*	Free Documentation License".
*/

#ifndef TONIGHT_LIBRARY
#	define TONIGHT_LIBRARY

#	include <stddef.h>
#	include <stdarg.h>

#	ifdef __cplusplus
		extern "C"{
#	endif

#	include "tonight.def.h"
#	include "tonight.OO.h"

    /* Objects */
    extern const TONIGHT struct __Key Key;
    extern const TONIGHT struct __Exit Exit;

    extern void TONIGHT NO_CALL __create_using_context(size_t, pointer);
    extern bool TONIGHT NO_CALL __function_using(pointer, P_void);

    extern void TONIGHT NO_CALL __create_with_context(pointer);
    extern bool TONIGHT NO_CALL __function_with(void);

    extern void TONIGHT NO_CALL __create_this_context(const Class);
    extern bool TONIGHT NO_CALL __function_this(void);

    extern INLINE pointer TONIGHT useContext(void);

    extern wstring TONIGHT toWide(pointer);
    extern wstring TONIGHT wconcat(wstring, ...);
    extern wstring TONIGHT nwconcat(size_t, wstring, ...);
    extern fixWideString TONIGHT wfixConcat(wstring, ...);
    extern INLINE void TONIGHT checkArgumentPointer(pointer);

#	ifdef __cplusplus
		}
#	endif
#endif
