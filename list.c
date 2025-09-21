// list/list.c
//
// Implementation for linked list.
//
// <Author>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

/* Allocate a new, empty list. Heap allocated. */
list_t *list_alloc() {
    list_t *l = (list_t *) malloc(sizeof(list_t));
    if (l == NULL) return NULL;
    l->head = NULL;
    return l;
}

/* Free the list and all nodes (heap). Safe with NULL. */
void list_free(list_t *1) {
