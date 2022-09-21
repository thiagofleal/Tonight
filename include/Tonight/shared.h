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

    $_add(Shared, {
        pointer (* get)(string);
        void (* close)(void);
    });

#	ifdef __cplusplus
		}
#	endif

#endif
