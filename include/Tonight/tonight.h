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
#	include <stdarg.h>

#	ifdef __cplusplus
		extern "C"{
#	endif

#			include "tonight.undef.h"
#			include "tonight.def.h"
#			include "tonight.OO.h"
			
			/* Objects */
			extern const TONIGHT struct __New New;
			extern const TONIGHT struct __Array Array;
			extern const TONIGHT struct __Matrix Matrix;
			extern const TONIGHT struct __Memory Memory;
			extern const TONIGHT struct __String String;
			extern const TONIGHT struct __String WideString;
			extern const TONIGHT struct __File File;
			extern const TONIGHT struct __Key Key;
			extern const TONIGHT struct __Exit Exit;
			extern const TONIGHT struct Resources Tonight;
			extern const TONIGHT ICollection Collection;
			
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
			extern void TONIGHT Throw(EXCEPTION, string);
			extern pointer TONIGHT NO_CALL __create_try_context(void);
			extern bool TONIGHT NO_CALL __try_context(void);
			extern bool TONIGHT NO_CALL __function_try(void);
			extern bool TONIGHT NO_CALL __function_catch(EXCEPTION);
			extern bool TONIGHT NO_CALL __function_finally(void);
			
			extern pointer TONIGHT NO_CALL __create_array(size_t, int, pointer);
			
			extern INLINE Exception TONIGHT getException(void);
			extern INLINE string TONIGHT Error(Exception);
			extern INLINE string TONIGHT Message(Exception);
			extern INLINE EXCEPTION TONIGHT ExceptionType(Exception);
			
			extern INLINE bool TONIGHT NO_CALL initForeach(void);
			extern bool TONIGHT NO_CALL foreachIterator(pointer, pointer);
			extern void TONIGHT NO_CALL __create_using_context(size_t, pointer);
			extern bool TONIGHT NO_CALL __function_using(pointer, P_void);
			
			/* Tonight strings functions */
			extern bool TONIGHT equal(register string const, register string const);
			extern string TONIGHT toString(pointer);
			extern pstring TONIGHT toWide(pointer);
			extern string TONIGHT concat(string, ...);
			extern string TONIGHT nconcat(int, string, ...);
			extern retString TONIGHT retConcat(string, ...);
			extern pstring TONIGHT wconcat(pstring, ...);
			extern pstring TONIGHT nwconcat(int, pstring, ...);
			extern retWideString TONIGHT wretConcat(pstring, ...);
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
			
			extern longRetString TONIGHT longRetConcat(string, ...);
			extern longRetString TONIGHT cls(char);
			extern longRetString TONIGHT bls(bool);
			extern longRetString TONIGHT ils(int);
			extern longRetString TONIGHT fls(float);
			extern longRetString TONIGHT dls(double);
			extern longRetString TONIGHT flsf(float, int);
			extern longRetString TONIGHT dlsf(double, int);
			extern longRetString TONIGHT longFormated(const string, ...);
			
			extern INLINE void TONIGHT checkArgumentPointer(pointer);
			extern INLINE ICollection * TONIGHT getICollection(pointer);
	
#	ifdef __cplusplus
		}
#	endif
#endif
