#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stock.h"
#define BUFF_SIZE 512
#define COMM_NUM  4

static void init_messages(void);

int main(int argc, char **argv) {
    init_messages();

    char buffer[BUFF_SIZE], *ch;
    char command[COMM_NUM][10];
    int change, i = 0, j, id = 1;

    part_t *new;
    part_t *phead = (part_t *) malloc(sizeof(part_t));
    if (phead == NULL) {
        perror("phead");
	exit(EXIT_FAILURE);
    }

    printf("> ");
    while (fgets(buffer, BUFF_SIZE, stdin) != NULL) {
        buffer[strlen(buffer) - 1] = '\0';
	ch = buffer;
	for (j = 0; j <= strlen(buffer); j++) {
	    if (buffer[j] == ' ' || buffer[j] == '\0') {
	        strncpy(command[i], ch, (buffer + j) - ch);
		command[i][(buffer+j)-ch] = '\0';
		ch = buffer + j + 1;
		i++;
	    }
	}
	i = 0;

	if (strcmp(command[0], "end") == 0) {
	    end(phead);
	    break;
	} else if (strcmp(command[0], "new") == 0) {
	    new = newpart(phead);
	    new->id = id++;
	    strcpy(new->desc, command[1]);
	    new->num = atoi(command[2]);
	    new->price = atoi(command[3]);
	    printf("> ");
	} else if (strcmp(command[0], "print") == 0) {
	    printparts(phead, command[1]);
	    printf("> ");
	} else if (strcmp(command[0], "delete") == 0) { 
	    delpart(&phead, atoi(command[1]));
	    printf("> ");
	} else {
	    perror("command error");
	    exit(EXIT_FAILURE);
	}
    }


    return 0;
}

static void init_messages(void) {
    puts("stock system");
    puts("Begin!");
}
