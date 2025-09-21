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
    if (l == NULL) return;
    node_t *cur = l->head;
    while (cur != NULL) {
        node_t *next = cur->next;
        free(cur);
        cur = next;
    }
    free(l);
}

/* Return a malloc'd string representation of the list. Caller should free it. */
char * listToString(list_t *l) {
    size_t cap = 1024 * 8;
    char *buf = (char *) malloc(cap);
    if (buf == NULL) return NULL;
    size_t pos = 0;
    buf[0] = '\0';

    if (l == NULL) {
        snprintf(buf, cap, "NULL");
        return buf;
    }

node_t *curr = 1->head;
if (curr == NULL) {
    snprintf(buf, cap, "NULL");
    return buf;
}

while (curr != NULL) {
    int written = snprintf(buf + pos, cap - pos, "%d->, curr->value);
    
