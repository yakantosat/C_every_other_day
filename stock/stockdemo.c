#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mstack.h"
#include "stock.h"
#define BUFF_SIZE 512
#define COMM_NUM  4

static void init_messages(void);

int main(int argc, char **argv) {
    init_messages();

    char buffer[BUFF_SIZE], *ch;
    char command[COMM_NUM][10];
    int change, i = 0, j, id = 1;

    stock_t *shead, *tmp, *snew;
    part_t *phead, *new;

    phead = (part_t *) malloc(sizeof(part_t));
    if (phead == NULL) {
        perror("phead");
	exit(EXIT_FAILURE);
    }

    shead = (stock_t *) malloc(sizeof(stock_t));
    if (shead == NULL) {
        perror("shead");
	exit(EXIT_FAILURE);
    }

    if (argc < 1) {
        perror("input file error");
	exit(EXIT_FAILURE);
    }
    mystack_t s;
    initStack(&s);
    upload(argv[1], shead, phead, &s);

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
	    unload(argv[1], shead);
	    end(phead);
	    s_end(shead);
	    break;
	} else if (strcmp(command[0], "new") == 0) {
	    int iid = pop(&s);
	    printf("%d\n", iid);
	    new = newpart(phead);
	    printf("ok\n");
	    new->id = iid;
	    strcpy(new->desc, command[1]);
	    new->num = atoi(command[2]);
	    new->price = atoi(command[3]);

	    snew = newstock(shead);
	    snew->id = iid;
	    snew->num = new->num;
	    snew->sold = 0;
	    strcpy(snew->desc, command[1]);
	    snew->total = new->num * new->price;
	    printf("> ");
	} else if (strcmp(command[0], "print") == 0) {
	    printparts(phead, command[1]);
	    printf("> ");
	} else if (strcmp(command[0], "delete") == 0) { 
	    delpart(&shead, &phead, atoi(command[1]));
	    push(&s, atoi(command[1]));
	    printf("> ");
	} else if (strcmp(command[0], "buy") == 0) {
	    buypart(shead, phead, atoi(command[1]), atoi(command[2]), atoi(command[3]));
	    printf("> ");
	} else if (strcmp(command[0], "total") == 0) {
	    totalstocks(shead);
	    printf("> ");
	} else if (strcmp(command[0], "sell") == 0) {
	    sellpart(shead, phead, atoi(command[1]), atoi(command[2]), atoi(command[3]));
	    printf("> ");
	} else {
	    perror("command error");
	    //exit(EXIT_FAILURE);
	    printf("> ");
	}
    }

    return 0;
}

static void init_messages(void) {
    puts("stock system");
    puts("Begin!");
}
