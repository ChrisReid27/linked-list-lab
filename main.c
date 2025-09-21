#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main() {
    printf("--- List Allocate Test ---\n");
    list_t *mylist = list_alloc();
    if (mylist != NULL && mylist->head == NULL) {
        printf("List Allocate Test: PASS\n");
    } else {
        printf("List Allocate Test: FAILED\n");
    }
    list_print(mylist);
    printf("---------------------------\n\n");

    printf("--- List Add_to_front Tests ---\n");
    list_add_to_front(mylist, 10);
    list_add_to_front(mylist, 20);
    list_add_to_front(mylist, 30);
    char *s = listToString(mylist);
    if (strcmp(s, "30->20->10->NULL") == 0) {
        printf("List Add_to_front Test: PASS\n");
    } else {
        printf("List Add_to_front Test: FAILED\n");
    }
    free(s);
    list_print(mylist);
    printf("---------------------------\n\n");

    printf("--- List Add_to_back Tests ---\n");
    list_t *back_list = list_alloc();
    list_add_to_back(back_list, 10);
    list_add_to_back(back_list, 20);
    list_add_to_back(back_list, 30);
    s = listToString(back_list);
    if (strcmp(s, "10->20->30->NULL") == 0) {
        printf("List Add_to_back Test: PASS\n");
    } else {
        printf("List Add_to_back Test: FAILED\n");
    }
    free(s);
    list_print(back_list);
    printf("---------------------------\n\n");

    printf("--- List Add_at_index Tests ---\n");
    list_add_at_index(back_list, 15, 2); // Insert 15 at index 2
    s = listToString(back_list);
    if (strcmp(s, "10->15->20->30->NULL") == 0) {
        printf("List Add_at_index (valid index) Test: PASS\n");
    } else {
        printf("List Add_at_index (valid index) Test: FAILED\n");
    }
    free(s);
    list_add_at_index(back_list, 5, 1); // Insert 5 at index 1
    s = listToString(back_list);
    if (strcmp(s, "5->10->15->20->30->NULL") == 0) {
        printf("List Add_at_index (index 1) Test: PASS\n");
    } else {
        printf("List Add_at_index (index 1) Test: FAILED\n");
    }
    free(s);
    list_add_at_index(back_list, 100, 10); // Insert 100 at out-of-bounds index
    s = listToString(back_list);
    if (strcmp(s, "5->10->15->20->30->100->NULL") == 0) {
        printf("List Add_at_index (out of bounds) Test: PASS\n");
    } else {
        printf("List Add_at_index (out of bounds) Test: FAILED\n");
    }
    free(s);
    list_print(back_list);
    printf("---------------------------\n\n");

    printf("--- List Remove_from_front Tests ---\n");
    elem removed_front = list_remove_from_front(mylist);
    s = listToString(mylist);
    if (strcmp(s, "20->10->NULL") == 0 && removed_front == 30) {
        printf("List Remove_from_front Test: PASS\n");
    } else {
        printf("List Remove_from_front Test: FAILED\n");
    }
    free(s);
    list_print(mylist);
    printf("---------------------------\n\n");

    printf("--- List Remove_from_back Tests ---\n");
    elem removed_back = list_remove_from_back(mylist);
    s = listToString(mylist);
    if (strcmp(s, "20->NULL") == 0 && removed_back == 10) {
        printf("List Remove_from_back Test: PASS\n");
    } else {
        printf("List Remove_from_back Test: FAILED\n");
    }
    free(s);
    list_print(mylist);
    printf("---------------------------\n\n");

    printf("--- List Remove_at_index Tests ---\n");
    list_t *remove_list = list_alloc();
    list_add_to_back(remove_list, 10);
    list_add_to_back(remove_list, 20);
    list_add_to_back(remove_list, 30);
    list_add_to_back(remove_list, 40);
    list_print(remove_list);
    elem removed_index = list_remove_at_index(remove_list, 2); // Remove 20
    s = listToString(remove_list);
    if (strcmp(s, "10->30->40->NULL") == 0 && removed_index == 20) {
        printf("List Remove_at_index (valid) Test: PASS\n");
    } else {
        printf("List Remove_at_index (valid) Test: FAILED\n");
    }
    free(s);
    list_print(remove_list);
    removed_index = list_remove_at_index(remove_list, 1); // Remove 10
    s = listToString(remove_list);
    if (strcmp(s, "30->40->NULL") == 0 && removed_index == 10) {
        printf("List Remove_at_index (index 1) Test: PASS\n");
    } else {
        printf("List Remove_at_index (index 1) Test: FAILED\n");
    }
    free(s);
    list_print(remove_list);
    removed_index = list_remove_at_index(remove_list, 5); // Remove out of bounds
    s = listToString(remove_list);
    if (strcmp(s, "30->40->NULL") == 0 && removed_index == -1) {
        printf("List Remove_at_index (out of bounds) Test: PASS\n");
    } else {
        printf("List Remove_at_index (out of bounds) Test: FAILED\n");
    }
    free(s);
    list_print(remove_list);
    printf("---------------------------\n\n");

    printf("--- List Deallocation Test ---\n");
    list_free(mylist);
    list_free(back_list);
    list_free(remove_list);
    printf("List Deallocation Test: PASS\n");
    printf("---------------------------\n\n");

    return 0;
}
