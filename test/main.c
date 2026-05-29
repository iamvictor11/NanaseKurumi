#include <stdio.h>
#include "project_name/pn.h"
#include "project_name/platform/console.h"
#include "project_name/container/str.h"

pn_Allocator allocator = PN_DEFAULT_ALLOCATOR;

PN_DEC_STRING(test, String)
PN_DEF_STRING(test, String)
PN_IMPL_STRING(test, String, &allocator)

int main()
{
    pn_SetConsoleOutputCP_UTF8();
    testString str = testStringCreateFromFormat("%s", "-011");
    printf("%s, hash: %zu, int: %d\n", testStringToCstr(str), testStringHash(str), testStringToInt(str));
    testStringAssignFromCstr(str, "0xF'F");
    printf("%s, hash: %zu, int: %d\n", testStringToCstr(str), testStringHash(str), testStringToInt(str));
    testStringAssignFromCstr(str, "01.2e-3");
    printf("%s, hash: %zu, float: %f\n", testStringToCstr(str), testStringHash(str), testStringToFloat(str));
    PN_STRING_FOREACH(char, str, c)
        printf("%c", *c);
    testStringDestroy(str);
    pn_GetChar();
    return EXIT_SUCCESS;
}
