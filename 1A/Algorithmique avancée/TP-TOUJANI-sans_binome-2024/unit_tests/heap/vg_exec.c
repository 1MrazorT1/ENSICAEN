#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#include "../../heap/heap.h"

#include "valgrind_tests.c"
#include "unit_test_createHeap.c"
#include "unit_test_getElement.c"
#include "unit_test_insertHeap.c"
#include "unit_test_modifyPriorityHeap.c"
#include "unit_test_removeElement.c"
#include "unit_test_largeHeap.c"

int main(int argc, char* argv[]){
    srand(time(NULL));

    if(argc<2)
        return -1;
    if(strcmp(argv[1],"createHeap") ==0){
        test_createHeap_results();
    }
    if(strcmp(argv[1],"getElement") ==0){
        test_getElement_results();
    }
    if(strcmp(argv[1],"insertHeap") ==0){
        test_insertHeap_results();
    }
    if(strcmp(argv[1],"modifyPriorityHeap") ==0){
        test_modifyPriorityHeap_results();
    }
    if(strcmp(argv[1],"removeElement") ==0){
        test_removeElement_results();
    }
    if(strcmp(argv[1],"largeHeap") ==0){
        test_largeHeap_results();
    }

    return EXIT_SUCCESS;
}
