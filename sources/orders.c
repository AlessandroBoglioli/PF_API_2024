#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/orders.h"
#include "../include/warehouse.h"
#include "../include/recipe.h"
#include "../include/utils.h"

void insert_order(queue *C, order *x) {
    if (C->head == NULL) {
        C->head = x;
        C->tail = x;
    } else {
        C->tail->next = x;
        C->tail = x;
    }
}

int check_ingredients(warehouse *M, ingredient *l, int q) {
    ingredient *x = l;
    lot *y;

    while (x != NULL) {
        if (x->lot_cor == NULL) {
            x->lot_cor = lot_search(M, x->name);
        }
        y = x->lot_cor;
        if (y == NULL || verify_information(y, (long)x->quantity * q) == 0) {
            return 0;
        }
        x = x->next;
    }

    x = l;
    while (x != NULL) {
        y = x->lot_cor;
        update_information(y, (long)x->quantity * q);
        x = x->next;
    }
    return 1;
}

void check_waiting_orders(warehouse *M, queue *C) {
    order *x = C->head;
    while (x != NULL) {
        if (x->ready == 0) {
            if (check_ingredients(M, x->ingredient_list, x->quantity) == 1) {
                x->ready = 1;
            }
        }
        x = x->next;
    }
}

int waiting_recipes(order *x, char *s) {
    order *y = x;
    while (y != NULL) {
        if (strcmp(y->name, s) == 0) {
            return 1;
        }
        y = y->next;
    }
    return 0;
}

void print_shipper(order *x) {
    order *y;
    while (x != NULL) {
        printf("%d %s %hu\n", x->arrival_time, x->name, x->quantity);
        y = x->next;
        free(x);
        x = y;
    }
}

void add_order_in_shipper(order **corr, order *x) {
    if (*corr == NULL) {
        *corr = x;
        return;
    }

    order *y = *corr;
    order *z = NULL;
    long weight_x = (long)calculate_weight(x->ingredient_list) * x->quantity;

    while (y != NULL) {
        long weight_y = (long)calculate_weight(y->ingredient_list) * y->quantity;
        if (weight_x > weight_y || (weight_x == weight_y && x->arrival_time < y->arrival_time)) {
            break;
        }
        z = y;
        y = y->next;
    }

    if (z == NULL) {
        x->next = *corr;
        *corr = x;
    } else {
        z->next = x;
        x->next = y;
    }
}

void load_shipper(order **corr, queue *C, int q) {
    if (C->head == NULL) {
        if (*corr == NULL) printf("camioncino vuoto\n");
        return;
    }

    order *current = C->head;
    order *prev = NULL;

    while (current != NULL) {
        if (current->ready) {
            int peso = calculate_weight(current->ingredient_list) * current->quantity;
            if (peso <= q) {
                q -= peso;
                order *to_ship = current;
             
                if (prev == NULL) {
                    C->head = current->next;
                } else {
                    prev->next = current->next;
                }
                
                if (C->tail == current) {
                    C->tail = prev;
                }
                
                current = current->next;
                to_ship->next = NULL;
                add_order_in_shipper(corr, to_ship);

            } else {
                prev = current;
                current = current->next;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }

    if (*corr != NULL) {
        print_shipper(*corr);
        *corr = NULL;
    } else {
        printf("camioncino vuoto\n");
    }
}
