#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int test_modifyPriorityHeap_results(){
    int score = 0;
    int compare;

    // Creating heaps
    int n=10;
    Heap solution, heap;
    solution.n = n;
    heap.n = n;
    solution.nbElements = n;
    heap.nbElements=n;
    solution.position = (int*)malloc(sizeof(int) * n);
    solution.heap = (int*)malloc(sizeof(int) * n);
    solution.priority = (double*)malloc(sizeof(double) * n);
    heap.position = (int*)malloc(sizeof(int) * n);
    heap.heap = (int*)malloc(sizeof(int) * n);
    heap.priority = (double*)malloc(sizeof(double) * n);
    for(int i=0;i<n;i++){
        solution.position[i]=i;
        heap.position[i]=i;
        solution.priority[i]=i;
        heap.priority[i]=i;
        solution.heap[i]=i;
        heap.heap[i]=i;
    }


    printf("** Decrease the priority of the root: should not change the heap (except the priority).\n");
    modifyPriorityHeap(&heap,0,-0.5);
    solution.priority[0] = -0.5;
    compare = compareHeap(heap,solution);
    if(compare==0){
        printf("Test Case Failed: one field in the heap is not updated conveniently.\n");
        printf("Fix the bug before continuing.\n");
        return score;
    }
    printf("Passed.\n");
    score++;

    printf("** Increase the priority of the root without impact on the heap (except the priority).\n");
    modifyPriorityHeap(&heap,0,0);
    solution.priority[0] = 0;
    compare = compareHeap(heap,solution);
    if(compare==0){
        printf("Test Case Failed: one field in the heap is not updated conveniently.\n");
        printf("Fix the bug before continuing.\n");
        return score;
    }
    printf("Passed.\n");
    score++;

    printf("** Increase the priority of a node with an impact on the heap.\n");
    modifyPriorityHeap(&heap,1,10);
    solution.priority[1] = 10;
    myswap(&solution,1,3);
    myswap(&solution,3,7);
    compare = compareHeap(heap,solution);
    if(compare==0){
        printf("Test Case Failed: one field in the heap is not updated conveniently.\n");
        printf("Fix the bug before continuing.\n");
        return score;
    }
    printf("Passed.\n");
    score++;

    printf("** Increase the priority of a node with an impact on the heap.\n");
    modifyPriorityHeap(&heap,7,8.5);
    solution.priority[7] = 8.5;
    myswap(&solution,8,3);
    compare = compareHeap(heap,solution);
    if(compare==0){
        printf("Test Case Failed: one field in the heap is not updated conveniently.\n");
        printf("Fix the bug before continuing.\n");
        return score;
    }
    printf("Passed.\n");
    score++;


    printf("** Decrease the priority of a node with an impact on the heap.\n");

    modifyPriorityHeap(&heap,9,-0.5);
    solution.priority[9] = -0.5;
    myswap(&solution,9,4);
    myswap(&solution,4,1);
    myswap(&solution,0,1);
    compare = compareHeap(heap,solution);
    if(compare==0){
        printf("Test Case Failed: one field in the heap is not updated conveniently.\n");
        printf("Fix the bug before continuing.\n");

        return score;
    }
    printf("Passed.\n");
    score++;


    free(solution.position);
    solution.position = NULL;
    free(solution.heap);
    solution.heap=NULL;
    free(solution.priority);
    solution.priority=NULL;

    free(heap.position);
    heap.position = NULL;
    free(heap.heap);
    heap.heap=NULL;
    free(heap.priority);
    heap.priority=NULL;



    return score;
}

int test_modifyPriorityHeap_vg(){
    int score=valgrind_test("modifyPriorityHeap","","Memory test for modifyPriorityHeap");
    return score;
}


int test_modifyPriorityHeap() {

    int score = 0;
    printf("-----------------------------------\n");
    printf("Unit tests for modifyPriorityHeap \n");
    printf("-------------------------------------\n");
    score+= test_modifyPriorityHeap_results();
    score+= test_modifyPriorityHeap_vg();
    return score;
}
