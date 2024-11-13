#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>



int test_createHeap_results(){
    int score = 0;
    printf("** Creating a heap with a negative capacity\n");
    Heap* heap = createHeap(-5);
    if (heap == NULL) {
        printf("Passed: Heap creation with a negative capacity failed as expected!\n");
        score++;
    } else {
        printf("Failed: Heap with a negative capacity created unexpectedly! The function should return NULL.\n");
    }

    printf("** Creating a heap with a capacity of 0\n");
    heap = createHeap(0);
    if (heap == NULL) {
        printf("Passed: Heap creation with a null capacity failed as expected!\n");
        score++;
    } else {
        printf("Failed: Heap with a null capacity created unexpectedly! The function should return NULL.\n");
    }


    printf("** Creating a heap with a positive capacity\n");
    int fail = 0;
    int n = 10;
    heap = createHeap(n);
    if (heap == NULL){
            fail = 1;
            printf("Failed: Heap cration failed (null pointer returned).\n");
    }
    if (heap->n != n){
            fail = 1;
            printf("Failed: field n in heap not initialized to the convenient value.\n");
    }
    if (heap->nbElements != 0){
            fail = 1;
            printf("Failed: field nbElements in heap not initialized to the convenient value 0.\n");
    }
    if (heap->position == NULL){
            fail = 1;
            printf("Failed: array position in heap has null value.\n");
    }
    for(int i=0;i<n;i++)
        if(heap->position[i] != -1){
            fail = 1;
            printf("Failed: elements in array position in heap are not set to -1;.\n");
            break;
        }
    free(heap->position); heap->position=NULL;
    free(heap->priority); heap->priority=NULL;
    free(heap->heap); heap->heap = NULL;
    free(heap);
    heap=NULL;

    if(fail){
        return score;
    }
    printf("Passed: Heap creation with a positive capacity!\n");
    score++;
    return score;
}

int test_createHeap_vg(){
    int score=valgrind_test("createHeap","","Memory test for createHeap");
    return score;
}


int test_createHeap() {

    int score = 0;
    printf("-----------------------------------\n");
    printf("Unit tests for createHeap \n");
    printf("-------------------------------------\n");
    score+= test_createHeap_results();
    score+= test_createHeap_vg();
    return score;
}
