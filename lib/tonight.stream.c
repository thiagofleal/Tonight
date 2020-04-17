#include "../include/tonight.h"
#include "../include/Tonight/exceptions.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/stream.h"

INLINE IStream* getIStream(pointer obj){
    return Memory.getHeader(obj, (const pointer)&Stream);
}

INLINE void setIStream(pointer obj, IStream *str){
    Memory.addHeader(obj, (const pointer)&Stream, str);
}

static INLINE int Stream_scan(pointer obj, const string frmt, pointer args){
    return getIStream(obj)->scan(obj, frmt, args);
}

static INLINE int Stream_print(pointer obj, const string frmt, pointer args){
    return getIStream(obj)->print(obj, frmt, args);
}

const IStream Stream = {
    .scan = Stream_scan,
    .print = Stream_print
};

static INLINE int Stream_select_scan(const string frmt, pointer args){
    return Stream_scan(getCurrentObject(), frmt, args);
}

static INLINE int Stream_select_print(const string frmt, pointer args){
    return Stream_print(getCurrentObject(), frmt, args);
}

$_interface(Stream, {
    .scan = Stream_select_scan,
    .print = Stream_select_print
});
