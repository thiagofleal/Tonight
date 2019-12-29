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
        void (* assertNull)(pointer);
        void (* assertNotNull)(pointer);
        void (* assertError)(int);
        void (* assertException)(P_void, EXCEPTION);
        void (* assertMessage)(bool, string);
        void (* assertNullMessage)(pointer, string);
        void (* assertNotNullMessage)(pointer, string);
        void (* assertErrorMessage)(int, string);
        void (* assertExceptionMessage)(P_void, EXCEPTION, string);
        TestResult (* run)(P_void);
        TestResult (* runWithArguments)(P_void, pointer);
    }Test;

    extern const struct __Check {
        void (* pointer)(pointer);
        void (* pointerMessage)(pointer, string);
    }Check;

    extern const struct __Error {
        int (* getNumber)(void);
        void (* setNumber)(int);
        void (* throwException)(void);
        void (* throwExceptionMessage)(string);
    }Error;

#	ifdef __cplusplus
		}
#	endif

#endif
