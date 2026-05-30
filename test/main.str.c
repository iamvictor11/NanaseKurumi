#include <stdio.h>
#include "project_name/platform/console.h"
#include "project_name/version.h"
#include "project_name/container/str.h"

PNX_DEF_VERSION(static inline, test, Test)

PNX_DEC_ALLOCATOR(static inline, test, Test)
PNX_DEF_ALLOCATOR(static inline, test, Test)
PNX_IMPL_ALLOCATOR(static inline, test, Test)

TestAllocator allocator;

PNX_DEC_STRING(static inline, test, Test, String)
PNX_DEF_STRING(static inline, test, Test, String)
PNX_IMPL_STRING(static inline, test, Test, String, &allocator)

int main()
{
    pnxSetConsoleOutputCP_UTF8();

    allocator = testDefaultAllocator();

    TestVersion version = PNX_VERSION;
    printf("%s\n", version.name);
    TestString str = testStringCreateFromFormat("0%d", PNX_VERSION_CAST_UINT(version));
    printf("%s, hash: %zu, int: %d\n", testStringToCstr(str), testStringHash(str), testStringToInt(str));
    testStringAssignFromCstr(str, "-0xF'F");
    printf("%s, hash: %zu, int: %d\n", testStringToCstr(str), testStringHash(str), testStringToInt(str));
    testStringAssignFromCstr(str, "01.2e-3");
    printf("%s, hash: %zu, float: %f\n", testStringToCstr(str), testStringHash(str), testStringToFloat(str));
    PNX_STRING_FOREACH(str, c)
        printf("%c", *c);
    printf("\n");
    testStringDestroy(str);

    pnxGetChar();
    return EXIT_SUCCESS;
}
