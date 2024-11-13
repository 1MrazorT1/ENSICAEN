/**
 * @file heap.h
 * @brief This header file defines the Heap data structure and provides
 *        functions for creating, modifying, and removing elements from the heap.
 */

/**
 * @struct Heap
 * @brief The Heap data structure that represents a priority queue.
 * @var Heap::n
 * The maximum number of elements that the heap can store.
 * @var Heap::nbElements
 * The current number of elements in the heap.
 * @var Heap::position
 * An array that stores the positions of the elements in the heap.
 * @var Heap::heap
 * An array used to implement the heap.
 * @var Heap::priority
 * An array that stores the priority of each element used to insert the elements in the heap.
 */

 typedef struct sheap{
    int n; //maximal number of elements
    int nbElements; //number of elements in the heap
    int *position; //array of the positions of the elements in the heap
    int *heap; //array used to implement the heap
    double *priority; //priority of each element used to insert the elements in the heap
} Heap;

/**
 * @brief Creates a new empty Heap data structure.
 * @param n The maximum number of elements that the heap can store.
 * @return A pointer to the newly created Heap data structure.
 */
Heap* createHeap(int n);

/**
 * @brief Prints the elements in the Heap data structure.
 * @param h The Heap data structure to print.
 */
void printHeap(Heap *h);

/**
 * @brief Gets the element with the smallest priority (smallest value in the priority array) from the Heap data structure.
 * @param h The Heap data structure to get the element from.
 * @return The element with the smallest priority (smallest value in the priority array).
 */
int getElement(Heap h);

/**
 * @brief Inserts a new element into the Heap data structure with the given priority.
 * @param h A pointer to the Heap data structure to insert the element into.
 * @param element The element to insert.
 * @param priority The priority of the element to insert.
 */
void insertHeap(Heap *h, int element, double priority);

/**
 * @brief Modifies the priority of an element in the Heap data structure.
 * @param h A pointer to the Heap data structure to modify.
 * @param element The element to modify the priority of.
 * @param priority The new priority of the element.
 */
void modifyPriorityHeap(Heap *h, int element, double priority);

/**
 * @brief Removes the element with the smallest priority (smallest value in the priority array) from the Heap data structure.
 * @param h A pointer to the Heap data structure to remove the element from.
 * @return The element with the smallest priority (smallest value in the priority array) that was removed from the Heap data structure.
 */
int removeElement(Heap *h);
