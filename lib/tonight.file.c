#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "../include/tonight.h"
#include "../include/Tonight/exceptions.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/file.h"

struct FileModeDescriptor{
    string value;
};

struct __file__{
    FILE* data;
};

struct __file_data__{
    IStream* _stream;
    byte data[0];
};

static IStream file_stream = {
    .scan = (pointer)vfscanf,
    .print = (pointer)vfprintf
};

static file TONIGHT $throws __new_File(string fName, FileModeDescriptor fMode){
	struct __file_data__ *fd = Memory.alloc(sizeof(struct __file_data__) + sizeof(file));
	file f = (file)fd->data;
	fd->_stream = &file_stream;
	f->data = fopen(fName, fMode->value);
	if(!f->data)
		throw(FileOpenException, concat("Impossible to open the file \"", fName, "\"", $end));
	return f;
}

static INLINE void TONIGHT File_close(file f){
	if(f) fclose(*(FILE**)f);
	Memory.free(f - sizeof(struct __file_data__));
}

static INLINE bool TONIGHT File_end(file f){
	if(f) return feof(*(FILE**)f) ? true : false;
	return false;
}

static INLINE void TONIGHT File_rewind(file f){
	if(f) rewind(*(FILE**)f);
}

static INLINE file TONIGHT File_stdInput(void){
	return (file){stdin};
}

static INLINE file TONIGHT File_stdOutput(void){
	return (file){stdout};
}

static INLINE file TONIGHT File_stdError(void){
	return (file){stderr};
}

struct FileModeDescriptor File_Mode_read = {"r"};
struct FileModeDescriptor File_Mode_write = {"w"};
struct FileModeDescriptor File_Mode_append = {"a"};

/* File */
const struct __File File = {
	.open = __new_File,
	.close = File_close,
	.end = File_end,
	.rewind = File_rewind,
	.stdInput = File_stdInput,
	.stdOutput = File_stdOutput,
	.stdError = File_stdError
};

const struct __FileMode FileMode = {
    .read = &File_Mode_read,
    .write = &File_Mode_write,
    .append = &File_Mode_append
};
