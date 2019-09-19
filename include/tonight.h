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

#	include <stddef.h>
#	include <stdarg.h>

#	ifdef __cplusplus
		extern "C"{
#	endif

#			include "tonight.def.h"
#			include "tonight.OO.h"

			/* Objects */
			extern const TONIGHT struct __New New;
			extern const TONIGHT struct __String String;
			extern const TONIGHT struct __WideString WideString;
			extern const TONIGHT struct __Key Key;
			extern const TONIGHT struct __Exit Exit;

			extern void TONIGHT NO_CALL __create_using_context(size_t, pointer);
			extern bool TONIGHT NO_CALL __function_using(pointer, P_void);

			extern void TONIGHT NO_CALL __create_with_context(pointer);
			extern bool TONIGHT NO_CALL __function_with(void);

			extern void TONIGHT NO_CALL __create_this_context(const Class);
            extern bool TONIGHT NO_CALL __function_this(void);

			extern INLINE pointer TONIGHT useContext(void);

			/* Tonight strings functions */
			extern bool TONIGHT equal(register string const, register string const);
			extern string TONIGHT toString(pointer);
			extern wstring TONIGHT toWide(pointer);
			extern string TONIGHT concat(string, ...);
			extern string TONIGHT nconcat(size_t, string, ...);
			extern retString TONIGHT retConcat(string, ...);
			extern wstring TONIGHT wconcat(wstring, ...);
			extern wstring TONIGHT nwconcat(size_t, wstring, ...);
			extern retWideString TONIGHT wretConcat(wstring, ...);
			extern string TONIGHT s_cs(char);
			extern string TONIGHT s_bs(bool);
			extern string TONIGHT s_is(int);
			extern string TONIGHT s_fs(float);
			extern string TONIGHT s_ds(double);
			extern string TONIGHT s_fsf(float, int);
			extern string TONIGHT s_dsf(double, int);
			extern string TONIGHT s_ps(pointer);

			extern INLINE string TONIGHT s_cps(char*);
			extern INLINE string TONIGHT s_bps(bool*);
			extern INLINE string TONIGHT s_ips(int*);
			extern INLINE string TONIGHT s_fps(float*);
			extern INLINE string TONIGHT s_dps(double*);
			extern INLINE string TONIGHT s_fpsf(float*, int);
			extern INLINE string TONIGHT s_dpsf(double*, int);
			extern INLINE string TONIGHT s_pps(pointer*);

			extern retString TONIGHT retConcat(string, ...);
			extern retString TONIGHT cs(char);
			extern retString TONIGHT bs(bool);
			extern retString TONIGHT is(int);
			extern retString TONIGHT fs(float);
			extern retString TONIGHT ds(double);
			extern retString TONIGHT fsf(float, int);
			extern retString TONIGHT dsf(double, int);
			extern retString TONIGHT ps(pointer);
			extern retString TONIGHT formated(const string, ...);

			extern INLINE retString TONIGHT cps(char*);
			extern INLINE retString TONIGHT bps(bool*);
			extern INLINE retString TONIGHT ips(int*);
			extern INLINE retString TONIGHT fps(float*);
			extern INLINE retString TONIGHT dps(double*);
			extern INLINE retString TONIGHT fpsf(float*, int);
			extern INLINE retString TONIGHT dpsf(double*, int);
			extern INLINE retString TONIGHT pps(pointer*);

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

#	ifdef __cplusplus
		}
#	endif
#endif
