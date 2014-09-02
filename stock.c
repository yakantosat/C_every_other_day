#include "stock.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

part_t *newpart(part_t *phead) {
    part_t *new = (part_t *) malloc(sizeof(part_t));
    part_t *tmp;
    if (new == NULL) {
        perror("new");
	exit(EXIT_FAILURE);
    }

    tmp = phead->next;
    if (tmp) {
        phead->next = new;
	new->next = tmp;
    } else {
        phead->next = new;
	new->next = NULL;
    }
    
    return new;
}

void printparts(part_t *phead, char *flag) {
    part_t *tmp;
    tmp = phead->next;

    if (strcmp(flag, "all") == 0) {
        while (tmp) {
            printf("ID: %d, DESC: %s, NUM: %d, PRICE: %d\n", tmp->id, tmp->desc, tmp->num, tmp->price);
	    tmp = tmp->next;
        }
    } else {
        int id = atoi(flag);
	while (tmp) {
	    if (tmp->id == id) {
	        printf("ID: %d, DESC: %s, NUM: %d, PRICE: %d\n", tmp->id, tmp->desc, tmp->num, tmp->price);
		break;
	    }
	    tmp = tmp->next;
	}
    }
}

void end(part_t *phead) {
    part_t *tmp;
    tmp = phead->next;

    while (tmp) {
        phead->next = tmp->next;
	free(tmp);
	tmp = phead->next;
    }
    free(phead);
}

int delpart(part_t **phead, int id) {
    part_t *tmp;

    while ((tmp = *phead) != NULL && tmp->id != id) {
        phead = &(tmp->next);
    }

    if (tmp->id == id) {
        *phead = tmp->next;
	free(tmp);
	return 1;
    } else {
        return 0;
    }
}
