#ifndef ___TONIGHT_NAMESPACE___
    #define ___TONIGHT_NAMESPACE___

	typedef struct IO *__Console_set;
	typedef struct IO *__File_set;
	typedef struct IO *__String_set;
	typedef struct IO *__Object_set;
	typedef struct IO *__Error_set;
	typedef struct IO_set *__Std_set;
	typedef struct IO_set *__Wide_set;
	typedef struct __Locale_set *__Locale_set;
	typedef struct __Random_set *__Random_set;
	typedef struct __Color_set *__Color_set;
    typedef struct __Timer_set *__Timer_set;
    typedef struct __Util_set *__Util_set;
    typedef struct __Encode_set *__Encode_set;
    typedef struct __Callback_set *__Callback_set;
    typedef struct __Shared_set *__Shared_set;
    typedef struct __Classes_set *__Classes_set;
    typedef struct __Extension_set *__Extension_set;

	/* struct Resources */
	struct Resources{
		__Std_set Std;
		__Wide_set Wide;
		__Object_set Object;
		__Random_set Random;
        __Color_set Color;
        __Timer_set Timer;
		__Conversor_set Conversor;
		__Locale_set Locale;
		__Util_set Util;
		__Encode_set Encode;
        __Callback_set Callback;
        __Shared_set Shared;
        __Classes_set Classes;
        __Extension_set Extension;
	};

	struct __Locale_set{
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

	struct IO_set{
        __Console_set Console;
        __File_set File;
        __String_set String;
        __Object_set Object;
        __Error_set Error;
    };

    typedef RandomicMaker __Simple_set;
    typedef RandomicMaker __Limit_set;
    typedef RandomicMaker __Range_set;

    struct __Random_set{
        __Simple_set Simple;
        __Limit_set Limit;
        __Range_set Range;
    };

	struct __Color_set{
        ColorCreate Console;
    };

    struct __Timer_set{
        TimerCreate Now;
    };

    typedef pointer __DefaultFunctionPointer_set;
    typedef void (*__assert_set)(bool);
    typedef void (*__checkErrno_set)(void);
    typedef string (*__password_set)(int);
    typedef void (*__clearScreen_set)(void);
    typedef int (*__getKey_set)(void);
    typedef int (*__getKeyEcho_set)(void);
    typedef bool (*__pressKey_set)(void);
    typedef void (*__sleep_set)(unsigned int);
    typedef void (*__position_set)(int, int);

    struct __Util_set{
	    pointer DefaultFunctionPointer;
	    void (*assert)(bool);
		void (*checkErrno)(void);
		string (*password)(int);
		void (*clearScreen)(void);
		int (*getKey)(void);
		int (*getKeyEcho)(void);
		bool (*pressKey)(void);
		void (*sleep)(unsigned int);
		void (*position)(int, int);
    };

    struct __Encode_set{
        void (*enableSTD)(file);
        void (*enableUTF8)(file);
    };

    struct __Callback_set{
        void (* setMalloc)(P_pointer);
        void (* setCalloc)(P_pointer);
        void (* setRealloc)(P_pointer);
        void (* setFree)(P_void);
    };

    struct __Shared_set{
        void (* close)(pointer);
        pointer (* open)(string);
        pointer (* get)(pointer, string);
    };

#endif // ___TONIGHT_NAMESPACE___
