#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "singly_linked_list_node.h"

static Node *add_node(Node *head);
static void free_node(Node *head);
static void display_node(Node *head);
static int ssl_remove(Node **rootp, Node *node);

int main(void) {
    Node *head = (Node *) malloc(sizeof(Node));
    Node *new;

    int values[] = {10, 16, 7, 15, 22, 56};
    int i;

    if (head == NULL) {
        printf("memory error.\n");
	return 1;
    }

    head->next = NULL;

    for (i = 0; i < sizeof(values)/sizeof(int); i++) {
        new = add_node(head);
	new->value = values[i];
    }

    printf("Before cut down node: \n");
    display_node(head);

    printf("After cut down node: \n");
    ssl_remove(&head, head->next->next);
    display_node(head);

    free_node(head);

    return 0;
}

static Node *add_node(Node *head) {
    Node *new = (Node *) malloc(sizeof(Node));
    Node *temp;
    if (new == NULL) {
        printf("memory error.\n");
	return NULL;
    }

    temp = head->next;

    if (temp) {
        new->next = temp;
        head->next = new;
    } else {
        head->next = new;
	new->next = NULL;
    }

    return new;
}

static void free_node(Node *head) {
    Node *temp;
    temp = head->next;

    while (temp) {
        head->next = temp->next;
	free(temp);
	temp = temp->next;
    }
    free(head);
}

static void display_node(Node *head) {
    Node *temp;

    temp = head->next;
    while (temp) {
        printf("%d, ", temp->value);
	temp = temp->next;
    }
    printf("\n");
}

static int ssl_remove(Node **head, Node *node) {
    Node *temp;
    
    while ((temp = *head) != NULL && temp != node) {
        head = &temp->next;
    }

    if (temp == node) {
        *head = temp->next;
	free(temp);
	return 1;
    } else {
        return 0;
    }
}
