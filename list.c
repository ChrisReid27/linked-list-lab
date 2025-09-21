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
    if (written < 0) break; /* encoding error */
        pos += (size_t) written;
        if (pos + 64 >= cap) { /* grow if necessary */
            cap *= 2;
            char *tmp = realloc(buf, cap);
            if (!tmp) break; /* keep existing buffer */
            buf = tmp;
        }
        curr = curr->next;
    }
    /* append NULL */
    snprintf(buf + pos, cap - pos, "NULL");
    return buf;
}

/* Print convenience function (stack-allocated format call). */
void list_print(list_t *l) {
    char *s = listToString(l);
    if (s) {
        printf("%s\n", s);
        free(s);
    } else {
        printf("(null)\n");
    }
}

/* Create a new node on the heap. */
node_t * getNode(elem value) {
    node_t *mynode = (node_t *) malloc(sizeof(node_t));
    if (mynode == NULL) return NULL;
    mynode->value = value;
    mynode->next = NULL;
    return mynode;
}

/* Return the number of nodes in the list (stack-local counter). */
int list_length(list_t *l) {
    if (l == NULL) return 0;
    int count = 0;
    node_t *cur = l->head;
    while (cur != NULL) {
        count++;
        cur = cur->next;
    }
    return count;
}

/* Add to back of list. Heap allocates the new node. */
void list_add_to_back(list_t *l, elem value) {
    if (l == NULL) return;
    node_t *n = getNode(value);
    if (n == NULL) return;
    if (l->head == NULL) {
        l->head = n;
        return;
    }
    node_t *cur = l->head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
}

