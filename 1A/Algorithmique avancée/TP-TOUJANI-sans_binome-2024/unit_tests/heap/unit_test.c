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



int main() {
    srand(time(NULL));
    int score1 = 0;
    int score2 = 0;
    int score3 = 0;
    int score4 = 0;
    int score5 = 0;
    int score6 = 0;

    system("clear");
    system("rm -f score.log");
    score1 = test_createHeap();
    score2 = test_getElement();
    score3 = test_insertHeap();
    score4 = test_modifyPriorityHeap();
    score5 = test_removeElement();
    score6 = test_largeHeap();
    system("rm -f output.txt");
    printf("-----------------------------------\n");
    printf("Summary of the unit tests \n");
    printf("-------------------------------------\n");
    printf("Summary: %d passed tests over 4 tests for createHeap().\n",score1);
    printf("Summary: %d passed tests over 2 tests for getElement().\n",score2);
    printf("Summary: %d passed tests over 6 tests for insertHeap().\n",score3);
    printf("Summary: %d passed tests over 6 tests for modifyPriorityHeap().\n",score4);
    printf("Summary: %d passed tests over 2 tests for removeElement().\n",score5);
    printf("Summary: %d passed tests over 4 tests for largeHeap().\n",score6);


    return 0;
}
