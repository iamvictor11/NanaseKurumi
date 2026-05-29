#include <stdio.h>
#include "project_name/platform/console.h"
#include "project_name/version.h"
#include "project_name/container/str.h"

pnxAllocator allocator = PNX_DEFAULT_ALLOCATOR;

PNX_DEC_STRING(test, String)
PNX_DEF_STRING(test, String)
PNX_IMPL_STRING(test, String, &allocator)

int main()
{
    pnxSetConsoleOutputCP_UTF8();

    pnxVersion version = PNX_VERSION;
    printf("%s\n", version.name);
    testString str = testStringCreateFromFormat("0%d", PNX_VERSION_CAST_UINT(version));
    printf("%s, hash: %zu, int: %d\n", testStringToCstr(str), testStringHash(str), testStringToInt(str));
    testStringAssignFromCstr(str, "-0xF'F");
    printf("%s, hash: %zu, int: %d\n", testStringToCstr(str), testStringHash(str), testStringToInt(str));
    testStringAssignFromCstr(str, "01.2e-3");
    printf("%s, hash: %zu, float: %f\n", testStringToCstr(str), testStringHash(str), testStringToFloat(str));
    PNX_STRING_FOREACH(char, str, c)
        printf("%c", *c);
    testStringDestroy(str);

    pnxGetChar();
    return EXIT_SUCCESS;
}
