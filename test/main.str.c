#include <stdio.h>
#include "project_name/platform/console.h"
#include "project_name/version.h"
#include "project_name/container/str.h"

PnxAllocator allocator = PNX_DEFAULT_ALLOCATOR;

PNX_DEC_STRING(test, Test, String)
PNX_DEF_STRING(test, Test, String)
PNX_IMPL_STRING(test, Test, String, &allocator)

int main()
{
    pnxSetConsoleOutputCP_UTF8();

    PnxVersion version = PNX_VERSION;
    printf("%s\n", version.name);
    TestString str = testStringCreateFromFormat("0%d", PNX_VERSION_CAST_UINT(version));
    printf("%s, hash: %zu, int: %d\n", testStringToCstr(str), testStringHash(str), testStringToInt(str));
    testStringAssignFromCstr(str, "-0xF'F");
    printf("%s, hash: %zu, int: %d\n", testStringToCstr(str), testStringHash(str), testStringToInt(str));
    testStringAssignFromCstr(str, "01.2e-3");
    printf("%s, hash: %zu, float: %f\n", testStringToCstr(str), testStringHash(str), testStringToFloat(str));
    PNX_STRING_FOREACH(str, c)
        printf("%c", *c);
    testStringDestroy(str);

    pnxGetChar();
    return EXIT_SUCCESS;
}
