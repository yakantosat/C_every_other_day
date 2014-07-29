#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node Node;
struct node {
    int value;
    Node * next;
};

Node *add(Node *head);
void node_free(Node *head);
void display(Node *head);

int main(void) {
    Node *head = (Node *) malloc(sizeof(Node));
    Node *temp;

    if (head == NULL) {
        puts("memory error.");
        return;
    }

    head->next = NULL;

    temp = add(head);
    temp->value = 5;

    temp = add(head);
    temp->value = 10;

    temp = add(head);
    temp->value = 15;

    display(head);

    node_free(head);

    return 0;
    
}

void display(Node *head) {
    Node *temp;
    temp = head->next;

    while (temp) {
        printf("%d\n", temp->value);
        temp = temp->next;
    }
}

Node *add(Node *head) {
    Node *new = (Node *) malloc(sizeof(Node));
    if (new == NULL) {
        puts("memory error.");
        return;
    }

    Node *temp;
    temp = head->next;

#if 0
    new->next = NULL;
    
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = new;
#endif

    if (temp) {
        new->next = head->next;
        head->next = new;
    } else {
        head->next = new;
        new->next = NULL;
    }

    return new;
}

void node_free(Node *head) {
    Node *temp;
    temp = head->next;

    while (temp) {
        head->next = temp->next;
        free(temp);
        temp = head->next;
    }

    free(head);
}
