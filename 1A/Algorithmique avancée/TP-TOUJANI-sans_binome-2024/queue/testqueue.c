#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main() {
    Queue* q = createQueue();
    //queuePrint(*q);

    // Add elements to the queue
    /*
    printf("\nAdd 1 to queue:\n");
    enqueue(q, 1);
    queuePrint(*q);
    printf("\nAdd 2 to queue:\n");
    enqueue(q, 2);
    queuePrint(*q);
    printf("\nAdd 3 to queue:\n");
    enqueue(q, 3);
    queuePrint(*q);
    */
    // Remove an element from the queue
    /*
    int frontValue = dequeue(q);
    printf("\nDequeued value: %d\n", frontValue);
    // Print the elements in the queue
    printf("Updated queue:\n");
    queuePrint(*q);
    frontValue = dequeue(q);
    printf("\nDequeued value: %d\n", frontValue);
    // Print the elements in the queue
    printf("Updated queue:\n");
    queuePrint(*q);
    */
    // Get the value of the front element without removing it
    /*
    frontValue = queueGetFrontValue(*q);
    printf("\nFront value: %d\n", frontValue);
    */
    /*
    printf("add 4 to queue:\n");
    enqueue(q, 4);
    queuePrint(*q);
    // Check if the queue is empty
    printf("\nIs queue empty? %d\n", isQueueEmpty(*q));
    */

    // Remove all elements from the queue
    /*
    while (!isQueueEmpty(*q)) {
        dequeue(q);
    }

    // Print the elements in the queue
    printf("Final queue:\n");
    queuePrint(*q);

    // Check if the queue is empty
    printf("\nIs queue empty? %d\n", isQueueEmpty(*q));
    */
    free(q);

    return 0;
}
