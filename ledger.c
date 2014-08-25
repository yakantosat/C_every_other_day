#include <stdio.h>
/*
 * gcc -g -o ledger ledger.c -DOPTION_LONG
 * gcc -g -o ledger ledger.c -DOPTION_DETAILED
 * gcc -g -o ledger ledger.c (default)
 * */

static void print_ledger_long(int x) {
    printf("print_ledger_long: %d\n", x);
}

static void print_ledger_detailed(int x) {
    printf("print_ledger_detailed: %d\n", x);
}

static void print_ledger_default(int x) {
    printf("print_ledger_default: %d\n", x);
}

void print_ledger(int x) {
#ifdef OPTION_LONG
#define OK 1
    print_ledger_long(x);
#endif

#ifdef OPTION_DETAILED
#define OK 1
    print_ledger_detailed(x);
#endif

#ifndef OK
    print_ledger_default(x);
#endif
}

int main(void) {
    print_ledger(5);

    return 0;
}
