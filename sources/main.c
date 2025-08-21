#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/structures.h"
#include "../include/utils.h"
#include "../include/warehouse.h"
#include "../include/recipe.h"
#include "../include/orders.h"

int time = -1;

int main() {
    warehouse *M = (warehouse *)malloc(sizeof(warehouse));
    recipe_book *R = (recipe_book *)malloc(sizeof(recipe_book));
    init_name_manager();

    for (int i = 0; i < HASH_DIM; i++) {
        M->table[i] = NULL;
        R->table[i] = NULL;
    }

    queue *orders = (queue *)malloc(sizeof(queue));
    orders->head = NULL;
    orders->tail = NULL;

    order *shipper = NULL;
    int shipper_time;
    int shipper_capacity;
    (void)scanf("%d", &shipper_time);
    (void)scanf("%d", &shipper_capacity);

    char instruction[17];
    char end_line;
    char recipe_name[MAX_LEN_WORD];

    while (scanf("%s", instruction) != EOF) {
        time++;

        if (time && time % shipper_time == 0) {
            load_shipper(&shipper, orders, shipper_capacity);
        }

        if (strcmp(instruction, "rifornimento") == 0) {
            do {
                (void)scanf("%s", recipe_name);
                hash_insert(M, recipe_name);
                (void)scanf("%c", &end_line);
            } while (end_line != '\n');
            printf("rifornito\n");
            check_waiting_orders(M, orders);
        }

        if (strcmp(instruction, "add_recipe") == 0) {
            (void)scanf("%s", recipe_name);
            add_recipe(R, recipe_name);
        }

        if (strcmp(instruction, "remove_recipe") == 0) {
            (void)scanf("%s", recipe_name);
            if (!waiting_recipes(orders->head, recipe_name)) {
                remove_recipe(R, recipe_name);
            } else {
                printf("orders in sospeso\n");
            }
        }

        if (strcmp(instruction, "order") == 0) {
            order *new_order = (order *)malloc(sizeof(order));
            (void)scanf("%s", recipe_name);
            new_order->name = assign_name(recipe_name);
            (void)scanf("%hu", &new_order->quantity);
            new_order->arrival_time = time;
            new_order->ready = false;
            new_order->ingredient_list = search_recipe_ingredients(R, new_order->name);
            new_order->next = NULL;

            if (new_order->ingredient_list == NULL) {
                printf("rifiutato\n");
                free(new_order);
            } else {
                if (check_ingredients(M, new_order->ingredient_list, new_order->quantity) == 1) {
                    new_order->ready = true;
                }
                printf("accettato\n");
                insert_order(orders, new_order);
            }
        }
    }
    
    time++;
    if (time && time % shipper_time == 0) {
        load_shipper(&shipper, orders, shipper_capacity);
    }
    
    return 0;
}
