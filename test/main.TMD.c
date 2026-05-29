#include <stdlib.h>
#include <stdio.h>
#include "project_name/platform/console.h"
#include "project_name/TMD.h"

DEC Test;
DEF Test IS
int i;
AS Test;

INLINE FUNC void testf(int i) IMPL
Test test = {0};
LOOP i < 10 DO
    printf("%d", test.i);
    i++;
    test.i = i;
END
END

int main()
{
    pnxSetConsoleOutputCP_UTF8();

    testf(0);

    pnxGetChar();
    return EXIT_SUCCESS;
}
