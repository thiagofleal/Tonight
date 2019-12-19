#include <errno.h>
#include <string.h>
#include "../include/tonight.h"
#include "../include/Tonight/exceptions.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/array.h"
#include "../include/Tonight/string.h"
#include "../include/Tonight/test.h"

static INLINE void TONIGHT Test_assert(bool test){
    if(!test) Throw(AssertException, "Assert test failed");
}

static INLINE void TONIGHT Test_assertMessage(bool test, string message){
    if(!test) Throw(AssertException, message);
}

static INLINE int TONIGHT Test_getError(void){
    return errno;
}

static INLINE void TONIGHT Test_checkError(void){
    if(errno) Throw(ErrnoException, "Error occurred with a C standard function", &errno, strerror(errno));
}

static INLINE void TONIGHT Test_checkErrorMessage(string message){
    if(errno) Throw(ErrnoException, message, &errno, strerror(errno));
}

static INLINE void TONIGHT Test_checkPointer(pointer test){
    if(!test) Throw(NullArgumentException, "Null argument", test);
}

static INLINE void TONIGHT Test_checkPointerMessage(pointer test, string message){
    if(!test) Throw(NullArgumentException, message, test);
}

static test_p TONIGHT Test_create(void){
    test_p p = Memory.alloc(sizeof(test_t));
    p->arg = NULL;
    p->argToString = NULL;
    p->func = NULL;
    p->name = NULL;
    return p;
}

static INLINE void TONIGHT Test_free(test_p data){
    Memory.free(data);
}

static test_result* TONIGHT Test_run(test_p test){
    bool b_free = false;
    size_t i, length;
    test_result ARRAY ret = NULL;
    Test.checkPointerMessage(test, "Null test");
    Test.checkPointerMessage(test->func, "Null function pointer");
    if(test->arg){
        length = Array.length(test->arg);
    }else{
        length = 1;
        test->arg = Array.Pointer(1);
        *(pointer*)test->arg = NULL;
        b_free = true;
    }
    ret = Array.Generic(sizeof(test_result), length);
    for(i = 0; i < length; i++){
        pointer p = Array.access(test->arg, i);
        bool b_arg = test->argToString ? true : false;
        fixString arg = b_arg ? test->argToString(p) : FixString.empty;
        string append = b_arg ? String.formated(" => (%s)", getText(arg)) : String.copy("");
        Try{
            ret[i].test = test;
            test->func(p);
            ret[i].success = true;
            ret[i].except = NULL;
            ret[i].info = String.formated("TEST SUCCESS: %s%s", test->name, append);
        }Catch(TestException){
            Exception e = CurrentException.get();
            Try{
                Throw(
                    ExceptionManager.type(e),
                    ExceptionManager.message(e),
                    test,
                    test->name
                );
            }Catch(GenericException){
                ret[i].except = CurrentException.get();
                ret[i].info = String.formated("TEST FAILED: %s%s", test->name, append);
            }
        }Catch(GenericException){
            ret[i].except = CurrentException.get();
            ret[i].info = String.formated("EXCEPTION: %s%s", test->name, append);
        }Finally{
            ret[i].success = false;
        }
        String.free(append);
    }
    if(b_free){
        Array.free(test->arg);
        test->arg = NULL;
    }
    return ret;
}

const struct __Test Test = {
    .assert = Test_assert,
    .assertMessage = Test_assertMessage,
    .getError = Test_getError,
    .checkError = Test_checkError,
    .checkErrorMessage = Test_checkErrorMessage,
    .checkPointer = Test_checkPointer,
    .checkPointerMessage = Test_checkPointerMessage,
    .create = Test_create,
    .free = Test_free,
    .run = Test_run
};
