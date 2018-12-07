/*
*	This file is part of the Tonight library
*	
*	File: tonightdef.h
*	This file defines the types and data structures.
*	
*	Copyright (C)  2018  Thiago Fernandes Leal.
*	Permission is granted to copy, distribute and/or modify this document
*	under the terms of the GNU Free Documentation License, Version 1.3
*	or any later version published by the Free Software Foundation;
*	with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
*	A copy of the license is included in the section entitled "GNU
*	Free Documentation License".
*/

#ifndef TONIGHT_DEFINITIONS
#	define TONIGHT_DEFINITIONS

#	ifndef TONIGHT_LIBRARY
#		error "Include the Tonight library with #include<Tonight/tonight.h>"
#	endif

#	define	TONIGHT
#	define	NO_CALL

/* Definitions */
#	ifdef key_right
#		undef key_right
#	endif
#	ifdef key_left
#		undef key_left
#	endif
#	ifdef key_up
#		undef key_up
#	endif
#	ifdef key_down
#		undef key_down
#	endif
#	ifdef key_ESC
#		undef key_ESC
#	endif
#	ifdef key_ENTER
#		undef key_ENTER
#	endif
#	ifdef key_SPACE
#		undef key_SPACE
#	endif
#	ifdef key_BS
#		undef key_BS
#	endif

#	ifdef _WIN32
#		define key_right	295
#		define key_left		293
#		define key_up		294
#		define key_down		296
#		define key_ESC		27
#		define key_ENTER	13
#		define key_SPACE	32
#		define key_BS		8
#	else
#		define key_right	185
#		define key_left		186
#		define key_up		183
#		define key_down		184
#		define key_ESC		27
#		define key_ENTER	10
#		define key_SPACE	32
#		define key_BS		127
#	endif

#	define $Empty(Type)	((Type){0})
#	define $end			((string)0)
#	define ARRAY		*
#	define MATRIX		**
#	define getText(str) ((string)&((str).Text)[0])

#	define $throws
#	define TRY	setjmp(__create_try_context());while(__try_context())if(__function_try())
#	define CATCH(exception)	else if(__function_catch(exception))
#	define FINALLY	else if(__function_finally())
#	define Define_Exception(exc, msg, super)	static EXCEPTION_DEFINE __##exc = {msg, &super};\
												EXCEPTION exc = &__##exc

#	ifndef __cplusplus
#		define and	&&
#		define or	||
#		define new	New.
#		define try	TRY
#		define catch	CATCH
#		define finally	FINALLY
#		define throw	THROW
#		define using	USING
#	endif

#	if (defined __GNUC_GNU_INLINE || defined __cplusplus)
#		define INLINE	inline
#	else
#		define INLINE
#		define inline
#	endif

#	define	NORMAL

#	ifdef __cplusplus
#		define OptionalArgs	...
#	else
#		define OptionalArgs
#	endif

#	define	__using__(var, from, freely...)	__create_using_context(sizeof var, &var);\
											var = from;\
											while(__function_using(&var, ((Freely){freely}).free))
#	define USING(_arg_)		__using__(_arg_)

#	define __forindex__(ind, array)	for(ind=0;ind<Array.length(array);ind++)
#	define	forindex(_args_)	__forindex__(_args_)

#	define __foreach__(var, array)	for(initForeach(); foreachIterator(&var, array);)
#	define	foreach(_args_)		__foreach__(_args_)

#	define	__application_start_with__(_main, _func, _mod...)	_mod int _main(OptionalArgs);\
																int main(int argc, string argv[]){\
																	return _func(_main, argc, argv);\
																}
#	define	APPLICATION_START_WITH(_args_)	__application_start_with__(_args_)

#	define $in		,
#	define $as		,
#	define $with	,

#	define	$c(arg)	getText(cs(arg))
#	define	$b(arg)	getText(bs(arg))
#	define	$i(arg)	getText(is(arg))
#	define	$f(arg)	getText(fs(arg))
#	define	$d(arg)	getText(ds(arg))
#	define	$s(arg)	getText(arg)
#	define	$ff(arg, n)	getText(fsf(arg, n))
#	define	$df(arg, n)	getText(dsf(arg, n))
#	define	$F(format, args...)	getText(formated(format, args))

#	define	$cp(arg)		getText(cps(arg))
#	define	$bp(arg)		getText(bps(arg))
#	define	$ip(arg)		getText(ips(arg))
#	define	$fp(arg)		getText(fps(arg))
#	define	$dp(arg)		getText(dps(arg))
#	define	$sp(arg)		getText((*arg))
#	define	$fpf(arg, n)	getText(fpsf(arg, n))
#	define	$dpf(arg, n)	getText(dpsf(arg, n))

#	define	$lc(arg)	getText(cls(arg))
#	define	$lb(arg)	getText(bls(arg))
#	define	$li(arg)	getText(ils(arg))
#	define	$lf(arg)	getText(fls(arg))
#	define	$ld(arg)	getText(dls(arg))
#	define	$ls(arg)	getText(arg)
#	define	$lff(arg, n)	getText(flsf(arg, n))
#	define	$ldf(arg, n)	getText(dlsf(arg, n))
#	define	$lF(format, args...)	getText(longFormated(format, args))

/* data types definitions */
#	ifndef __cplusplus
		typedef unsigned char bool;
#		define true	0x1
#		define false	0x0
#	endif
	typedef unsigned char u_char, byte;
	typedef	char *string;
	typedef void *pointer, *file;
	typedef struct str_Intern_Object	Intern_Object, *object;
	typedef void (*P_void)	(OptionalArgs);
	typedef char (*P_char)	(OptionalArgs);
	typedef bool (*P_bool)	(OptionalArgs);
	typedef int (*P_int)	(OptionalArgs);
	typedef float (*P_float)	(OptionalArgs);
	typedef double (*P_double)	(OptionalArgs);
	typedef char* (*P_string)	(OptionalArgs);
	typedef void* (*P_pointer)(OptionalArgs);
	typedef object (*P_object)	(OptionalArgs);
	
	typedef struct{
		char Text[101];
	}retString;
	
	typedef struct{
		char Text[1001];
	}long_retString;
	
	typedef retString (*P_retString)(OptionalArgs);
	typedef long_retString (*P_long_retString)(OptionalArgs);
	
	typedef struct tm* Time;
	typedef Time (*P_Time)(OptionalArgs);
	
	/* Exceptions */
	typedef struct str_EXCEPTION EXCEPTION_DEFINE, *EXCEPTION;
	typedef struct __struct_exception *Exception;
	
	struct str_EXCEPTION{
		const string error_name;
		EXCEPTION *_super;
	};
	
	/* Objects structs */
	typedef struct str_Class{
		const size_t size;
		void (* ctor)(object, __builtin_va_list *);
		void (* dtor)(object);
	}*Class;
	
	struct str_Intern_Object{
		pointer obj;
		Class class_pointer;
	};
	
	/* cast */
	typedef struct{
		size_t original;
		size_t result;
		void (* parse)(pointer, pointer);
	}cast, (* P_cast)(OptionalArgs);
	
#	define __DefineCast__(_cast, typeFrom, typeTo, _arg...)	static void _cast##_##cast\
															(pointer from, pointer to)\
															{*(typeTo*)to = (typeTo)(*(typeFrom*)from);}\
															_arg cast _cast = (cast){\
															sizeof(typeFrom),\
															sizeof(typeTo),\
															_cast##_##cast}
#	define DefineCast(__args__)	__DefineCast__(__args__)
	
	/* "Class" Input */
	typedef struct{
		pointer ReadChar;
		pointer ReadInt;
		pointer ReadFloat;
		pointer ReadDouble;
		pointer Read;
		pointer ReadLine;
		pointer ClearInputBuffer;
		pointer IgnoreString;
		pointer IgnoreChar;
	}Input;
	
	/* "Class" Output */
	typedef struct{
		pointer WriteText;
		pointer WriteTextln;
		pointer Write;
		pointer Writeln;
		pointer Writeargln;
		pointer newLine;
		pointer newMultipleLines;
		pointer SetBuffer;
		pointer ClearOutputBuffer;
	}Output;
	
	/* struct IO */
	struct IO{
		Input Input;
		Output Output;
	};
	
	/* Class Scanner */
	typedef struct{
		char (*nextChar)(OptionalArgs);
		int (*nextInt)(OptionalArgs);
		float (*nextFloat)(OptionalArgs);
		double (*nextDouble)(OptionalArgs);
		string (*next)(OptionalArgs);
		string (*nextLine)(OptionalArgs);
		void (*clear)(OptionalArgs);
		void (*ignore)(OptionalArgs);
		void (*ignoreChar)(OptionalArgs);
	}Scanner;
	
	/* Class Writer */
	typedef struct{
		void (*text)(OptionalArgs);
		void (*textln)(OptionalArgs);
		void (*print)(OptionalArgs);
		void (*println)(OptionalArgs);
		void (*printargln)(OptionalArgs);
		void (*nl)(OptionalArgs);
		void (*nls)(OptionalArgs);
		void (*buffer)(OptionalArgs);
		void (*clear)(OptionalArgs);
	}Writer;
	
	/* Interface IScanner */
	typedef struct{
		string (*getString)(object);
		void (*setString)(object, string);
	}IScanner;
	
	/* Interface IWriter */
	typedef struct{
		void (*addText)(object, string);
		void (*clear)(object);
	}IWriter;
	
	/* Class RandomicMaker */
	typedef struct{
		pointer MakeRandomicChar;
		pointer MakeRandomicInt;
		pointer MakeRandomicFloat;
		pointer MakeRandomicDouble;
	}RandomicMaker;
	
	/* Class Random */
	typedef struct{
		char (*nextChar)(OptionalArgs);
		int (*nextInt)(OptionalArgs);
		float (*nextFloat)(OptionalArgs);
		double (*nextDouble)(OptionalArgs);
	}Random;
	
	/* Class Timer */
	typedef struct{
		pointer GetTime;
		pointer TimeHours;
		pointer TimeMinutes;
		pointer TimeSeconds;
		pointer TimeMonth;
		pointer TimeDay_month;
		pointer TimeDay_week;
		pointer TimeDay_year;
		pointer TimeYear;
	}TimerCreate;
	
	/* Class Time */
	typedef struct{
		Time (*getTime)(OptionalArgs);
		int (*hours)(OptionalArgs);
		int (*minutes)(OptionalArgs);
		int (*seconds)(OptionalArgs);
		int (*month)(OptionalArgs);
		int (*day_month)(OptionalArgs);
		int (*day_week)(OptionalArgs);
		int (*day_year)(OptionalArgs);
		int (*year)(OptionalArgs);
	}Timer;
	
	/* Class CreateColor */
	typedef struct{
		pointer textColor;
		pointer backgroundColor;
		pointer bothColors;
	}ColorCreate;
	
	/* Class Colors */
	typedef struct{
		void (*text)(OptionalArgs);
		void (*background)(OptionalArgs);
		void (*both)(OptionalArgs);
	}Painter;
	
	/* Conversor */
	typedef struct{
		char (*toChar)(string);
		byte (*toByte)(string);
		bool (*toBool)(string);
		int (*toInt)(string);
		float (*toFloat)(string);
		double (*toDouble)(string);
		string (*fromChar)(char);
		string (*fromByte)(byte);
		string (*fromBool)(bool);
		string (*fromInt)(int);
		string (*fromFloat)(float);
		string (*fromDouble)(double);
		string (*fromTime)(Time);
	}Conversor;
	
	/* Constructors */
	struct __New{
		Scanner (*Scanner)(Input);
		Writer (*Writer)(Output);
		Random (*Random)(RandomicMaker);
		Timer (*Timer)(TimerCreate);
		Painter (*Painter)(ColorCreate);
		object (*Object)(Class, ...);
		
		char* (*Char)(char);
		byte* (*Byte)(byte);
		bool* (*Bool)(bool);
		int* (*Int)(int);
		float* (*Float)(float);
		double* (*Double)(double);
		string* (*String)(string);
		pointer (*Pointer)(pointer);
	};
	
	typedef struct{
		void (* free)(OptionalArgs);
	}Freely;
	
	struct __Array{
		void	(* free)(pointer);
		int		(* length)(pointer);
		size_t	(* size)(pointer);
		pointer	(* access)(pointer, int);
		string	(* toString)(pointer, P_retString, string);
		pointer	(* convert)(pointer, cast);
		
		char* (*Char)(int);
		byte* (*Byte)(int);
		bool* (*Bool)(int);
		int* (*Int)(int);
		float* (*Float)(int);
		double* (*Double)(int);
		string* (*String)(int);
		object* (*Object)(int);
		pointer* (*Pointer)(int);
		pointer	(*Generic)(size_t, int);
	};
	
	struct __Matrix{
		void (* free)(pointer);
		char** (*Char)(int, int);
		byte** (*Byte)(int, int);
		bool** (*Bool)(int, int);
		int** (*Int)(int, int);
		float** (*Float)(int, int);
		double** (*Double)(int, int);
		string** (*String)(int, int);
		object** (*Object)(int, int);
		pointer** (*Pointer)(int, int);
		pointer	(*Generic)(size_t, int, int);
	};
	
	struct __Memory{
		void	(* free)(pointer);
		pointer	(* alloc)(size_t);
		pointer	(* realloc)(pointer, size_t);
		size_t	(* size)(pointer);
		pointer	(* copy)(pointer);
	};
	
	struct __String{
		void (* free)(string);
		string (* formated)(const string, ...);
		string (* copy)(string);
		string (* concatenate)(string, string);
		string (* upper)(const string);
		string (* lower)(const string);
		string (* trim)(const string);
		string* (* split)(const string, const string);
		size_t (* length)(const string);
		int (* compare)(const string, const string);
	};
	
	struct __File{
		file (* open)(string, string);
		void (* close)(file);
		void (* rewind)(file);
		bool (* end)(file);
		
		const struct{
			const string read;
			const string write;
			const string append;
		}Mode;
	};
	
	struct __Object{
		void (* free)(object);
		object (* instance)(Class, ...);
		Class (* getClass)(object);
		size_t (* getSize)(object);
		object (* copy)(object);
	};
	
	/* Keys */
	struct __Key{
		int Right;
		int Left;
		int Up;
		int Down;
		int Escape;
		int Enter;
		int Space;
		int BackSpace;
	};
	
	/* Exit codes */
	struct __Exit{
		int Success;
		int Failure;
		void (* With)(int);
		void (* WithSuccess)(void);
		void (* WithFail)(void);
	};
	
	struct Locale{
		int (* getCategory)(OptionalArgs);
		void (* setCategory)(OptionalArgs);
		string (* getName)(OptionalArgs);
		void (* setName)(OptionalArgs);
		string (* set)(OptionalArgs);
		string (* get)(OptionalArgs);
		
		struct{
			int All;
			int Collate;
			int Type;
			int Monetary;
			int Numeric;
			int Time;
		}Category;
	};
	
	/* struct Resources */
	struct Resources{
		const struct{
			const struct IO Console;
			const struct IO File;
			const struct IO String;
			const struct IO Object;
			const struct IO Error;
			const struct{
				RandomicMaker Simple;
				RandomicMaker Limit;
				RandomicMaker Range;
			}Random;
			const TimerCreate TimeNow;
		}Std;
		
		const struct{
			ColorCreate Color;
		}Resources;
		
		const Conversor Convert;
		const struct Locale Locale;
		const pointer DefaultFunctionPointer;
		
		const struct{
			u_char (* normalizeChar)(int);
			string (* normalizeString)(string);
			u_char (* upper)(int);
			u_char (* lower)(int);
			bool (* isupper)(int);
			bool (* islower)(int);
		}ASCII;
		
		void (*assert)(bool);
		void (*checkErrno)(void);
		string (*password)(int);
		void (*clearScreen)(void);
		int (*getKey)(void);
		int (*getKeyEcho)(void);
		bool (*pressKey)(void);
		void (*sleep)(unsigned int);
		void (*position)(int, int);
		void (*initRandom)(void);
		
		const struct{
			void (* setMalloc)(P_pointer);
			void (* setCalloc)(P_pointer);
			void (* setRealloc)(P_pointer);
			void (* setFree)(P_void);
		}Callback;
	};
	
#endif
