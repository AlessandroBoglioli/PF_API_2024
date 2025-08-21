#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/recipe.h"
#include "../include/utils.h"

recipe *search_recipe(recipe_book *R, char *name) {
    recipe *x = R->table[hash_f(string_to_int(name))];
    while (x != NULL) {
        if (strcmp(x->name, name) == 0) {
            return x;
        }
        x = x->next;
    }
    return NULL;
}

ingredient *create_list() {
    char temp;
    char tnome[MAX_LEN_WORD];
    unsigned short tquantity;
    ingredient *head = NULL;

    do {
        (void)scanf("%s %hu", tnome, &tquantity);

        ingredient *new_ingredient = (ingredient *)malloc(sizeof(ingredient));
        new_ingredient->name = assign_name(tnome);
        new_ingredient->lot_cor = NULL;
        new_ingredient->quantity = tquantity;
        
        new_ingredient->next = head;
        head = new_ingredient;

        (void)scanf("%c", &temp);
    } while (temp != '\n');
    
    return head;
}

void add_recipe(recipe_book *R, char *name) {
    if (search_recipe(R, name) != NULL) {
        printf("ignorato\n");
        ingredient *temp_list = create_list();
        while (temp_list != NULL) {
            ingredient *to_free = temp_list;
            temp_list = temp_list->next;
            free(to_free);
        }
        return;
    }

    recipe *x = (recipe *)malloc(sizeof(recipe));
    x->name = assign_name(name);
    x->ingredient_list = create_list();
    
    int chiave = hash_f(string_to_int(x->name));
    x->next = R->table[chiave];
    R->table[chiave] = x;
    printf("aggiunta\n");
}

void remove_recipe(recipe_book *R, char *name) {
    int chiave = hash_f(string_to_int(name));
    recipe *current = R->table[chiave];
    recipe *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (prev == NULL) {
                R->table[chiave] = current->next;
            } else {
                prev->next = current->next;
            }
            ingredient *ing = current->ingredient_list;
            while(ing != NULL) {
                ingredient *temp = ing;
                ing = ing->next;
                free(temp);
            }
            free(current);
            printf("rimossa\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("non presente\n");
}


ingredient *search_recipe_ingredients(recipe_book *R, char *name) {
    recipe *x = search_recipe(R, name);
    if (x == NULL) {
        return NULL;
    }
    return x->ingredient_list;
}

int calculate_weight(ingredient *l) {
    int totale = 0;
    while (l != NULL) {
        totale += l->quantity;
        l = l->next;
    }
    return totale;
}
