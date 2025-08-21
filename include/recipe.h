#ifndef RECIPE_H
#define RECIPE_H

#include "structures.h"

void add_recipe(recipe_book *R, char *name);
void remove_recipe(recipe_book *R, char *name);
recipe *search_recipe(recipe_book *R, char *name);
ingredient *search_recipe_ingredients(recipe_book *R, char *name);
ingredient *create_list();
int calculate_weight(ingredient *l);

#endif // RECIPE_H
