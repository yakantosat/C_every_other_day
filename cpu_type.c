#include <stdio.h>
#include <stdlib.h>

#include "cpu_type.h"

int cpu_type(void) {
    int count = 0;
#if defined(VAX)
    count++;
#endif
#if defined(M68000)
    count++;
#endif
#if defined(M68020)
    count++;
#endif
#if defined(I80386)
    count++;
#endif
#if defined(X6809)
    count++;
#endif
#if defined(X6502)
    count++;
#endif
#if defined(U3B2)
    count++;
#endif

    if (count == 0)
        return CPU_UNKNOWN;
    else if (count != 1)
        return CPU_UNKNOWN;

#if defined(VAX)
    return CPU_VAX;
#elif defined(M68000)
    return CPU_68000;
#elif defined(M68020)
    return CPU_68020;
#elif defined(I80386)
    return CPU_80386;
#elif defined(X6809)
    return CPU_6809;
#elif defined(X6502)
    return CPU_6502;
#elif defined(U3B2)
    return CPU_3B2;
#else
    return CPU_UNKNOWN;
#endif
}

int main(void) {
    int r;
    r = cpu_type();
    printf("The cpu type is: %d\n", r);

    return 0;
}
