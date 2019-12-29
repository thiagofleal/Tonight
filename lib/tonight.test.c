#include <errno.h>
#include <string.h>
#include "../include/tonight.h"
#include "../include/Tonight/exceptions.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/array.h"
#include "../include/Tonight/string.h"
#include "../include/Tonight/test.h"

static INLINE void TONIGHT Test_assertMessage(bool test, string message){
    if(!test) Throw(AssertException, message);
}

static INLINE void TONIGHT Test_assert(bool test){
    Test_assertMessage(test, "Assert test failed");
}

static INLINE void TONIGHT Test_assertNullMessage(pointer test, string message){
    if(test) Throw(AssertException, message);
}

static INLINE void TONIGHT Test_assertNull(pointer test){
    Test_assertNullMessage(test, "Null assert test failed");
}

static INLINE void TONIGHT Test_assertNotNullMessage(pointer test, string message){
    if(!test) Throw(AssertException, message);
}

static INLINE void TONIGHT Test_assertNotNull(pointer test){
    Test_assertNotNullMessage(test, "Not null assert test failed");
}

static INLINE void TONIGHT Test_assertErrorMessage(int error, string message){
    if(errno != error) Throw(AssertException, message);
}

static INLINE void TONIGHT Test_assertError(int error){
    Test_assertErrorMessage(error, "Error assert test failed");
}

static void TONIGHT Test_assertExceptionMessage(P_void func, EXCEPTION expect, string message){
    Try{
        func();
    }Catch(GenericException){
        if(!ExceptionManager.isType(CurrentException.get(), expect)) Throw(AssertException, message);
    }
}

static INLINE void TONIGHT Test_assertException(P_void func, EXCEPTION expect){
    Test_assertExceptionMessage(func, expect, "Exception assert test failed");
}

static INLINE TestResultItem* array_TestResultItem(size_t length){
    return Array.Generic(sizeof(TestResultItem), length);
}

static void init_TestResult(TestResult *res, size_t length){
    res->results = array_TestResultItem(length);
    res->count.except = 0;
    res->count.failed = 0;
    res->count.success = 0;
    res->count.tests = length;
    res->statistic.success = 0.0;
    res->statistic.failed = 0.0;
    res->statistic.except = 0.0;
}

static TestResult TONIGHT Test_run(P_void func){
    TestResult ret;
    Check.pointer(func);
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

static TestResult TONIGHT Test_runWithArguments(P_void func, pointer args){
    TestResult ret;
    size_t length = Array.length(args), i;
    Check.pointer(func);
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
    .assertNull = Test_assertNull,
    .assertNotNull = Test_assertNotNull,
    .assertError = Test_assertError,
    .assertException = Test_assertException,
    .assertMessage = Test_assertMessage,
    .assertNullMessage = Test_assertNullMessage,
    .assertNotNullMessage = Test_assertNotNullMessage,
    .assertErrorMessage = Test_assertErrorMessage,
    .assertExceptionMessage = Test_assertExceptionMessage,
    .run = Test_run,
    .runWithArguments = Test_runWithArguments
};

static INLINE void TONIGHT Check_pointerMessage(pointer check, string message){
    if(!check) Throw(NullArgumentException, message);
}

static INLINE void TONIGHT Check_pointer(pointer check){
    Check_pointerMessage(check, "Null pointer");
}

const struct __Check Check = {
    .pointer = Check_pointer,
    .pointerMessage = Check_pointerMessage
};

static INLINE int TONIGHT Error_getNumber(void){
    return errno;
}

static INLINE void TONIGHT Error_setNumber(int value){
    errno = value;
}

static INLINE void TONIGHT Error_throwExceptionMessage(string message){
    if(errno) Throw(ErrnoException, message, strerror(errno));
}

static INLINE void TONIGHT Error_throwException(void){
    Error_throwExceptionMessage("C Error-System");
}

const struct __Error Error = {
    .getNumber = Error_getNumber,
    .setNumber = Error_setNumber,
    .throwException = Error_throwException,
    .throwExceptionMessage = Error_throwExceptionMessage
};
