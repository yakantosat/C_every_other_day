#include "mstack.h"
#include "stock.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

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

stock_t *newstock(stock_t *shead) {
    stock_t *new = (stock_t *) malloc(sizeof(stock_t));
    stock_t *tmp;
    if (new == NULL) {
        perror("new");
	exit(EXIT_FAILURE);
    }

    tmp = shead->next;
    if (tmp) {
        shead->next = new;
	new->next = tmp;
    } else {
        shead->next = new;
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

void s_end(stock_t *shead) {
    stock_t *tmp;
    tmp = shead->next;

    while (tmp) {
        shead->next = tmp->next;
	free(tmp);
	tmp = shead->next;
    }
    free(shead);
}

void delpart(stock_t **shead, part_t **phead, int id) {
    part_t *tmp;
    stock_t *stmp;

    while ((tmp = *phead) != NULL && tmp->id != id) {
        phead = &(tmp->next);
    }

    if (tmp->id == id) {
        *phead = tmp->next;
	free(tmp);
    }

    while ((stmp = *shead) != NULL && stmp->id != id) {
        shead = &(stmp->next);
    }

    if (stmp->id == id) {
        *shead = stmp->next;
	free(stmp);
    }
}

void buypart(stock_t *shead, part_t *phead, int id, int num, int price) {
    part_t *ptmp;
    ptmp = phead->next;

    while (ptmp) {
        if (ptmp->id == id) {
	    ptmp->num += num;
	    ptmp->price = price;
	    break;
	}
	ptmp = ptmp->next;
    }

    stock_t *stmp;
    stmp = shead->next;

    while (stmp) {
        if (stmp->id == id) {
	    stmp->total = ptmp->num * ptmp->price;
	    stmp->num += num;
	    break;
	}
	stmp = stmp->next;
    }
}

void totalstocks(stock_t *shead) {
    stock_t *tmp;
    tmp = shead->next;

    while (tmp) {
        printf("ID: %d, DESC: %s, Total: %d\n", tmp->id, tmp->desc, tmp->total);
	tmp = tmp->next;
    }
}

void sellpart(stock_t *shead, part_t *phead, int id, int num, int sell) {
    part_t *ptmp;
    stock_t *stmp;
    ptmp = phead->next;

    while (ptmp) {
        if (id == ptmp->id) {
	    if (num > ptmp->num) {
	        printf("sell not\n");
	        goto EXIT;
	    } else {
	        ptmp->num -= num;
	    }
	    break;
	}
	ptmp = ptmp->next;
    }

    stmp = shead->next;
    while (stmp) {
        if (id == stmp->id) {
	    stmp->total = (ptmp->num * ptmp->price) + (num * sell);
	    stmp->num -= num;
	    stmp->sold += num;
	    break;
	} else {
	    stmp = stmp->next;
	}
    }
EXIT:
    printf("Num is bigger than stock.\n");
}

void upload(char *filename, stock_t *shead, part_t *phead, mystack_t *s) {
    FILE *fp;
    size_t ret;
    stock_t *sbuffer = (stock_t *) malloc(sizeof(stock_t));

    if (access(filename, F_OK) == 0) {
        fp = fopen(filename, "rb");
	if (fp == NULL) {
	    perror("file error");
	    exit(EXIT_FAILURE);
	}

	while (fread(sbuffer, 1, sizeof(stock_t), fp)) {
	    int iid = pop(s);
	    stock_t *tmp = newstock(shead);
	    tmp->id = iid;
	    tmp->total = sbuffer->total;
	    tmp->num = sbuffer->num;
	    tmp->sold = sbuffer->sold;
	    strcpy(tmp->desc, sbuffer->desc);

	    part_t *ptmp = newpart(phead);
	    ptmp->id = iid;
	    strcpy(ptmp->desc, sbuffer->desc);
	    ptmp->num = sbuffer->num;
	    ptmp->price = sbuffer->total / (sbuffer->num + sbuffer->sold);
	}
	fclose(fp);
	free(sbuffer);
    }
}

void unload(char *filename, stock_t *shead) {
    FILE *fp;
    stock_t *tmp;
    size_t ret;

    fp = fopen(filename, "wb");
    if (fp == NULL) {
	perror("open file error");
	exit(EXIT_FAILURE);
    }

    tmp = shead->next;
    while (tmp) {
	ret = fwrite(tmp, sizeof(stock_t), 1, fp);
	if (ret != 1) {
	    perror("write error");
	    exit(EXIT_FAILURE);
	}
	tmp = tmp->next;
    }
    fclose(fp);
}
