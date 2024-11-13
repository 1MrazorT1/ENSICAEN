#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//duplicate : TODO: add swap in heap.h file
void myswap(Heap *h, int i, int j) {
    int temp = h->heap[i];
    h->heap[i] = h->heap[j];
    h->heap[j] = temp;

    temp = h->position[h->heap[i]];
    h->position[h->heap[i]] = h->position[h->heap[j]];
    h->position[h->heap[j]] = temp;
}



int compareHeap(Heap h1, Heap h2){
    if(h1.n != h2.n){
        printf("Field n different from %d.\n",h2.n);
        return 0;
    }
    if(h1.nbElements != h2.nbElements){
        printf("Field nbElements different from %d.\n",h2.nbElements);
         return 0;
    }
    for(int i=0;i<h1.n;i++){
        if(h1.position[i] != h2.position[i]){
            printf("Element position[%d] different from %d.\n",i,h2.position[i]);
            return 0;
        }
        if(h1.position[i]!=-1){
            int posi = h1.position[i];
            if(h1.heap[posi] != h2.heap[posi]){
                printf("Element heap[%d] different from %d.\n",posi,h2.heap[posi]);
                return 0;
            }
            if(h1.priority[i] != h2.priority[i]){
                printf("Element priority[%d] different from %lf.\n",i,h2.priority[i]);
                return 0;
            }
        }
    }
    return 1;

}

int test_insertHeap_results(){
    int score = 0;
    int compare;

    // Creating heaps
    int n=10;
    Heap solution;
    solution.n = n;
    solution.nbElements = 0;
    solution.position = (int*)malloc(sizeof(int) * n);
    solution.heap = (int*)malloc(sizeof(int) * n);
    solution.priority = (double*)malloc(sizeof(double) * n);
    for(int i=0;i<n;i++){
        solution.position[i]=-1;
    }

    Heap heap;
    heap.n = n;
    heap.nbElements = 0;
    heap.position = (int*)malloc(sizeof(int) * heap.n);
    heap.heap = (int*)malloc(sizeof(int) * heap.n);
    heap.priority = (double*)malloc(sizeof(double) * heap.n);
    for(int i=0;i<heap.n;i++){
        heap.position[i]=-1;
    }

    printf("** Inserting a first element: value %d with priority %.2lf\n",1,0.5);
    insertHeap(&heap,1,0.5);
    solution.nbElements = 1;
    solution.position[1] = 0 ;
    solution.heap[0] = 1;
    solution.priority[1] = 0.5;
    compare = compareHeap(heap,solution);
    if(compare==0){
        printf("Test Case Failed: one field in the heap is not updated conveniently.\n");
        printf("Fix the bug before continuing.\n");
        return score;
    }
    printf("Passed.\n");
    score++;

    printf("** Inserting new element: value %d with priority %.2lf\n",5,1.);
    insertHeap(&heap,5,1);
    solution.nbElements = 2;
    solution.position[5] = 1 ;
    solution.heap[1] = 5;
    solution.priority[5] = 1;
    compare = compareHeap(heap,solution);
    if(compare==0){
        printf("Test Case Failed: one field in the heap is not updated conveniently.\n");
        printf("Fix the bug before continuing.");
        return score;
    }
    printf("Passed.\n");
    score++;

    printf("** Inserting new element: value %d with priority %.2lf\n",3,0.4);
    insertHeap(&heap,3,0.4);
    solution.nbElements = 3;
    solution.position[3] = 2 ;
    solution.heap[2] = 3;
    solution.priority[3] = 0.4;
    myswap(&solution,0,2);
    compare = compareHeap(heap,solution);
    if(compare==0){
        printf("Test Case Failed: one field in the heap is not updated conveniently.\n");
        printf("Fix the bug before continuing.");
        return score;
    }
    printf("Passed.\n");
    score++;

    printf("** Inserting new element: value %d with priority %.2lf\n",0,0.6);
    insertHeap(&heap,0,0.6);
    solution.nbElements = 4;
    solution.position[0] = 3 ;
    solution.heap[3] = 0;
    solution.priority[0] = 0.6;
    myswap(&solution,1,3);
    compare = compareHeap(heap,solution);
    if(compare==0){
        printf("Test Case Failed: one field in the heap is not updated conveniently.\n");
        printf("Fix the bug before continuing.");
        return score;
    }
    printf("Passed.\n");
    score++;

    printf("** Inserting new element: value %d with priority %.2lf\n",7,0.3);
    insertHeap(&heap,7,0.3);
    solution.nbElements = 5;
    solution.position[7] = 4;
    solution.heap[4] = 7;
    solution.priority[7] = 0.3;
    myswap(&solution,1,4);
    myswap(&solution,1,0);
    compare = compareHeap(heap,solution);
    if(compare==0){
        printf("Test Case Failed: one field in the heap is not updated conveniently.\n");
        printf("Fix the bug before continuing.");
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

int test_insertHeap_vg(){
    int score=valgrind_test("insertHeap","","Memory test for insertHeap");
    return score;
}


int test_insertHeap() {

    int score = 0;
    printf("-----------------------------------\n");
    printf("Unit tests for insertHeap \n");
    printf("-------------------------------------\n");
    score+= test_insertHeap_results();
    score+= test_insertHeap_vg();
    return score;
}
