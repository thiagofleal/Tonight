#ifdef WIN32
#	include <windows.h>
#	include <conio.h>

	static INLINE pointer TONIGHT __Shared_open(string path){
		return (pointer)LoadLibrary(path);
	}

	static INLINE void TONIGHT __Shared_close(pointer lib){
		if(lib)	FreeLibrary(lib);
	}

	static INLINE pointer TONIGHT __Shared_get(pointer lib, string proc){
		return (pointer)GetProcAddress(lib, proc);
	}

#else
#	include <termios.h>
#	include <unistd.h>
#	include <fcntl.h>
#	include <dlfcn.h>
#	include <sys/select.h>
#	include <sys/ioctl.h>
#	include <stropts.h>

	static INLINE pointer TONIGHT __Shared_open(string path){
		return (pointer)dlopen(path, RTLD_LAZY);
	}

	static INLINE void TONIGHT __Shared_close(pointer lib){
		if(lib)	dlclose(lib);
	}

	static INLINE pointer TONIGHT __Shared_get(pointer lib, string proc){
		return (pointer)dlsym(lib, proc);
	}

#endif
