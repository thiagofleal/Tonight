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

static INLINE TestResultItem* array_TestResultItem(size_t length){
    return Array.Generic(sizeof(TestResultItem), length);
}

static void init_TestResult(TestResult *res, size_t length){
    res->results = array_TestResultItem(length);
    res->count.except = 0;
    res->count.failed = 0;
    res->count.success = 0;
    res->count.tests = 0;
    res->statistic.success = 0.0;
    res->statistic.failed = 0.0;
    res->statistic.except = 0.0;
}

static TestResult TONIGHT Test_run(P_void func){
    TestResult ret;
    Test.checkPointer(func);
    init_TestResult(&ret, 1);
    ret.results[0].data = NULL;
    ret.results[0].except = NULL;
    ret.results[0].success = true;
    Try{
        func();
        ret.count.success = 1;
        ret.statistic.success = 1.0;
    }Catch(TestException){
        ret.count.failed = 1;
        ret.statistic.failed = 1.0;
    }Catch(GenericException){
        ret.count.except = 1;
        ret.statistic.except = 1.0;
    }Finally{
        ret.results[0].except = CurrentException.get();
        ret.results[0].success = false;
    }
    return ret;
}

static TestResult TONIGHT Test_runArguments(P_void func, pointer args){
    TestResult ret;
    size_t length = Array.length(args), i;
    Test.checkPointer(func);
    init_TestResult(&ret, length);
    for(i = 0; i < length; i++){
        ret.results[i].data = Array.access(args, i);
        ret.results[i].except = NULL;
        ret.results[i].success = true;
        Try{
            func(Array.access(args, i));
            ++ ret.count.success;
            ret.statistic.success += 1.0 / length;
        }Catch(TestException){
            ++ ret.count.failed;
            ret.statistic.failed += 1.0 / length;
        }Catch(GenericException){
            ++ ret.count.except;
            ret.statistic.except += 1.0 / length;
        }Finally{
            ret.results[i].except = CurrentException.get();
            ret.results[i].success = false;
        }
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
    .run = Test_run,
    .runArguments = Test_runArguments
};
