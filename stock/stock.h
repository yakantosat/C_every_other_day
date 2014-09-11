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
    int num;
    int sold;
    int total;
    char desc[40];
};

part_t *newpart(part_t *phead);
stock_t *newstock(stock_t *shead);
void freeparts(part_t *phead);
void buypart(stock_t *shead, part_t *phead, int id, int num, int price);
void sellpart(stock_t *shead, part_t *phead, int id, int num, int sell);
void delpart(stock_t **shead, part_t **phead, int id);
void printparts(part_t *phead, char *flag);
void totalstocks(stock_t *shead);
void end(part_t *phead);
void s_end(stock_t *shead);

void upload(char *filename, stock_t *shead, part_t *phead, mystack_t *s);
void unload(char *filename, stock_t *shead);
