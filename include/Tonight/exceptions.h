#ifndef ___TONIGHT_EXCEPTIONS___
#   define ___TONIGHT_EXCEPTIONS___

#	include <setjmp.h>

#   ifdef __cplusplus
        extern "C"{
#   endif // __cplusplus

#	ifdef  $throws
#	    undef  $throws
#   endif
#	ifdef  Try
#	    undef  Try
#   endif
#	ifdef  Catch
#	    undef  Catch
#   endif
#	ifdef  Finally
#	    undef  Finally
#   endif
#	ifdef  ___Define_Exception___
#	    undef  ___Define_Exception___
#   endif
#	ifdef  Define_Exception
#	    undef Define_Exception
#   endif

#   ifndef __cplusplus
#		ifdef try
#		    undef try
#       endif
#		ifdef catch
#	        undef catch
#       endif
#		ifdef finally
#   		undef finally
#       endif
#		ifdef throw
#		    undef throw
#       endif
#	endif

#	define  Throw(args...)      __Throw__(\
                                    first(args),\
                                    second(args, "Exception throwed"),\
                                    third(args, NULL, NULL),\
                                    fourth(args, NULL, NULL, NULL)\
                                )
#	define  Try                 if(setjmp(__create_try_context())||1)while(__try_context())if(__function_try())
#	define  Catch(exception)    else if(__function_catch(exception))
#	define  Finally             else if(__function_finally())

#	define  ___Define_Exception___(exc, msg, super) static EXCEPTION_DEFINE __##exc = {msg, &super};\
                                                    EXCEPTION exc = &__##exc
#	define Define_Exception(_args_)                 ___Define_Exception___(_args_)

#   ifndef __cplusplus
#		define try      Try
#	    define catch	Catch
#   	define finally	Finally
#		define throw	Throw
#	endif

    /* Exceptions */
    typedef struct str_EXCEPTION EXCEPTION_DEFINE, *EXCEPTION;
    typedef struct __struct_exception *Exception;

    struct str_EXCEPTION{
        const string error_name;
        EXCEPTION *_super;
    };

    extern EXCEPTION TONIGHT GenericException;
    extern EXCEPTION TONIGHT TestException;
    extern EXCEPTION TONIGHT AssertException;
    extern EXCEPTION TONIGHT ErrnoException;
    extern EXCEPTION TONIGHT NullArgumentException;
    extern EXCEPTION TONIGHT MemoryAllocException;
    extern EXCEPTION TONIGHT ArrayIndexBoundException;
    extern EXCEPTION TONIGHT FileOpenException;
    extern EXCEPTION TONIGHT InputException;
    extern EXCEPTION TONIGHT ConvertException;
    extern EXCEPTION TONIGHT NotImplementException;
    extern EXCEPTION TONIGHT ArgumentException;
    extern EXCEPTION TONIGHT IllegalAccessException;
    extern EXCEPTION TONIGHT ApplicationException;

    /* Exceptions control */
    extern  void    TONIGHT NO_CALL __Throw__(EXCEPTION, string, pointer, pointer);
    extern  pointer TONIGHT NO_CALL __create_try_context(void);
    extern  bool    TONIGHT NO_CALL __try_context(void);
    extern  bool    TONIGHT NO_CALL __function_try(void);
    extern  bool    TONIGHT NO_CALL __function_catch(EXCEPTION);
    extern  bool    TONIGHT NO_CALL __function_finally(void);

    extern const struct ExceptionManager{
        string (* error)(Exception);
        string (* message)(Exception);
        EXCEPTION (* type)(Exception);
        pointer (* data)(Exception);
        pointer (* info)(Exception);
        Exception (* copy)(Exception);
        bool (* isType)(Exception, EXCEPTION);
        void (* throwException)(Exception);
        void (* free)(Exception);
    }ExceptionManager;

    extern const struct CurrentException{
        Exception (* get)(void);
        string (* error)(void);
        string (* message)(void);
        Exception (* copy)(void);
        EXCEPTION (* type)(void);
        pointer (* data)(void);
        pointer (* info)(void);
        void (* throwAgain)(void);
    }CurrentException;

    $_add(Exception, {
        string (* error)(void);
        string (* message)(void);
        EXCEPTION (* type)(void);
        Exception (* copy)(void);
        pointer (* data)(void);
        pointer (* info)(void);
        void (* throwAgain)(void);
    });

    #ifdef __cplusplus
        }
    #endif // __cplusplus

#endif // ___TONIGHT_EXCEPTIONS___
