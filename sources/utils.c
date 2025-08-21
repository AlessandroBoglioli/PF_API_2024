#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/utils.h"

names_list *N;

void init_name_manager() {
    N = (names_list *)malloc(sizeof(names_list));
    for (int i = 0; i < HASH_DIM; i++) {
        N->table[i] = NULL;
    }
}

int string_to_int(char *x) {
    int t = 0;
    for (size_t i = 0; i < strlen(x); i++) {
        t += (int)x[i];
    }
    return t;
}

int hash_f(int x) {
    return x % HASH_DIM;
}

char *assign_name(char *name) {
    int chiave = hash_f(string_to_int(name));
    names *x;
    if (N->table[chiave] == NULL) {
        x = (names *)malloc(sizeof(names));
        x->name = malloc(strlen(name) + 1);
        strcpy(x->name, name);
        x->next = NULL;
        N->table[chiave] = x;
        return x->name;
    }
    x = N->table[chiave];
    while (x != NULL) {
        if (strcmp(x->name, name) == 0) {
            return x->name;
        }
        x = x->next;
    }
    x = (names *)malloc(sizeof(names));
    x->name = malloc(strlen(name) + 1);
    strcpy(x->name, name);
    x->next = N->table[chiave];
    N->table[chiave] = x;
    return x->name;
}
