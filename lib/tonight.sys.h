#include "tonight.proto.h"

#ifdef WIN32
#	include <windows.h>
#	include <conio.h>
	
	static bool TONIGHT pressKey(void){
		return kbhit() ? true : false;
	}
	
	static int TONIGHT getKey(void){
		DWORD mode;
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
	}
	
	INLINE void TONIGHT __sleep(unsigned int miliseconds){
		Sleep(miliseconds);
	}
	
	INLINE void TONIGHT cursor_position(int x, int y){
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){x, y});
	}
	
	INLINE void TONIGHT __clearScreen(void){
		system("cls");
	}
	
	static INLINE void TONIGHT __Colors_textbackground(register int _tcolor, register int _bcolor){
		WORD w = (0x0F & (text_color = _tcolor)) + ((0x0F & (background_color = _bcolor)) << 4);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), w);
	}
	
#else
#	include <termios.h>
#	include <unistd.h>
#	include <fcntl.h>
#	include <sys/select.h>
#	include <sys/ioctl.h>
#	include <stropts.h>
	
	/**
	*	@Atention!
	*	
	*	Function: pressKey
	*	This function needs be changed
	*/
	static bool TONIGHT pressKey(void){
		static int bytesWaiting;
		static struct termios old_term, new_term;
		tcgetattr(stdin->_fileno, &old_term);
		new_term = old_term;
		new_term.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(stdin->_fileno, TCSANOW, &new_term);
		ioctl(stdin->_fileno, FIONREAD, &bytesWaiting);
		tcsetattr(stdin->_fileno, TCSANOW, &old_term);
		return bytesWaiting ? true : false;
	}
	
	static int TONIGHT getKey(void){
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
	}
	
	INLINE void TONIGHT __sleep(unsigned int miliseconds){
		usleep(miliseconds * 1000);
	}
	
	INLINE void TONIGHT cursor_position(int x, int y){
		printf("\033[%d;%dH", y, x);
	}
	
	static void TONIGHT __clearScreen(void){
		printf("\e[2J\e[H");
	}
	
	INLINE void TONIGHT __Colors_textbackground(int _tcolor, int _bcolor){
		printf("\033[%im\033[%im", _bcolor + 39, _tcolor + 29);
	}

#endif
