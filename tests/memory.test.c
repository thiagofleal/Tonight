#include <string.h>

#include "../include/tonight.h"
#include "../include/Tonight/memory.h"
#include "../include/Tonight/exceptions.h"
#include "../include/Tonight/test.h"

static void testAlloc(void) {
    size_t size = 256 * 1024;
    pointer p = Memory.alloc(size);

    Test.assertMessage(Memory.size(p) == size, "[Memory.alloc] Memory alloc size error");
    Memory.free(p);
}

static void testRealloc(void) {
    size_t size0 = 10, size1 = 20, size2 = 1000;
    pointer p = Memory.alloc(size0);

    p = Memory.realloc(p, size1);
    Test.assertMessage(Memory.size(p) == size1, "[Memory.realloc] Memory realloc size error");

    p = Memory.realloc(p, size2);
    Test.assertMessage(Memory.size(p) == size2, "[Memory.realloc] Memory realloc size error");

    Memory.free(p);
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

    Test.assertMessage(!memcmp(p0, &valueInt, sizeof valueInt), "[memcpy] memcpy failed");

    p1 = Memory.copy(p0);

    Test.assertMessage(Memory.size(p0) == Memory.size(p1), "[Memory.copy] Size failed");
    Test.assertMessage(!memcmp(p0, p1, Memory.size(p0)), "[Memory.copy] Copy failed");

    p0 = Memory.realloc(p0, sizeof valueStruct);
    memcpy(p0, &valueStruct, sizeof valueStruct);

    Test.assertMessage(!memcmp(p0, &valueStruct, sizeof valueStruct), "[memcpy] memcpy failed");

    p1 = Memory.copy(p0);

    Test.assertMessage(Memory.size(p0) == Memory.size(p1), "[Memory.copy] Size failed");
    Test.assertMessage(!memcmp(p0, p1, Memory.size(p0)), "[Memory.copy] Copy failed");
}

static void testAddHeader(void) {
    throw(NotImplementException, "Test not implemented");
}

static void testRemoveHeader(void) {
    throw(NotImplementException, "Test not implemented");
}

static void testGetHeader(void) {
    throw(NotImplementException, "Test not implemented");
}

void testMemory(void) {
    Test.run(testAlloc);
    Test.run(testRealloc);
    Test.run(testCopy);
    Test.run(testAddHeader);
    Test.run(testRemoveHeader);
    Test.run(testGetHeader);
}