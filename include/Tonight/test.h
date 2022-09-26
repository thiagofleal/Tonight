#ifndef TONIGHT_TEST_H
#	define	TONIGHT_TEST_H

#	ifdef __cplusplus
		extern "C"{
#	endif

    typedef struct TestEchoValue *TestEchoValue;

    extern const struct __TestConfig {
        TestEchoValue DEBUG;
        TestEchoValue RESULTS;
        TestEchoValue FAILED_AND_EXCEPTIONS;
        TestEchoValue FAILED;
        TestEchoValue NOTHING;
    }TestEcho;

    typedef struct TestData {
        P_void function;
        pointer argument;
    }TestData;

    typedef struct TestResultItem {
        TestData data;
        bool success;
        Exception except;
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
        void (* start)(TestEchoValue);
        void (* run)(string, P_void);
        void (* runWith)(string, P_void, pointer);
        void (* runWithCollection)(string, P_void, pointer);
        TestResult (* finalize)(void);
        TestResult (* getResult)(void);
        void (* freeResult)(void);
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
