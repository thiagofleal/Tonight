#include <stdlib.h>
#include "../include/tonight.h"
#include "../include/Tonight/exceptions.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/array.h"
#include "../include/Tonight/string.h"

#undef main

static string ARRAY __args = NULL;

void freeArg(pointer pArg) {
    string arg = *(string*)pArg;
    String.free(arg);
}

static void onExit(void){
	if(__args){
        Array.forEach(__args, freeArg);
		Array.free(__args);
		__args = NULL;
	}
}

#pragma weak __main__
extern int __main__();
#pragma weak Main
extern int Main(string*);
#pragma weak Setup
extern void Setup(string*);
#pragma weak Loop
extern bool Loop(void);

static void TONIGHT __Base_TonightMode(register int argc, string argv[]){
	register int i;
	static int f;
	__args = Array.String(argc);
	if(f++)
		throw(ApplicationException, "Application previously initialized");
	for(i = 0; i < argc; i++)
		__args[i] = toString(argv[i]);
	atexit(onExit);
}

static int TONIGHT TonightModeDefault(register int argc, string argv[]){
	P_int func = Main;
	__Base_TonightMode(argc, argv);
	try
		return func(__args);
	catch(GenericException)
        return EXIT_FAILURE;
}

static int TONIGHT TonightModeLoop(register int argc, string argv[]){
	P_void func = Setup;
	P_bool loop = Loop;
	__Base_TonightMode(argc, argv);
	try
		if(func && loop){
			func(__args);
			while(loop());
			return EXIT_SUCCESS;
		}
		else
			return EXIT_FAILURE;
	catch(GenericException);
    return EXIT_FAILURE;
}

int main(int argc, string argv[]){
	if((pointer)__main__)
		return __main__(argc, argv);
	if((pointer)Main)
		return TonightModeDefault(argc, argv);
	if((pointer)Setup)
		return TonightModeLoop(argc, argv);
}
