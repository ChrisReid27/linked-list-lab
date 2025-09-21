// list/list.c
// 
// Implementation for linked list.
//
// <Author>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

typedef int elem;

typedef struct node {
    elem value;
    struct node *next;
} node_t;

typedef struct list {
    node_t *head;
} list_t;

// Allocate a new, empty list.
list_t *list_alloc() {
    list_t *l = (list_t *)malloc(sizeof(list_t));
    if (l == NULL) return NULL;
    l->head = NULL;
    return l;
}

// Free the list and all nodes.
void list_free(list_t *l) {
    if (l == NULL) return;
    node_t *cur = l->head;
    while (cur != NULL) {
        node_t *next = cur->next;
        free(cur);
        cur = next;
    }
    free(l);
}

// Return a malloc'd string representation of the list.
char *listToString(list_t *l) {
    size_t cap = 1024 * 8;
    char *buf = (char *)malloc(cap);
    if (buf == NULL) return NULL;
    size_t pos = 0;
    buf[0] = '\0';

    if (l == NULL || l->head == NULL) {
        snprintf(buf, cap, "NULL");
        return buf;
    }
    
    node_t *curr = l->head;
    while (curr != NULL) {
        int written = snprintf(buf + pos, cap - pos, "%d->", curr->value);
        if (written < 0) {
            break;
        }
        pos += (size_t)written;
        if (pos + 64 >= cap) {
            cap *= 2;
            char *tmp = realloc(buf, cap);
            if (!tmp) {
                break;
            }
            buf = tmp;
        }
        curr = curr->next;
    }
    snprintf(buf + pos, cap - pos, "NULL");
    return buf;
}

// Print convenience function.
void list_print(list_t *l) {
    char *s = listToString(l);
    if (s) {
        printf("%s\n", s);
        free(s);
    } else {
        printf("(null)\n");
    }
}

// Create a new node.
node_t *getNode(elem value) {
    node_t *mynode = (node_t *)malloc(sizeof(node_t));
    if (mynode == NULL) return NULL;
    mynode->value = value;
    mynode->next = NULL;
    return mynode;
}

// Return the number of nodes in the list.
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

// Add to back of list.
void list_add_to_back(list_t *l, elem value) {
    if (l == NULL) return;
    node_t *n = getNode(value);
    if (n == NULL) return;
    if (l->head == NULL) {
        l->head = n;
        return;
    }
    node_t *cur = l->head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = n;
}

// Add to front of list.
void list_add_to_front(list_t *l, elem value) {
    if (l == NULL) return;
    node_t *n = getNode(value);
    if (n == NULL) return;
    n->next = l->head;
    l->head = n;
}

// Insert at 1-based index.
void list_add_at_index(list_t *l, elem value, int index) {
    if (l == NULL) {
        return;
    }
    // If index is 1 or less, or list is empty, add to front.
    if (index <= 1 || l->head == NULL) {
        list_add_to_front(l, value);
        return;
    }

    node_t *n = getNode(value);
    if (n == NULL) {
        return;
    }

    node_t *cur = l->head;
    int i = 1;
    // Traverse to the node BEFORE the target index.
    while (cur != NULL && i < index - 1) {
        cur = cur->next;
        i++;
    }

    // Check if we found a valid insertion point. If not, add to the back.
    if (cur == NULL) {
        // This case is actually handled by the loop condition,
        // but it's good practice to free the node if it can't be added.
        free(n);
        list_add_to_back(l, value);
        return;
    }
    
    n->next = cur->next;
    cur->next = n;
}

// Remove from back.
elem list_remove_from_back(list_t *l) {
    if (l == NULL || l->head == NULL) {
        return -1;
    }

    // Case 1: The list has only one node.
    if (l->head->next == NULL) {
        elem val = l->head->value;
        free(l->head);
        l->head = NULL;
        return val;
    }

    // Case 2: The list has multiple nodes.
    node_t *cur = l->head;
    // Traverse to the second to last node.
    while (cur->next->next != NULL) {
        cur = cur->next;
    }

    node_t *last = cur->next;
    elem val = last->value;
    free(last);
    cur->next = NULL; // This is the corrected line.
    return val;
}

// Remove from front.
elem list_remove_from_front(list_t *l) {
    if (l == NULL || l->head == NULL) {
        return -1;
    }
    node_t *first = l->head;
    elem v = first->value;
    l->head = first->next;
    free(first);
    return v;
}

// Remove at 1-based index.
elem list_remove_at_index(list_t *l, int index) {
    if (l == NULL || l->head == NULL || index < 1) {
        return -1;
    }

    if (index == 1) {
        return list_remove_from_front(l);
    }

    node_t *cur = l->head;
    int i = 1;
    // Traverse to the node BEFORE the target index.
    while (cur != NULL && i < index - 1) {
        cur = cur->next;
        i++;
    }

    // If we've reached the end or the index is out of bounds.
    if (cur == NULL || cur->next == NULL) {
        return -1;
    }

    node_t *victim = cur->next;
    elem val = victim->value;
    cur->next = victim->next;
    free(victim);

    return val;
}

// Checks membership.
bool list_is_in(list_t *l, elem value) {
    if (l == NULL) return false;
    node_t *cur = l->head;
    while (cur != NULL) {
        if (cur->value == value) return true;
        cur = cur->next;
    }
    return false;
}

// Return element at 1-based index.
elem list_get_elem_at(list_t *l, int index) {
    if (l == NULL || index < 1) return -1;
    node_t *cur = l->head;
    int i = 1;
    while (cur != NULL) {
        if (i == index) return cur->value;
        cur = cur->next;
        i++;
    }
    return -1;
}

// Return first index (1-based) of value.
int list_get_index_of(list_t *l, elem value) {
    if (l == NULL) return -1;
    node_t *cur = l->head;
    int i = 1;
    while (cur != NULL) {
        if (cur->value == value) return i;
        cur = cur->next;
        i++;
    }
    return -1;
}
