#include "xk/xkvector.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    printf("\x1b%%G");

    xkvector(int) intv = {};
    xkvectorinit(int)(&intv, 10);

    for (int i = 0; i < xkvectorcapacity(int)(&intv); ++i)
        xkvectorpushback(int)(&intv, i);

    xkvectorforeach(int, &intv, e)
        printf("%d, ", *e);

    xkvectorfree(int)(&intv);

    getchar();
    return 0;
}
