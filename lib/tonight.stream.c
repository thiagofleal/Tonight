#include "../include/tonight.h"
#include "../include/Tonight/exceptions.h"
#include "../include/Tonight/stream.h"

INLINE IStream* getIStream(pointer obj){
    return obj - sizeof(IStream*);
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
