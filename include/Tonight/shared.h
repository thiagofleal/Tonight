#ifndef TONIGHT_SHARED_H
#	define	TONIGHT_SHARED_H

#	ifdef __cplusplus
		extern "C"{
#	endif

    extern const struct __Shared{
        pointer (* open)(string);
        pointer (* get)(pointer, string);
        void (* close)(pointer);
    }Shared;

#	ifdef __cplusplus
		}
#	endif

#endif
