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

/* Add to front of list. */
void list_add_to_front(list_t *l, elem value) {
    if (l == NULL) return;
    node_t *n = getNode(value);
    if (n == NULL) return;
    n->next = l->head;
    l->head = n;
}

/* Insert at 1-based index. If index <= 1 insert at front. If index > length+1 insert at back. */
void list_add_at_index(list_t *l, elem value, int index) {
    if (l == NULL) return;
    if (index <= 1 || l->head == NULL) {
        /* If list empty or index <=1, insert at front. */
        list_add_to_front(l, value);
        return;
    }
    int len = list_length(l);
    if (index > len + 1) {
        /* out of bounds -> append to back */
        list_add_to_back(l, value);
        return;
    }
    /* walk to node before insertion point */
    node_t *cur = l->head;
    int i = 1;
    while (cur != NULL && i < index - 1) {
        cur = cur->next;
        i++;
    }
    if (cur == NULL) {
        list_add_to_back(l, value);
        return;
    }
    node_t *n = getNode(value);
    if (n == NULL) return;
    n->next = cur->next;
    cur->next = n;
}


/* Remove from back, return value or -1 on error. */
elem list_remove_from_back(list-t *1) {
    if (1 == NULL || 1->head == NULL) return -1;
    node_t *cur = 1->head;
    if (cur->next == NULL) {
        /* single element */
        elem v = cur->value;
        free(cur);
        1->head = NULL;
        return v;
