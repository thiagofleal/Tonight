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
        bool test = ExceptionManager.isType(CurrentException.get(), expect);
        Test_assertMessage(test, message);
    }Finally{
        return;
    }
    Throw(AssertException, message);
}

static INLINE void TONIGHT Test_assertException(P_void func, EXCEPTION expect){
    Test_assertExceptionMessage(func, expect, "Exception assert test failed");
}

static INLINE TestResultItem* array_TestResultItem(size_t length){
    return Array.Generic(sizeof(TestResultItem), length);
}

static TestResult res;

struct list_tests {
    TestResultItem test;
    struct list_tests *next;
}*list = NULL, **end_list = &list;

static void list_push(TestResultItem value){
    *end_list = Memory.alloc(sizeof(struct list_tests));
    (*end_list)->test = value;
    (*end_list)->next = NULL;
    end_list = &(*end_list)->next;
}

static TestResultItem list_shift(void){
    TestResultItem item = list->test;
    struct list_tests *node = list;
    list = list->next;
    Memory.free(node);
    return item;
}

static void Test_start(void){
    res.results = NULL;
    res.count.except = 0;
    res.count.failed = 0;
    res.count.success = 0;
    res.count.tests = 0;
    res.statistic.success = 0.0;
    res.statistic.failed = 0.0;
    res.statistic.except = 0.0;
}

static void TONIGHT Test_runWith(P_void func, pointer data){
    bool success = false;
    pointer except = NULL;
    Try{
        ++ res.count.tests;
        func(data);
        ++ res.count.success;
        success = true;
    }Catch(TestException){
        ++ res.count.failed;
    }Catch(GenericException){
        ++ res.count.except;
    }Finally{
        except = CurrentException.copy();
    }
    list_push((TestResultItem){
        (TestData){
            .function = func,
            .argument = data
        },
        .success = success,
        .except = except
    });
}

static INLINE void TONIGHT Test_run(P_void func){
    return Test_runWith(func, NULL);
}

static void TONIGHT Test_runWithCollection(P_void func, pointer args){
    pointer arg;
    foreach(arg $in args){
        Test_runWith(func, arg);
    }
}

static TestResult TONIGHT Test_finalize(void){
    int i;
    if (res.count.tests){
        res.statistic.success = (double) res.count.success / res.count.tests;
        res.statistic.failed = (double) res.count.failed / res.count.tests;
        res.statistic.except = (double) res.count.except / res.count.tests;
    }else res.statistic.success = res.statistic.failed = res.statistic.except = 0;
    res.results = array_TestResultItem(res.count.tests);
    foreachkey(i $in res.results){
        res.results[i] = list_shift();
    }
    return res;
}

static INLINE TestResult TONIGHT Test_getResult(void){
    return res;
}

static void TONIGHT Test_freeResult(void){
    TestResultItem item;
    foreach(item $in res.results){
        ExceptionManager.free(item.except);
    }
    Array.free(res.results);
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
    .start = Test_start,
    .run = Test_run,
    .runWith = Test_runWith,
    .runWithCollection = Test_runWithCollection,
    .finalize = Test_finalize,
    .getResult = Test_getResult,
    .freeResult = Test_freeResult
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
