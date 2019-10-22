#include "../include/tonight.h"
#include "../include/Tonight/shared.h"

#ifdef WIN32
#	include <windows.h>

	static INLINE pointer TONIGHT Shared_open(string path){
		return (pointer)LoadLibrary(path);
	}

	static INLINE void TONIGHT Shared_close(pointer lib){
		if(lib)	FreeLibrary(lib);
	}

	static INLINE pointer TONIGHT Shared_get(pointer lib, string proc){
		return (pointer)GetProcAddress(lib, proc);
	}

#else
#	include <dlfcn.h>

	static INLINE pointer TONIGHT Shared_open(string path){
		return (pointer)dlopen(path, RTLD_LAZY);
	}

	static INLINE void TONIGHT Shared_close(pointer lib){
		if(lib)	dlclose(lib);
	}

	static INLINE pointer TONIGHT Shared_get(pointer lib, string proc){
		return (pointer)dlsym(lib, proc);
	}

#endif

const struct __Shared Shared = {
    .open = Shared_open,
    .get = Shared_get,
    .close = Shared_close
};
