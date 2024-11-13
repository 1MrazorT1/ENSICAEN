#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int isHeap(Heap h){
    if(h.n<=0)
        return 0;
    if(h.nbElements<0 || h.nbElements>h.n)
        return 0;
    int counter = 0;
    for(int i=0;i<h.n;i++){
        if(h.position[i]< -1 || h.position[i]>=h.n)
            return 0;
        if(h.position[i]!=-1){
            counter++;
            if(h.heap[h.position[i]]!=i)
                return 0;
        }
    }
    if(counter != h.nbElements){
        return 0;
    }
    for(int i=h.nbElements-1;i>0;i--){
        if(h.priority[h.heap[i]] < h.priority[h.heap[(i-1)/2]])
            return 0;
    }

    return 1;
}
int test_removeElement_results(){
    int score = 0;
    int value;

    // Creating heaps
    int n=10;
    Heap  heap;
    heap.n = n;
    heap.nbElements=n;
    heap.position = (int*)malloc(sizeof(int) * n);
    heap.heap = (int*)malloc(sizeof(int) * n);
    heap.priority = (double*)malloc(sizeof(double) * n);
    for(int i=0;i<n;i++){
        heap.position[i]=i;
        heap.priority[i]=i;
        heap.heap[i]=i;
    }
    myswap(&heap,1,2);
    myswap(&heap,3,6);
    myswap(&heap,7,9);


    printf("** Removes one by one all the elements of the tested heap.\n");
    printf("Tested heap:");
    printHeap(heap);
    for(int i=0;i<n;i++){
        value = removeElement(&heap);
        if(value!=i){
            printf("Failed: unexpected returned value after %d calls to removeElement.\n",i);
            printf("Fix the bug before continuing.\n");
            return score;
        }
        if(isHeap(heap)==0){
            printf("Failed: heap structure is no more a heap after %d calls to removeElement.\n",i);
            printf("Fix the bug before continuing.\n");
            return score;
        }
    }

    free(heap.position);
    heap.position = NULL;
    free(heap.heap);
    heap.heap=NULL;
    free(heap.priority);
    heap.priority=NULL;

    printf("Passed.\n");
    score++;

    return score;
}

int test_removeElement_vg(){
    int score=valgrind_test("removeElement","","Memory test for removeElement");
    return score;
}


int test_removeElement() {

    int score = 0;
    printf("-----------------------------------\n");
    printf("Unit tests for removeElement \n");
    printf("-------------------------------------\n");
    score+= test_removeElement_results();
    score+= test_removeElement_vg();
    return score;
}
