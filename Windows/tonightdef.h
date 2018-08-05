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
#		error "Include the Tonight library (tonight.h)"
#	endif

#	define	TONIGHT

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

#	define key_right	295
#	define key_left	293
#	define key_up		294
#	define key_down	296
#	define key_ESC		27
#	define key_ENTER	13
#	define key_SPACE	32
#	define key_BS		8
#	define end			((String)0)
#	define ARRAY		*
#	define MATRIX		**
#	define getText(str) ((String)&((str).Text)[0])

#	define throws
#	define TRY	setjmp(__create_try_context());while(__try_context())if(__function_try())
#	define CATCH(exception)	else if(__function_catch(exception))
#	define FINALLY	else if(__function_finally())
#	define Define_Exception(exc, msg, super)	EXCEPTION_DEFINE __##exc = {msg, &super};EXCEPTION exc = &__##exc

#	ifndef __cplusplus
#		define and	&&
#		define or	||
#		define new	New.
#		define try	TRY
#		define catch	CATCH
#		define finally	FINALLY
#		define throw	THROW
#	endif

#	if (defined __GNUC_GNU_INLINE || defined __cplusplus)
#		define INLINE	inline
#	else
#		define INLINE
#	endif

#	ifdef __cplusplus
#		define OptionalArgs	...
#	else
#		define OptionalArgs
#	endif

/* data types definitions */
#	ifndef __cplusplus
		typedef unsigned char bool;
#		define true	0x1
#		define false	0x0
#	endif
	typedef char* String;
	typedef void* pointer;
	typedef struct str_Intern_Object	Intern_Object, *Object;
	typedef void (*P_void)	(OptionalArgs);
	typedef char (*P_char)	(OptionalArgs);
	typedef bool (*P_bool)	(OptionalArgs);
	typedef int (*P_int)	(OptionalArgs);
	typedef float (*P_float)	(OptionalArgs);
	typedef double (*P_double)	(OptionalArgs);
	typedef char* (*P_String)	(OptionalArgs);
	typedef void* (*P_pointer)(OptionalArgs);
	typedef Object (*P_Object)	(OptionalArgs);
	
	typedef FILE *File;
	
	typedef struct{
		char Text[101];
	}retString;
	
	typedef struct{
		char Text[1001];
	}long_retString;
	
	typedef retString (*P_retString)(OptionalArgs);
	typedef long_retString (*P_long_retString)(OptionalArgs);
	
	/* Exceptions */
	typedef struct str_EXCEPTION EXCEPTION_DEFINE, *EXCEPTION;
	
	struct str_EXCEPTION{
		const String error_name;
		EXCEPTION *_super;
	};
	
	typedef struct __struct_exception{
		EXCEPTION exception;
		String message;
	}_Exception, *Exception;
	
	/* Objects structs */
	typedef struct str_Class{
		const size_t size;
		void (* ctor)(Intern_Object *, __builtin_va_list *);
		void (* dtor)(Intern_Object *);
	}*Class_Name;
	
	struct str_Intern_Object{
		pointer obj;
		Class_Name class_pointer;
	};
	
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
		pointer clearOutputBuffer;
	}Output;
	
	/* struct IO */
	struct IO{
		Input input;
		Output output;
	};
	
	/* Class Scanner */
	typedef struct{
		char (*nextChar)(OptionalArgs);
		int (*nextInt)(OptionalArgs);
		float (*nextFloat)(OptionalArgs);
		double (*nextDouble)(OptionalArgs);
		String (*next)(OptionalArgs);
		String (*nextLine)(OptionalArgs);
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
		String (*getString)(Object);
		void (*setString)(Object, String);
	}IScanner;
	
	/* Interface IWriter */
	typedef struct{
		void (*addText)(Object, String);
		void (*clear)(Object);
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
		char (*toChar)(String);
		bool (*toBool)(String);
		int (*toInt)(String);
		float (*toFloat)(String);
		double (*toDouble)(String);
		String (*fromChar)(char);
		String (*fromBool)(bool);
		String (*fromInt)(int);
		String (*fromFloat)(float);
		String (*fromDouble)(double);
		String (*formated)(const String, ...);
	}Conversor;
	
	/* Constructors */
	struct __New{
		Scanner (*Scanner)(Input);
		Writer (*Writer)(Output);
		Random (*Random)(RandomicMaker);
		Timer (*Timer)(TimerCreate);
		Painter (*Painter)(ColorCreate);
		File (*File)(String, String);
		Object (*Object)(Class_Name, ...);
		
		char* (*Char)(char);
		bool* (*Bool)(bool);
		int* (*Int)(int);
		float* (*Float)(float);
		double* (*Double)(double);
		String* (*String)(String);
		pointer (*Pointer)(pointer);
		pointer (*Memory)(size_t);
		
		struct{
			char* (*Char)(int);
			bool* (*Bool)(int);
			int* (*Int)(int);
			float* (*Float)(int);
			double* (*Double)(int);
			String* (*String)(int);
			Object* (*Object)(int);
			pointer* (*Pointer)(int);
		}array;
		
		struct{
			char** (*Char)(int, int);
			bool** (*Bool)(int, int);
			int** (*Int)(int, int);
			float** (*Float)(int, int);
			double** (*Double)(int, int);
			String** (*String)(int, int);
			Object** (*Object)(int, int);
			pointer** (*Pointer)(int, int);
		}matrix;
	};
	
	/* struct Resources */
	struct Resources{
		const struct{
			const struct IO console;
			const struct IO file;
			const struct IO string;
			const struct IO object;
			const Output error;
			const struct{
				RandomicMaker simple;
				RandomicMaker limit;
				RandomicMaker range;
			}random;
			const TimerCreate clock;
		}std;
		
		const struct{
			ColorCreate Color;
			Output Box;
		}resources;
		
		const Conversor Convert;
		const pointer DefaultFunctionPointer;
		
		void (*assert)(bool);
		void (*checkErrno)(void);
		String (*locale)(void);
		String (*password)(int);
		void (*clearScreen)(void);
		int (*getKey)(void);
		int (*getKeyEcho)(void);
		bool (*pressKey)(void);
		void (*sleep)(unsigned int);
		void (*position)(int, int);
		void (*initRandom)(void);
	};
	
#	undef OptionalArgs
#endif
