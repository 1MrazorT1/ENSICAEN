#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


int test_getElement_results(){
    int score = 0;

    // Creating heap
    Heap heap;
    heap.n = 5;
    heap.nbElements = 3;
    heap.position = (int*)malloc(sizeof(int) * 5);
    heap.heap = (int*)malloc(sizeof(int) * 5);
    heap.priority = (double*)malloc(sizeof(double) * 5);

    // Setting up heap elements
    heap.position[0] = 0;
    heap.position[1] = 1;
    heap.position[2] = 2;
    heap.heap[0] = 0;
    heap.heap[1] = 1;
    heap.heap[2] = 2;
    heap.priority[0] = 0.1; // Highest priority value
    heap.priority[1] = 0.5;
    heap.priority[2] = 0.3;

    printf("** Get the element with highest priority \n");

    // Getting the element with the highest priority
    int element = getElement(heap);

    // Testing the result
    if (element == 0) {
        printf("Test Case Passed: Correct element with highest priority returned!\n");
        score++;
    } else {
        printf("Test Case Failed: Incorrect element returned!\n");
    }
    free(heap.position);
    heap.position = NULL;
    free(heap.heap);
    heap.heap=NULL;
    free(heap.priority);
    heap.priority=NULL;
    return score;
}

int test_getElement_vg(){
    int score=valgrind_test("getElement","","Memory test for getElement");
    return score;
}


int test_getElement() {

    int score = 0;
    printf("-----------------------------------\n");
    printf("Unit tests for getElement \n");
    printf("-------------------------------------\n");
    score+= test_getElement_results();
    score+= test_getElement_vg();
    return score;
}
