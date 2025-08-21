#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "structures.h"

void hash_insert(warehouse *M, char *name);
lot *lot_search(warehouse *M, char *name);
void create_lot(warehouse *M, char *name);
void add_information(lot *x);
void update_information(lot *x, int quantity);
int verify_information(lot *x, int quantity);

#endif // WAREHOUSE_H
