#ifndef TONIGHT_CONSOLE_H
#	define	TONIGHT_CONSOLE_H

#   include "stream.h"

#	ifdef _WIN32
#		define key_right	295
#		define key_left		293
#		define key_up		294
#		define key_down		296
#		define key_ESC		27
#		define key_ENTER	13
#		define key_SPACE	32
#		define key_BS		8
#	else
#		define key_right	185
#		define key_left		186
#		define key_up		183
#		define key_down		184
#		define key_ESC		27
#		define key_ENTER	10
#		define key_SPACE	32
#		define key_BS		127
#	endif

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
        pointer (* getWideStream)(void);
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

    extern const struct __ConsoleKey{
		int Right;
		int Left;
		int Up;
		int Down;
		int Escape;
		int Enter;
		int Space;
		int BackSpace;
	}ConsoleKey;

#	ifdef __cplusplus
		}
#	endif

#endif
