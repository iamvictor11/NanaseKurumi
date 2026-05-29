#include <stdio.h>
#include "nanaku/nk.h"
#include "nanaku/container/str.h"

nkAllocator allocator = NK_DEFAULT_ALLOCATOR;

NK_DEC_STRING(test, String)
NK_DEF_STRING(test, String)
NK_IMPL_STRING(test, String, &allocator)

int main()
{
    testString_T str = {};
    testStringDef def = testNullStringDef();
    testStringCreate(&str, &def);
    testStringAssign(&str, 3, "abc");
    printf("%s, hash: %zu", testStringToCstr(&str), testStringHash(&str));
    int key;
    scanf("%d", &key);
    return EXIT_SUCCESS;
}
