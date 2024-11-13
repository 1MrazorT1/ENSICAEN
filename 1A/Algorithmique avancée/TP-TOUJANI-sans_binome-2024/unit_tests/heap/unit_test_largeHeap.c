#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>



int test_largeHeap_results(){
    int score = 0;

    // Creating heaps
    int n=1000;
    Heap  heap;
    heap.n = n;
    heap.nbElements=0;
    heap.position = (int*)malloc(sizeof(int) * n);
    heap.heap = (int*)malloc(sizeof(int) * n);
    heap.priority = (double*)malloc(sizeof(double) * n);
    for(int i=0;i<n;i++){
        heap.position[i]=-1;
        heap.priority[i]=-1;
        heap.heap[i]=-1;
    }


    printf("** add %d elements with random priority in heap.\n",n);
    for(int i=0;i<n;i++){
        insertHeap(&heap,i,(double) rand()/RAND_MAX);
        if(isHeap(heap)==0){
            printf("Failed: heap structure is no more a heap after %d calls to insertHeap.\n",i);
            printf("Fix the bug before continuing.\n");
            return score;
        }
    }
    score++;
    printf("Passed.\n");
    printf("** Modify randomly the priority of the %d elements in the heap.\n",n);
    for(int i=0;i<n;i++){
        modifyPriorityHeap(&heap,i,(double) rand()/RAND_MAX);
        if(isHeap(heap)==0){
            printf("Failed: heap structure is no more a heap after %d calls to modifyPriorityHeap.\n",i);
            printf("Fix the bug before continuing.\n");
            return score;
        }
    }
    score++;
    printf("Passed.\n");
    printf("** Remove the %d elements in the heap.\n",n);
    for(int i=0;i<n;i++){
        removeElement(&heap);
        if(isHeap(heap)==0){
            printf("Failed: heap structure is no more a heap after %d calls to removeElement.\n",i);
            printf("Fix the bug before continuing.\n");
            return score;
        }
    }
    score++;
    printf("Passed.\n");

    free(heap.position);
    heap.position = NULL;
    free(heap.heap);
    heap.heap=NULL;
    free(heap.priority);
    heap.priority=NULL;


    return score;
}

int test_largeHeap_vg(){
    int score=valgrind_test("largeHeap","","Memory test with a large heap data structure");
    return score;
}


int test_largeHeap() {

    int score = 0;
    printf("---------------------------------------------\n");
    printf("Unit tests with a large Heap datat structure \n");
    printf("---------------------------------------------\n");
    score+= test_largeHeap_results();
    score+= test_largeHeap_vg();
    return score;
}
