#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "singly_linked_list_node.h"

static Node *ssl_reverse(Node *first);
static Node *add_node(Node *first);
static void free_node(Node *first);
static void display_node(Node *first);

int main(void) {
    Node *head = (Node *) malloc(sizeof(Node));
    Node *tmp;
    if (head == NULL) {
        puts("memory error.");
	return 1;
    }

    head->next = NULL;
    
    tmp = add_node(head);
    tmp->value = 10;

    tmp = add_node(head);
    tmp->value = 15;

    tmp = add_node(head);
    tmp->value = 5;

    tmp = add_node(head);
    tmp->value = 19;

    printf("Before reverse: \n");
    display_node(head);

    ssl_reverse(head);

    printf("After reverse: \n");
    display_node(head);

    free_node(head);
    return 0;
}

static Node *ssl_reverse(Node *first) {
    Node *current, *prev, *next;

    current = first->next;
    next = current->next;
    current->next = NULL;

    while (next) {
        prev = next->next;
	next->next = current;
	current = next;
	next = prev;
    }

    first->next = current;

    return first;
}

static Node *add_node(Node *first) {
    Node *new = (Node *) malloc(sizeof(Node));
    if (new == NULL) {
        puts("memory error.");
	return NULL;
    }

    Node *temp;
    temp = first->next;

    if (temp) {
        new->next = first->next;
	first->next = new;
    } else {
        first->next = new;
	new->next = NULL;
    }

    return new;
}

static void free_node(Node *first) {
    Node *temp;
    temp = first->next;

    while (temp) {
        first->next = temp->next;
	free(temp);
	temp = first->next;
    }
    free(first);
}

static void display_node(Node *first) {
    Node *temp;
    temp = first->next;

    while (temp) {
        printf("%d ", temp->value);
	temp = temp->next;
    }
    printf("\n");
}
