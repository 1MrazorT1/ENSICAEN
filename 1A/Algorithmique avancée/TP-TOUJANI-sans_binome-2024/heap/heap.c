#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

/**
 * @brief Helper function to swap two elements in the heap.
 * @param h A pointer to the Heap data structure.
 * @param i The index of the first element.
 * @param j The index of the second element.
 */
void swap(Heap *h, int i, int j) {
    int temp = h->heap[i];
    h->heap[i] = h->heap[j];
    h->heap[j] = temp;

    temp = h->position[h->heap[i]];
    h->position[h->heap[i]] = h->position[h->heap[j]];
    h->position[h->heap[j]] = temp;
}


/**
 * @brief Creates a new Heap data structure.
 * @param n The maximum number of elements that the heap can store.
 * @return A pointer to the newly created Heap data structure.
 * The elements of the arrays position and priority are initialized to -1
 */
Heap* createHeap(int n) {
    Heap* heap;
    heap=malloc(sizeof(*heap));
    heap->n=n;
    heap->nbElements=0;
    heap->position=malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        heap->position[i]=-1;
    }
    heap->priority=malloc(sizeof(double)*n);
    for(int i=0;i<n;i++){
        heap->priority[i]=-1.00;
    }
    heap->heap=malloc(sizeof(int)*n);
    return heap;
}

/**
 * @brief Prints the elements in the Heap data structure.
 * @param h The Heap data structure to print.
 */
void printHeap(Heap *h) {
    printf("\n");
    if(h==NULL){
        return;
    }
    printf("n: %d\n", h->n);
    printf("nbElements: %d\n", h->nbElements);
    printf("position: [");
    for(int i=0;i<h->n;i++){
        printf("%d ",h->position[i]);
    }
    printf("]\n");
    printf("priority: [");
    for(int i=0;i<h->n;i++){
        printf("%f ",h->priority[i]);
    }
    printf("]\n");
    printf("heap: [");
    for(int i=0;i<h->nbElements;i++){
        printf("%d ",h->heap[i]);
    }
    printf("]\n");
    return;
}

/**
 * @brief Gets the element with the smallest priority (smallest value in the priority array) from the Heap data structure.
 * @param h The Heap data structure to get the element from.
 * @return The element with the smallest priority.
 */
int getElement(Heap h) {
    return h.heap[0];
}

/**
 * @brief Inserts a new element into the Heap data structure with the given priority.
 * @param h A pointer to the Heap data structure to insert the element into.
 * @param element The element to insert.
 * @param priority The priority of the element to insert.
 */
void insertHeap(Heap *h, int element, double priority) {
    h->nbElements=h->nbElements+1;
    h->position=malloc((sizeof(h->position)+1)*sizeof(int));
    h->heap=malloc((sizeof(h->heap)+1)*sizeof(int));
    h->priority=malloc((sizeof(h->priority)+1)*sizeof(double));
    h->heap[sizeof(h->heap)-1]=element;
    h->priority[sizeof(h->priority)-1]=priority;
    return;
}

/**
 * @brief Modifies the priority of an element in the Heap data structure.
 * @param h A pointer to the Heap data structure to modify.
 * @param element The element whose priority is to be modified.
 * @param priority The new priority of the element.
 */
void modifyPriorityHeap(Heap *h, int element, double priority) {
    int i=0;
    while(h->heap[i]!=element){
        i=i+1;
    }
    if(h->heap[i]==element){
        h->priority[i]=priority;
    }
    return;
}


/**
 * @brief Removes the element with the smallest priority (smallest value in the priority array) from the Heap data structure.
 * @param h A pointer to the Heap data structure to remove the element from.
 * @return The element with the smallest priority that was removed from the Heap data structure.
 */
int removeElement(Heap *h) {
    for(int i=0;i<h->n-2;i++){
        h->heap[i]=h->heap[i+1];
        h->position[i]=h->position[i+1];
        h->priority[i]=h->priority[i+1];
    }
    h->nbElements=h->nbElements-1;
    return 0;
}