#include <stdio.h>
#include "mstack.h"
#include "stock.h"

int stackIsEmpty(mystack_t s) {
    if (s.top == 0)
        return 1;
    else
        return 0;
}

void push(mystack_t *sp, int x) {
    sp->top += 1;
    sp->key[sp->top] = x;
}

int pop(mystack_t *sp) {
    if (sp->top == 0) {
        return -1;
    } else {
        sp->top--;
	return sp->key[sp->top+1];
    }
}

void initStack(mystack_t *s) {
    int i;
    for (i = 1; i <= M; i++) {
        s->top++;
	s->key[i] = i;
    }
}
