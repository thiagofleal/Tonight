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

#	include <setjmp.h>
#	include <stddef.h>	

#	ifdef __cplusplus
		extern "C"{
#	endif

#			include "tonightdef.h"
#			include "tonightOO.h"
			
			/* Objects */
			extern const TONIGHT struct __New New;
			extern const TONIGHT struct __Array Array;
			extern const TONIGHT struct __Matrix Matrix;
			extern const TONIGHT struct __Memory Memory;
			extern const TONIGHT struct __String String;
			extern const TONIGHT struct __File File;
			extern const TONIGHT struct __Key Key;
			extern const TONIGHT struct __Exit Exit;
			extern const TONIGHT struct Resources Tonight;
			extern TONIGHT struct __Locale Locale;
			
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
			extern EXCEPTION TONIGHT ArgumentException;
			extern EXCEPTION TONIGHT NullArgumentException;
			extern EXCEPTION TONIGHT ApplicationException;
			
			/* Exceptions control */
			extern void TONIGHT THROW(EXCEPTION, string);
			extern pointer TONIGHT NO_CALL __create_try_context(void);
			extern bool TONIGHT NO_CALL __try_context(void);
			extern bool TONIGHT NO_CALL __function_try(void);
			extern bool TONIGHT NO_CALL __function_catch(EXCEPTION);
			extern bool TONIGHT NO_CALL __function_finally(void);
			
			extern INLINE Exception TONIGHT getException(void);
			extern INLINE string TONIGHT Error(Exception);
			extern INLINE string TONIGHT Message(Exception);
			extern INLINE EXCEPTION TONIGHT ExceptionType(Exception);
			
			INLINE void TONIGHT NO_CALL initForeach(void);
			bool TONIGHT NO_CALL foreachIterator(pointer, pointer);
			
			/* Tonight strings functions */
			extern bool TONIGHT equal(register string const, register string const);
			extern string TONIGHT toString(pointer);
			extern string TONIGHT concat(string, ...);
			extern string TONIGHT nconcat(int, string, ...);
			extern string TONIGHT s_cs(char);
			extern string TONIGHT s_bs(bool);
			extern string TONIGHT s_is(int);
			extern string TONIGHT s_fs(float);
			extern string TONIGHT s_ds(double);
			extern string TONIGHT s_fsf(float, int);
			extern string TONIGHT s_dsf(double, int);
			
			extern INLINE string TONIGHT s_cps(char*);
			extern INLINE string TONIGHT s_bps(bool*);
			extern INLINE string TONIGHT s_ips(int*);
			extern INLINE string TONIGHT s_fps(float*);
			extern INLINE string TONIGHT s_dps(double*);
			extern INLINE string TONIGHT s_fpsf(float*, int);
			extern INLINE string TONIGHT s_dpsf(double*, int);
			
			extern retString TONIGHT retConcat(string, ...);
			extern retString TONIGHT cs(char);
			extern retString TONIGHT bs(bool);
			extern retString TONIGHT is(int);
			extern retString TONIGHT fs(float);
			extern retString TONIGHT ds(double);
			extern retString TONIGHT fsf(float, int);
			extern retString TONIGHT dsf(double, int);
			extern retString TONIGHT formated(const string, ...);
			
			extern INLINE retString TONIGHT cps(char*);
			extern INLINE retString TONIGHT bps(bool*);
			extern INLINE retString TONIGHT ips(int*);
			extern INLINE retString TONIGHT fps(float*);
			extern INLINE retString TONIGHT dps(double*);
			extern INLINE retString TONIGHT fpsf(float*, int);
			extern INLINE retString TONIGHT dpsf(double*, int);
			
			extern long_retString TONIGHT longRetConcat(string, ...);
			extern long_retString TONIGHT cls(char);
			extern long_retString TONIGHT bls(bool);
			extern long_retString TONIGHT ils(int);
			extern long_retString TONIGHT fls(float);
			extern long_retString TONIGHT dls(double);
			extern long_retString TONIGHT flsf(float, int);
			extern long_retString TONIGHT dlsf(double, int);
			extern long_retString TONIGHT longFormated(const string, ...);
			
			extern int TONIGHT NO_CALL TonightMode(P_int, register int, string[]);
			
			extern INLINE void TONIGHT checkArgumentPointer(pointer);
	
#	ifdef __cplusplus
		}
#	endif
#endif
