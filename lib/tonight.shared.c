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

static INLINE pointer TONIGHT Shared_select_get(string proc){
    return Shared_get(getCurrentObject(), proc);
}

static INLINE void TONIGHT Shared_select_close(void){
    Shared_close(getCurrentObject());
}

$_interface(Shared, {
    .get = Shared_select_get,
    .close = Shared_select_close
});
