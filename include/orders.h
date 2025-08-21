#ifndef ORDERS_H
#define ORDERS

#include "structures.h"

void insert_order(queue *C, order *x);
int check_ingredients(warehouse *M, ingredient *l, int q);
void check_waiting_orders(warehouse *M, queue *C);
int waiting_recipes(order *x, char *s);
void load_shipper(order **corr, queue *C, int q);
void add_order_in_shipper(order **corr, order *x);
void print_shipper(order *x);

#endif // ORDERS_H
