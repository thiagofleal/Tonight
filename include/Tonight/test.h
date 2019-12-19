#ifndef TONIGHT_TEST_H
#	define	TONIGHT_TEST_H

#	ifdef __cplusplus
		extern "C"{
#	endif

    typedef struct TestResultItem {
        bool success;
        Exception except;
        pointer data;
    }TestResultItem;

    typedef struct TestResult {
        TestResultItem *results;
        struct count{
            int tests;
            int success;
            int failed;
            int except;
        }count;
        struct statistic{
            double success;
            double failed;
            double except;
        }statistic;
    }TestResult;

    extern const struct __Test {
        void (* assert)(bool);
        void (* assertMessage)(bool, string);
        int (* getError)(void);
        void (* checkError)(void);
        void (* checkErrorMessage)(string);
        void (* checkPointer)(pointer);
        void (* checkPointerMessage)(pointer, string);
        TestResult (* run)(P_void);
        TestResult (* runArguments)(P_void, pointer);
    }Test;

#	ifdef __cplusplus
		}
#	endif

#endif
