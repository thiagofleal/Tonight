#ifndef TONIGHT_TEST_H
#	define	TONIGHT_TEST_H

#	ifdef __cplusplus
		extern "C"{
#	endif

    typedef struct test_t {
        string name;
        P_void func;
        pointer arg;
        P_fixString argToString;
    }test_t, *test_p;

    typedef struct test_result {
        bool success;
        string info;
        test_p test;
        Exception except;
    }test_result;

    extern const struct __Test {
        void (* assert)(bool);
        void (* assertMessage)(bool, string);
        int (* getError)(void);
        void (* checkError)(void);
        void (* checkErrorMessage)(string);
        void (* checkPointer)(pointer);
        void (* checkPointerMessage)(pointer, string);
        test_p (* create)(void);
        void (* free)(test_p);
        test_result* (* run)(test_p);
    }Test;

#	ifdef __cplusplus
		}
#	endif

#endif
