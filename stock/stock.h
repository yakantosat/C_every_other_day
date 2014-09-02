/*
 * stock.h
 * */

typedef struct part_s part_t;
struct part_s {
    part_t *next;
    int id;
    char desc[40];
    int num;
    int price;
};

typedef struct stock_s stock_t;
struct stock_s {
    stock_t *next;
    int id;
    int total;
};

part_t *newpart(part_t *phead);
void freeparts(part_t *phead);
int buypart(stock_t *shead, int id, int num, int price);
int sellpart(part_t *phead, int id, int num, int sell);
int delpart(part_t **phead, int id);
void printparts(part_t *phead, char *flag);
int totalstocks(stock_t *shead);
void end(part_t *phead);

int upload(char *filename);
int unload(char *filename);
