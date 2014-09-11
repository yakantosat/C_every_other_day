/*
 * stack.h
 * */
#ifndef _MSTACK_H
#define _MSTACK_H

#define M 100

typedef struct mystack_s mystack_t;
struct mystack_s {
    int top;
    int key[M];
};

void initStack(mystack_t *s);
int stackIsEmpty(mystack_t s);
void push(mystack_t *s, int x);
int pop(mystack_t *s);

#endif
