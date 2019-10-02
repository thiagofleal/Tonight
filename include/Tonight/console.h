#ifndef TONIGHT_CONSOLE_H
#	define	TONIGHT_CONSOLE_H

#   include "stream.h"

#	ifdef __cplusplus
		extern "C"{
#	endif

    typedef struct ColorDescriptor *ColorDescriptor;

    extern const struct __Console{
        struct setColor{
            void (* text)(ColorDescriptor);
            void (* background)(ColorDescriptor);
            void (* both)(ColorDescriptor, ColorDescriptor);
            void (* reset)(void);
        }setColor;
        pointer (* getStream)(void);
        void (* clearScreen)(void);
        bool (* pressedKey)(void);
        int (* getKey)(void);
        int (* getKeyEcho)(void);
        void (* cursorPosition)(int, int);
        void (* sleep)(unsigned);
    }Console;

    extern const struct __ConsoleColor{
        ColorDescriptor black, darkBlue, darkGreen, darkCyan, darkRed, darkMagenta, darkYellow, darkGray;
        ColorDescriptor gray, blue, green, cyan, red, magenta, yellow, white;
    }ConsoleColor;

#	ifdef __cplusplus
		}
#	endif

#endif
