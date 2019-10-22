#ifndef TONIGHT_APPLICATION_H
#	define	TONIGHT_APPLICATION_H

#	ifdef __cplusplus
		extern "C"{
#	endif

    extern const struct __Application {
        void (* exit)(int);
        void (* abort)(void);
        void (* onExit)(P_void);
    }Application;

    extern const struct __ExitValue{
        int Success;
        int Failure;
    }ExitValue;

#	ifdef __cplusplus
		}
#	endif

#endif

