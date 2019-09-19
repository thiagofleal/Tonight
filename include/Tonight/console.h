#ifndef TONIGHT_CONSOLE_H
#	define	TONIGHT_CONSOLE_H

#	ifdef __cplusplus
		extern "C"{
#	endif

    extern const struct __Console{
        Painter setColor;
        stream (* getInputStream)(void);
        stream (* getOutputStream)(void);
        void (* clearScreen)(void);
        string (* readPassword)(unsigned);
        wstring (* readPasswordWide)(unsigned);
    }Console;

#	ifdef __cplusplus
		}
#	endif

#endif
