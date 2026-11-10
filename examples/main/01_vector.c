#include "stl/stlvector.h"
#include <stdio.h>

stlvectorinst(int)
stlvectordecl(int, inline static)
stlvectorimpl(int, inline static)

int main(int argc, char* argv[])
{
    printf("\x1b%%G");

    stlvector(int) intv = {};
    stlvectorinit(int)(&intv, 10);
    
    for (int i = 0; i < stlvectorcapacity(int)(&intv); ++i)
        stlvectorpush(int)(&intv, i);
    
    stlvectorforeach(int, &intv, e)
        printf("%d, ", *e);
    
    stlvectorfree(int)(&intv);

    getchar();
    return 0;
}
