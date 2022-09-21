#include <stdlib.h>
#include "../include/tonight.h"
#include "../include/Tonight/application.h"

static INLINE void TONIGHT Application_exit(int value){
    exit(value);
}

static INLINE void TONIGHT Application_abort(void){
    abort();
}

static INLINE void TONIGHT Application_onExit(P_void func){
    atexit((void (*)(void))func);
}

const struct __Application Application = {
    .exit = Application_exit,
    .abort = Application_abort,
    .onExit = Application_onExit
};

const struct __ExitValue ExitValue = {
    .Success = EXIT_SUCCESS,
    .Failure = EXIT_FAILURE
};
