#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef WIN32
#   define IStream __temp_IStream__
#	include <windows.h>
#	include <conio.h>
#   undef IStream
#else
#	include <termios.h>
#	include <unistd.h>
#	include <fcntl.h>
#	include <dlfcn.h>
#	include <sys/select.h>
#	include <sys/ioctl.h>
#	include <stropts.h>
#endif

#include "../include/tonight.h"
#include "../include/Tonight/exceptions.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/console.h"

struct ColorDescriptor{
    int code;
};

static IStream console_stream = {
    .scan = (pointer)vscanf,
    .print = (pointer)vprintf
};

static pointer Console_getStream(void){
    static struct ret{
        IStream *stream;
        pointer null;
    } ret = {
        .stream = &console_stream,
        .null = NULL
    };
    return &ret.null;
}

static INLINE void Console_clearScreen(void){
#ifdef _WIN32
    system("cls");
#else
    printf("\e[2J\e[H");
#endif
}

static bool Console_pressedKey(void){
#ifdef WIN32
    return kbhit() ? true : false;
#else
    static int bytesWaiting;
    static struct termios old_term, new_term;
    tcgetattr(stdin->_fileno, &old_term);
    new_term = old_term;
    new_term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(stdin->_fileno, TCSANOW, &new_term);
    ioctl(stdin->_fileno, FIONREAD, &bytesWaiting);
    tcsetattr(stdin->_fileno, TCSANOW, &old_term);
    return bytesWaiting ? true : false;
#endif
}

static int Console_getKey(void){
#if _WIN32
    INPUT_RECORD inrec = {};
    DWORD count;
    int result;
    HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
    if(hstdin == INVALID_HANDLE_VALUE)
        return 0;
    do
        ReadConsoleInput(hstdin, &inrec, 1, &count);
    while(inrec.EventType != KEY_EVENT || !inrec.Event.KeyEvent.bKeyDown);
    if(inrec.Event.KeyEvent.uChar.AsciiChar)
        result = inrec.Event.KeyEvent.uChar.AsciiChar;
    else
        result = 256 + inrec.Event.KeyEvent.wVirtualKeyCode;
    return result;
#else
    struct termios oldattr, newattr;
    tcgetattr(stdin->_fileno, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    newattr.c_cc[VTIME] = 0;
    newattr.c_cc[VMIN] = 1;
    tcsetattr(stdin->_fileno, TCSANOW, &newattr);
    newattr.c_cc[VMIN] = 0;
    i = 0;
    while(true){
        c = getchar();
        if(!c || c == EOF) break;
        if(!i) tcsetattr(stdin->_fileno, TCSANOW, &newattr);
        i += c;
    }
    tcsetattr(stdin->_fileno, TCSANOW, &oldattr);
    return i;
#endif
}

static int Console_getKeyEcho(void){
    register int c = Console_getKey();
	putchar(c);
	return c;
}

static INLINE void Console_cursorPosition(int x, int y){
#ifdef _WIN32
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){x, y});
#else
    printf("\033[%d;%dH", y, x);
#endif
}

#ifdef _WIN32
static bool init = false;
static WORD wIni;

static CONSOLE_SCREEN_BUFFER_INFO bufferInfo(void){
    CONSOLE_SCREEN_BUFFER_INFO bufinfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufinfo);
    return bufinfo;
}

static INLINE WORD getTextAttributes(void){
    return bufferInfo().wAttributes;
}

#endif // _WIN32

static void Console_setColor_both(ColorDescriptor txt, ColorDescriptor bg){
    int _tcolor = txt ? txt->code : -29;
    int _bcolor = bg ? bg->code : -39;
#ifdef _WIN32
    static WORD w;
    if(!init){
        wIni = w = getTextAttributes();
        init = true;
    }
    if(txt) w &= (0x0F & _tcolor);
    if(bg)  w &= ((0x0F & _bcolor) << 4);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), w);
#else
    printf("\033[%im\033[%im", _bcolor + 39, _tcolor + 29);
#endif
}

static void Console_setColor_text(ColorDescriptor txt){
    Console_setColor_both(txt, NULL);
}

static void Console_setColor_background(ColorDescriptor bg){
    Console_setColor_both(NULL, bg);
}

static void Console_setColor_reset(void){
#ifdef _WIN32
    if(init) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wIni);
#else
    printf("\033[0m");
#endif
}

static void Console_sleep(unsigned miliseconds){
#ifdef _WIN32
    Sleep(miliseconds);
#else
    usleep(miliseconds * 1000);
#endif
}

const struct __Console Console = {
    .setColor = {
        .text = Console_setColor_text,
        .background = Console_setColor_background,
        .both = Console_setColor_both,
        .reset = Console_setColor_reset
    },
    .getStream = Console_getStream,
    .clearScreen = Console_clearScreen,
    .pressedKey = Console_pressedKey,
    .getKey = Console_getKey,
    .getKeyEcho = Console_getKeyEcho,
    .cursorPosition = Console_cursorPosition,
    .sleep = Console_sleep
};

static struct ColorDescriptor
    ConsoleColor_black = {0},
    ConsoleColor_darkBlue = {1},
    ConsoleColor_darkGreen = {2},
    ConsoleColor_darkCyan = {3},
    ConsoleColor_darkRed = {4},
    ConsoleColor_darkMagenta = {5},
    ConsoleColor_darkYellow = {6},
    ConsoleColor_darkGray = {7},
    ConsoleColor_gray = {8},
    ConsoleColor_blue = {9},
    ConsoleColor_green = {10},
    ConsoleColor_cyan = {11},
    ConsoleColor_red = {12},
    ConsoleColor_magenta = {13},
    ConsoleColor_yellow = {14},
    ConsoleColor_white = {15};

const struct __ConsoleColor ConsoleColor = {
    .black = &ConsoleColor_black,
    .darkBlue = &ConsoleColor_darkBlue,
    .darkGreen = &ConsoleColor_darkGreen,
    .darkCyan = &ConsoleColor_darkCyan,
    .darkRed = &ConsoleColor_darkRed,
    .darkMagenta = &ConsoleColor_darkMagenta,
    .darkYellow = &ConsoleColor_darkYellow,
    .darkGray = &ConsoleColor_darkGray,
    .gray = &ConsoleColor_gray,
    .blue = &ConsoleColor_blue,
    .green = &ConsoleColor_green,
    .cyan = &ConsoleColor_cyan,
    .red = &ConsoleColor_red,
    .magenta = &ConsoleColor_magenta,
    .yellow = &ConsoleColor_yellow,
    .white = &ConsoleColor_white
};
