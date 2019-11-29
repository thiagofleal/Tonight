#include <errno.h>
#include <string.h>
#include "../include/tonight.h"
#include "../include/Tonight/exceptions.h"
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
    if(errno) Throw(ErrnoException, strerror(errno));
}

static INLINE void TONIGHT Test_checkPointer(pointer test){
    if(!test) Throw(NullArgumentException, "Null argument");
}

const struct __Test Test = {
    .assert = Test_assert,
    .assertMessage = Test_assertMessage,
    .getError = Test_getError,
    .checkError = Test_checkError,
    .checkPointer = Test_checkPointer
};
