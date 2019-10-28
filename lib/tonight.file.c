#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "../include/tonight.h"
#include "../include/Tonight/exceptions.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/string.h"
#include "../include/Tonight/wstring.h"
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

static INLINE int file_stream_scan(pointer f, const string frmt, pointer args){
    return vfscanf(((file)f)->data, frmt, args);
}

static INLINE int file_stream_print(pointer f, const string frmt, pointer args){
    return vfprintf(((file)f)->data, frmt, args);
}
/*
static INLINE int file_stream_wscan(pointer f, const string frmt, pointer args){
    fixWideString _frmt = FixWideString.formated(L"%hs", frmt);
    return vfwscanf(((file)f)->data, (const wstring)getText(_frmt), args);
}

static INLINE int file_stream_wprint(pointer f, const string frmt, pointer args){
    fixWideString _frmt = FixWideString.formated(L"%hs", frmt);
    return vfwprintf(((file)f)->data, (const wstring)getText(_frmt), args);
}
*/
static IStream file_stream = {
    .scan = file_stream_scan,
    .print = file_stream_print
};
/*
static IStream file_wstream = {
    .scan = file_stream_wscan,
    .print = file_stream_wprint
};
*/
static file TONIGHT $throws __new_File(string fName, FileModeDescriptor fMode){
	struct __file_data__ *fd = Memory.alloc(sizeof(struct __file_data__) + sizeof(file));
	file f = (file)fd->data;
	fd->_stream = &file_stream;
	f->data = fopen(fName, fMode->value);
	if(!f->data)
		throw(FileOpenException, String.concat("Impossible to open the file \"", fName, "\"", $end));
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

static file create_file_from(pointer _fd, pointer from){
    struct __file_data__ *fd = _fd;
	file f = (file)fd->data;
	fd->_stream = &file_stream;
	f->data = from;
	return f;
}

static INLINE file TONIGHT File_stdInput(void){
    static byte data[sizeof(struct __file_data__) + sizeof(file)];
	return create_file_from(&data[0], stdin);
}

static INLINE file TONIGHT File_stdOutput(void){
    static byte data[sizeof(struct __file_data__) + sizeof(file)];
	return create_file_from(&data[0], stdout);
}

static INLINE file TONIGHT File_stdError(void){
    static byte data[sizeof(struct __file_data__) + sizeof(file)];
	return create_file_from(&data[0], stderr);
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
