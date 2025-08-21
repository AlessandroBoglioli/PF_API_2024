#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdbool.h>

#define MAX_LEN_WORD 256
#define HASH_DIM 10000

typedef struct info {
    unsigned short int quantity;
    int expiration;
    struct info *next;
} info;

typedef struct lot {
    char *ingredient_name;
    struct lot *next;
    info *information;
} lot;

typedef struct warehouse {
    lot *table[HASH_DIM];
} warehouse;

typedef struct ingredient {
    char *name;
    unsigned short int quantity;
    struct ingredient *next;
    lot *lot_cor;
} ingredient;

typedef struct recipe {
    char *name;
    struct recipe *next;
    ingredient *ingredient_list;
} recipe;

typedef struct recipe_book {
    recipe *table[HASH_DIM];
} recipe_book;

typedef struct order {
    char *name;
    unsigned short int quantity;
    int arrival_time;
    ingredient *ingredient_list;
    struct order *next;
    bool ready;
} order;

typedef struct queue {
    order *head;
    order *tail;
} queue;

typedef struct names {
    char *name;
    struct names *next;
} names;

typedef struct names_list {
    names *table[HASH_DIM];
} names_list;

#endif // STRUCTURES_H
