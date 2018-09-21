/*
*	This file is part of the Tonight library
*	
*	File: tonight.h
*	This file includes the Tonight library.
*	
*	Copyright (C)  2018  Thiago Fernandes Leal.
*	Permission is granted to copy, distribute and/or modify this document
*	under the terms of the GNU Free Documentation License, Version 1.3
*	or any later version published by the Free Software Foundation;
*	with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
*	A copy of the license is included in the section entitled "GNU
*	Free Documentation License".
*/

#ifndef TONIGHT_LIBRARY
#	define TONIGHT_LIBRARY

#	include <stdio.h>
#	include <setjmp.h>
#	include <stdlib.h>

#	ifdef __cplusplus
		extern "C"{
#	endif
	
#			include "tonightdef.h"
#			include "tonightOO.h"
	
			/* Objects */
			extern const TONIGHT struct __New New;
			extern const TONIGHT struct __Array Array;
			extern const TONIGHT struct __Matrix Matrix;
			extern const TONIGHT struct Resources Tonight;
			
			/* Exceptions */
			extern EXCEPTION TONIGHT GenericException;
			extern EXCEPTION TONIGHT AssertException;
			extern EXCEPTION TONIGHT ErrnoException;
			extern EXCEPTION TONIGHT MemoryAllocException;
			extern EXCEPTION TONIGHT ArrayIndexBoundException;
			extern EXCEPTION TONIGHT FileOpenException;
			extern EXCEPTION TONIGHT InputException;
			extern EXCEPTION TONIGHT ConvertException;
			extern EXCEPTION TONIGHT NotImplementException;
			
			/* Exceptions control */
			extern void TONIGHT THROW(EXCEPTION, string);
			extern pointer TONIGHT __create_try_context(void);
			extern bool TONIGHT __try_context(void);
			extern bool TONIGHT __function_try(void);
			extern bool TONIGHT __function_catch(EXCEPTION);
			extern bool TONIGHT __function_finally(void);
			
			extern INLINE Exception TONIGHT getException(void);
			extern INLINE void TONIGHT init_try(void);
			extern INLINE string TONIGHT Error(Exception);
			extern INLINE string TONIGHT Message(Exception);
			extern INLINE EXCEPTION TONIGHT ExceptionType(Exception);
			
			/* Tonight strings functions */
			extern bool TONIGHT equal(register string const, register string const);
			extern string TONIGHT toString(char ARRAY);
			extern string TONIGHT concat(string, ...);
			extern string TONIGHT s_cs(char);
			extern string TONIGHT s_bs(bool);
			extern string TONIGHT s_is(int);
			extern string TONIGHT s_fs(float);
			extern string TONIGHT s_ds(double);
			extern string TONIGHT s_fsf(float, int);
			extern string TONIGHT s_dsf(double, int);
			
			extern retString TONIGHT retConcat(string, ...);
			extern retString TONIGHT cs(char);
			extern retString TONIGHT bs(bool);
			extern retString TONIGHT is(int);
			extern retString TONIGHT fs(float);
			extern retString TONIGHT ds(double);
			extern retString TONIGHT fsf(float, int);
			extern retString TONIGHT dsf(double, int);
	
#	ifdef __cplusplus
		}
#	endif
#endif
