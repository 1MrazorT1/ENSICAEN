#ifndef LINKED_QUEUE_H_
#define LINKED_QUEUE_H_

#include <stdlib.h>
#include "../list/list.h"


/**
 * @brief A queue structure based on a linked list.
 *
 */
typedef struct queue {
    Cell* front; /** A pointer to the front (first) element in the queue. */
    Cell* rear; /** A pointer to the rear (last) element in the queue. */
} Queue;

/**
 * @brief Creates a new, empty queue.
 *
 * @return A pointer to the newly created queue.
 */
Queue* createQueue();

/**
 * @brief Prints all the elements in the queue, from front to rear.
 *
 * @param q The queue to print.
 */
void queuePrint(Queue q);

/**
 * @brief Adds an element to the rear of the queue.
 *
 * @param q A pointer to the queue to add the element to.
 * @param data The data to be added to the queue.
 */
void enqueue(Queue* q, int data);

/**
 * @brief Removes and returns the front element of the queue.
 *
 * @param q A pointer to the queue to remove the front element from.
 * @return The data stored in the front element of the queue.
 */
int dequeue(Queue* q);

/**
 * @brief Checks whether the queue is empty.
 *
 * @param q The queue to check.
 * @return 1 if the queue is empty, 0 otherwise.
 */
int isQueueEmpty(Queue q);

/**
 * @brief Returns the value of the front node but doesn't modify the queue
 *
 * @param q The queue to get the front value.
 * @return The value of the front node.
 */
int queueGetFrontValue(Queue q);

#endif /* LINKED_QUEUE_H_ */
