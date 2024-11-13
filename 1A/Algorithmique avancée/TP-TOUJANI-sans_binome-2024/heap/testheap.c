#include <stdio.h>
#include "heap.h"

int main() {
    Heap *heap = createHeap(5);
    
    
    printf("Current heap: ");
    printHeap(heap);
    

    insertHeap(heap, 1, 5.0);
    printf("Current heap: ");
    printHeap(*heap);

    insertHeap(heap, 2, 2.0);
    printf("Current heap: ");
    printHeap(*heap);

    insertHeap(heap, 3, 4.0);
    printf("Current heap: ");
    printHeap(*heap);

    insertHeap(heap, 4, 1.0);
    printf("Current heap: ");
    printHeap(*heap);

    insertHeap(heap, 0, 3.0);
    printf("Current heap: ");
    printHeap(*heap);
    

    /*printf("Element with lowest priority: %d\n", getElement(*heap));

    
    modifyPriorityHeap(heap, 4, 3.5);
    printf("Heap after modifying priority of element 4: ");
    printHeap(*heap);
    

    
    int removedElement = removeElement(heap);
    printf("Heap after removing element with lowest priority: ");
    printHeap(*heap);
    printf("Removed element: %d\n", removedElement);
    */
    return 0;
}
