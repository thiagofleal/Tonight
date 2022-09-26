#include <string.h>

#include "../include/tonight.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/exceptions.h"
#include "../include/Tonight/test.h"

static void testAlloc(void) {
    size_t size = 256 * 1024;
    pointer p = Memory.alloc(size);

    Test.assertMessage(Memory.size(p) == size, "memory size is equal size");
    Memory.free(p);
}

static void testRealloc(void) {
    size_t size0 = 10, size1 = 20, size2 = 1000;
    pointer p = Memory.alloc(size0);

    p = Memory.realloc(p, size1);
    Test.assertMessage(Memory.size(p) == size1, "memory reallocated size is equal size");

    p = Memory.realloc(p, size2);
    Test.assertMessage(Memory.size(p) == size2, "memory reallocated size is equal size");

    Memory.free(p);
}

static void testReallocArgumentsCallback(void) {
    size_t size = 256 * 1024;
    pointer p = Memory.realloc(NULL, size);
    Memory.free(p);
}

static void testReallocArguments(void) {
    Test.assertExceptionMessage(
        testReallocArgumentsCallback,
        NullArgumentException,
        "Memory.realloc throws exception when argument is null"
    );
}

static void testCopy(void) {
    int valueInt = 10;
    struct {
        char vChar;
        int vInt;
        double vDouble;
    } valueStruct = {
        .vChar = 'c',
        .vInt = 6000,
        .vDouble = 12.345
    };

    pointer p0, p1;

    p0 = Memory.alloc(sizeof valueInt);
    memcpy(p0, &valueInt, sizeof valueInt);

    Test.assertMessage(!memcmp(p0, &valueInt, sizeof valueInt), "int value copied from memcpy is equal value");

    p1 = Memory.copy(p0);

    Test.assertMessage(Memory.size(p0) == Memory.size(p1), "memory copied size is equal size");
    Test.assertMessage(!memcmp(p0, p1, Memory.size(p0)), "memory copied data is equal pointer data");

    p0 = Memory.realloc(p0, sizeof valueStruct);
    memcpy(p0, &valueStruct, sizeof valueStruct);

    Test.assertMessage(!memcmp(p0, &valueStruct, sizeof valueStruct), "struct value copied from memcpy is equal value");

    p1 = Memory.copy(p0);

    Test.assertMessage(Memory.size(p0) == Memory.size(p1), "memory copied size is equal size");
    Test.assertMessage(!memcmp(p0, p1, Memory.size(p0)), "memory copied data is equal pointer data");
}

static void testAddHeader(void) {
    pointer p = Memory.alloc(0);
    const pointer header = (const pointer)&p;
    pointer value = (pointer)10, ret;

    Memory.addHeader(p, header, value);
    ret = Memory.getHeader(p, header);

    Test.assertNotNullMessage(ret, "header is not null");
    Test.assertMessage(ret == value, "header value is equal value");
}

static void testRemoveHeader(void) {
    pointer p = Memory.alloc(0);
    const pointer header = (const pointer)&p;
    pointer value = (pointer)10, ret;

    Memory.addHeader(p, header, value);
    ret = Memory.getHeader(p, header);

    Test.assertNotNullMessage(ret, "header is not null before remove");

    Memory.removeHeader(p, header);
    ret = Memory.getHeader(p, header);
    Test.assertNullMessage(ret, "header is null after remove");
}

void testMemory(void) {
    Test.run("Allocation with Memory.alloc", testAlloc);
    Test.run("Reallocation with Memory.realloc", testRealloc);
    Test.run("Invalid argument to Memory.realloc", testReallocArguments);
    Test.run("Clone data with Memory.copy", testCopy);
    Test.run("Using headers with Memory.addHeader", testAddHeader);
    Test.run("Removing headers with Memory.removeHeader", testRemoveHeader);
}