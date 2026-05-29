#include <stdio.h>
#include "nanaku/nk.h"
#include "nanaku/container/str.h"

nkAllocator allocator = NK_DEFAULT_ALLOCATOR;

NK_DEC_STRING(test, String)
NK_DEF_STRING(test, String)
NK_IMPL_STRING(test, String, &allocator)

int main()
{
    int key;
    scanf("%d", &key);
    testString str = testStringCreateFromFormat("%d", key);
    printf("%s, hash: %zu, float: %f\n", testStringToCstr(str), testStringHash(str), testStringToFloat(str));
    testStringAssignFromCstr(str, "11e3");
    printf("%s, hash: %zu, float: %f\n", testStringToCstr(str), testStringHash(str), testStringToFloat(str));
    testStringDestroy(str);
    scanf("%d", &key);
    return EXIT_SUCCESS;
}
