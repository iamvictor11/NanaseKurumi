#include <stdio.h>
#include "nanaku/platform/console.h"
#include "nanaku/nk.h"
#include "nanaku/container/str.h"

nkAllocator allocator = NK_DEFAULT_ALLOCATOR;

NK_DEC_STRING(test, String)
NK_DEF_STRING(test, String)
NK_IMPL_STRING(test, String, &allocator)

int main()
{
    nkSetConsoleOutputCP_UTF8();
    testString str = testStringCreateFromFormat("%s", "-011");
    printf("%s, hash: %zu, int: %d\n", testStringToCstr(str), testStringHash(str), testStringToInt(str));
    testStringAssignFromCstr(str, "0xF'F");
    printf("%s, hash: %zu, int: %d\n", testStringToCstr(str), testStringHash(str), testStringToInt(str));
    testStringAssignFromCstr(str, "01.2e-3");
    printf("%s, hash: %zu, float: %f\n", testStringToCstr(str), testStringHash(str), testStringToFloat(str));
    NK_STRING_FOREACH(char, str, c)
        printf("%c", *c);
    testStringDestroy(str);
    nkGetChar();
    return EXIT_SUCCESS;
}
