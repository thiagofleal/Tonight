#include <stdarg.h>
#include "../include/tonight.h"
#include "../include/Tonight/exceptions.h"
#include "../include/Tonight/string.h"
#include "../include/Tonight/reader.h"

static int stream_scan(pointer stream, const string frmt, ...){
    register int ret;
    va_list v;
    va_start(v, frmt);
    ret = Stream.scan(stream, frmt, v);
    va_end(v);
    return ret;
}

static int Reader_nextChar(void){
    int ret;
    pointer stream = $$(this $as Reader).stream;
    if(stream_scan(stream, "%c", &ret) != 1) throw(InputException, "Impossible to read a character");
    return ret;
}

static int Reader_nextInt(void){
    int ret;
    pointer stream = $$(this $as Reader).stream;
    if(stream_scan(stream, "%i", &ret) != 1) throw(InputException, "Impossible to read an integer");
    return ret;
}

static float Reader_nextFloat(void){
    float ret;
    pointer stream = $$(this $as Reader).stream;
    if(stream_scan(stream, "%f", &ret) != 1) throw(InputException, "Impossible to read a floating pointer");
    return ret;
}

static double Reader_nextDouble(void){
    double ret;
    pointer stream = $$(this $as Reader).stream;
    if(stream_scan(stream, "%lf", &ret) != 1) throw(InputException, "Impossible to read a double floating pointer");
    return ret;
}

static pointer Reader_next(void){
    fixString ret;
    fixString frmt = FixString.formated("%%%us", sizeof ret - 1);
    pointer stream = $$(this $as Reader).stream;
    if(stream_scan(stream, (const string)getText(frmt), &ret) != 1) throw(InputException, "Impossible to read a string");
    return toString(getText(ret));
}

static pointer Reader_nextLine(void){
    longFixString ret;
    fixString frmt = FixString.formated(" %%%u[^\n]s", sizeof ret - 1);
    pointer stream = $$(this $as Reader).stream;
    if(stream_scan(stream, (const string)getText(frmt), &ret) != 1) throw(InputException, "Impossible to read a string");
    return toString(getText(ret));
}

static IReader Reader_vtble = {
    .nextChar = Reader_nextChar,
    .nextInt = Reader_nextInt,
    .nextFloat = Reader_nextFloat,
    .nextDouble = Reader_nextDouble,
    .next = Reader_next,
    .nextLine = Reader_nextLine
};

static void Reader_constructor(pointer args){
    $va_set(args, {
        pointer stream;
    });
    construct(superOf(Reader));
    $$(this $as Reader).stream = $va_get.stream;
    setInterface(Reader, Reader_vtble);
}

static void Reader_destructor(void){
    destruct(superOf(Reader));
}

static int IReader_nextChar(void){
    int ret = $Empty(int);
    Method(Reader){
        ret = getInterface(Reader).nextChar();
    }
    return ret;
}

static int IReader_nextInt(void){
    int ret = $Empty(int);
    Method(Reader){
        ret = getInterface(Reader).nextInt();
    }
    return ret;
}

static float IReader_nextFloat(void){
    float ret = $Empty(float);
    Method(Reader){
        ret = getInterface(Reader).nextFloat();
    }
    return ret;
}

static double IReader_nextDouble(void){
    double ret = $Empty(double);
    Method(Reader){
        ret = getInterface(Reader).nextDouble();
    }
    return ret;
}

static pointer IReader_next(void){
    pointer ret = NULL;
    Method(Reader){
        ret = getInterface(Reader).next();
    }
    return ret;
}

static pointer IReader_nextLine(void){
    pointer ret = NULL;
    Method(Reader){
        ret = getInterface(Reader).nextLine();
    }
    return ret;
}

static IReader Reader_interface = {
    .nextChar = IReader_nextChar,
    .nextInt = IReader_nextInt,
    .nextFloat = IReader_nextFloat,
    .nextDouble = IReader_nextDouble,
    .next = IReader_next,
    .nextLine = IReader_nextLine
};

Constructor(Reader, Reader_constructor);
Destructor(Reader, Reader_destructor);

Define_Class(Reader $extends Object $implements IReader $with Reader_interface);
