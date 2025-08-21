#ifndef UTILS_H
#define UTILS_H

#include "structures.h"

extern int time;
extern names_list *N;

int string_to_int(char *x);
int hash_f(int x);
char *assign_name(char *name);
void init_name_manager();

#endif // UTILS_H
