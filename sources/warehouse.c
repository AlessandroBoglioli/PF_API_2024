#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/warehouse.h"
#include "../include/utils.h"

lot *lot_search(warehouse *M, char *name) {
    lot *x = M->table[hash_f(string_to_int(name))];
    while (x != NULL) {
        if (strcmp(x->ingredient_name, name) == 0) {
            return x;
        }
        x = x->next;
    }
    return NULL;
}

void add_information(lot *x) {
    info *y = (info *)malloc(sizeof(info));
    (void)scanf("%hu", &y->quantity);
    (void)scanf("%d", &y->expiration);
    y->next = NULL;

    if (x->information == NULL) {
        x->information = y;
    } else {
        info *z = x->information;
        info *w = z;
        while (z != NULL && z->expiration < y->expiration) {
            w = z;
            z = z->next;
        }
        if (z == NULL) {
            w->next = y;
        } else {
            if (x->information == z) {
                y->next = z;
                x->information = y;
            } else {
                w->next = y;
                y->next = z;
            }
        }
    }
}

void create_lot(warehouse *M, char *name) {
    lot *x = (lot *)malloc(sizeof(lot));
    x->ingredient_name = malloc(strlen(name) + 1);
    strcpy(x->ingredient_name, name);
    
    x->information = (info *)malloc(sizeof(info));
    (void)scanf("%hu", &x->information->quantity);
    (void)scanf("%d", &x->information->expiration);
    x->information->next = NULL;

    int hash_key = hash_f(string_to_int(name));
    x->next = M->table[hash_key];
    M->table[hash_key] = x;
}

void hash_insert(warehouse *M, char *name) {
    lot *x = lot_search(M, name);
    if (x == NULL) {
        create_lot(M, name);
    } else {
        add_information(x);
    }
}

int verify_information(lot *x, int quantity) {
    while (x->information != NULL && x->information->expiration <= time) {
        info *expired = x->information;
        x->information = x->information->next;
        free(expired);
    }

    info *y = x->information;
    int total_quantity = 0;
    while (y != NULL) {
        total_quantity += y->quantity;
        if (total_quantity >= quantity) {
            return 1;
        }
        y = y->next;
    }
    return 0;
}

void update_information(lot *x, int quantity) {
    info *current = x->information;
    info *prev = NULL;

    while (quantity > 0 && current != NULL) {
        if (current->quantity > quantity) {
            current->quantity -= quantity;
            quantity = 0;
        } else {
            quantity -= current->quantity;
            if (prev == NULL) {
                x->information = current->next;
                free(current);
                current = x->information;
            } else {
                prev->next = current->next;
                free(current);
                current = prev->next;
            }
        }
    }
}
