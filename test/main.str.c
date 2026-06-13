#include <stdio.h>
#include "c_template/platform/console.h"
#include "c_template/version.h"
#include "c_template/container/str.h"

C_TEMPLATE_VERSION_STRUCT(static inline, test, Test)

C_TEMPLATE_DECL_ALLOCATOR(static inline, test, Test)
C_TEMPLATE_DEFN_ALLOCATOR(static inline, test, Test)
C_TEMPLATE_IMPL_ALLOCATOR(static inline, test, Test)

TestAllocator allocator;

C_TEMPLATE_DECL_STRING(static inline, test, Test, String)
C_TEMPLATE_DEFN_STRING(static inline, test, Test, String)
C_TEMPLATE_IMPL_STRING(static inline, test, Test, String, &allocator)

int main()
{
    osSetConsoleOutputCP_UTF8();

    allocator = testDefaultAllocator();

    TestVersion version = C_TEMPLATE_VERSION;
    printf("%s\n", version.name);
    TestString str = testStringCreateFromFormat("0%d", C_TEMPLATE_VERSION_CAST_UINT(version));
    printf("%s, hash: %zu, int: %d\n", testStringToCstr(str), testStringHash(str), testStringToInt(str));
    testStringAssignFromCstr(str, "-0xF'F");
    printf("%s, hash: %zu, int: %d\n", testStringToCstr(str), testStringHash(str), testStringToInt(str));
    testStringAssignFromCstr(str, "01.2e-3");
    printf("%s, hash: %zu, float: %f\n", testStringToCstr(str), testStringHash(str), testStringToFloat(str));
    C_TEMPLATE_STRING_FOREACH(c, str)
        printf("%c", *c);
    printf("\n");
    testStringDestroy(str);

    osGetChar();
    return EXIT_SUCCESS;
}
