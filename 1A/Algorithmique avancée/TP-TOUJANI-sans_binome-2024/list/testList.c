/**
 * @file testList.c
 * @brief Test program for the linked list data structure
 *
 * This file contains a program that tests the linked list data structure
 * and its associated functions.
 *
 * @author Loïck Lhote
 * @date February 2023
 */

#include <stdio.h>
#include "list.h"

int main() {
    List L;
    Cell *c;
    L = newList();
    printf("Is the list NULL (0=NO, 1=YES)? %d\n", L==NULL);
    printf("Print empty list:");
    printList(L,0); printf("\n");printList(L,1);
    printf("\nTest findKeyList with empty list:\n");
    c = findKeyInList(L, "two");
    if (c != NULL) {
        printf("Found key %s with value %d\n", c->key, c->value);
    } else {
        printf("Key %s not found\n","two");
    }
    printf("\nTest delKeyInList with empty list:\n");
    L = delKeyInList(L, "two");
    printf("Print empty list after deletion:"); printList(L,1);

    printf("\nTest add function:\n");
    L = addKeyValueInList(L, "one", 1);
    printList(L,0); printf("\n");
    printList(L,1); printf("\n");
    L = addKeyValueInList(L, "two", 2);
    printList(L,0); printf("\n");
    printList(L,1); printf("\n");
    L = addKeyValueInList(L, "three", 3);
    printList(L,0); printf("\n");
    printList(L,1); printf("\n");
    L = addKeyValueInList(L, NULL, 0);
    printList(L,0); printf("\n");
    printList(L,1); printf("\n");
    L = addKeyValueInList(L, "four", 4);
    printList(L,0); printf("\n");
    printList(L,1); printf("\n");
    c = findKeyInList(L, "two");
    if (c != NULL) {
        printf("Found key %s with value %d\n", c->key, c->value);
    } else {
        printf("Key %s not found\n","two");
    }
    c = findKeyInList(L, "twelve");
    if (c != NULL) {
        printf("Found key %s with value %d\n", c->key, c->value);
    } else {
        printf("Key %s not found\n","twelve");
    }
    c = findKeyInList(L, NULL);
    if (c != NULL) {
        printf("Found key %s with value %d\n", c->key, c->value);
    } else {
        printf("Key %s not found\n","NULL");
    }

    printf("Test delete function:");
    L = delKeyInList(L, NULL);
    printf("NULL: ");printList(L,1);printf("\n");
    printf("Test delete function:");
    L = delKeyInList(L, "two");
    printf("two: ");printList(L,1);printf("\n");
    L = delKeyInList(L, "five");
    printf("five: ");printList(L,1);printf("\n");
    L = delKeyInList(L, "four");
    printf("four: ");printList(L,1);printf("\n");
    L = delKeyInList(L, "one");
    printf("one: ");printList(L,1);printf("\n");
    L = delKeyInList(L, "three");
    printf("three: ");printList(L,1);printf("\n");
    L = delKeyInList(L, "three");
    printf("three: ");printList(L,1);printf("\n");


    freeList(L);
    return 0;
}
