#ifndef TONIGHT_TEST_H
#	define	TONIGHT_TEST_H

#	ifdef __cplusplus
		extern "C"{
#	endif

    extern const struct __Test {
        void (* assert)(bool);
        int (* getError)(void);
        void (* checkError)(void);
        void (* checkPointer)(pointer);
    }Test;

#	ifdef __cplusplus
		}
#	endif

#endif
