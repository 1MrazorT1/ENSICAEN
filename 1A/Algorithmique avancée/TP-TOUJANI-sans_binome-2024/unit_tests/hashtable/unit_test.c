#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#include "../../hashtable/hashtable.h"
#include "../../list/list.h"

#include "valgrind_tests.c"
#include "unit_test_hashtableCreate.c"
#include "unit_test_hashtableInsertWithoutResizing.c"
#include "unit_test_hashtableDestroy.c"
#include "unit_test_hashtableDoubleSize.c"
#include "unit_test_hashtableInsert.c"
#include "unit_test_hashtableHasKey.c"
#include "unit_test_hashtableGetValue.c"
#include "unit_test_hashtableRemove.c"



int main() {
    srand(time(NULL));

    system("clear");
    system("rm -f score.log");
    int score1 = 0;
    int score2 = 0;
    int score3 = 0;
    int score4 = 0;
    int score5 = 0;
    int score6 = 0;
    int score7 = 0;
    int score8 = 0;

    printf("------------------------------------------------------\n");
    printf("Unit test for HashTable \n");
    printf("WARNING: Unit tests for list must be satisfied !!!!!! \n");
    printf("------------------------------------------------------\n");

    score1 = test_hashtableCreate();
    if(score1==3)
        score2 = test_hashtableInsertWithoutResizing();
    if(score2==3)
        score3 = test_hashtableDestroy();
    if(score3==2)
        score4 = test_hashtableDoubleSize();
    if(score4==3)
        score5 = test_hashtableInsert();
    if(score5==3)
        score6 = test_hashtableHasKey();
    if(score6==2)
        score7 = test_hashtableGetValue();
    if(score7==2)
        score8 = test_hashtableRemove();

    system("rm -f output.txt");
    printf("-----------------------------------\n");
    printf("Summary of the unit tests \n");
    printf("-------------------------------------\n");
    printf("Summary: %d passed tests over 3 tests for hashtableCreate().\n",score1);
    printf("Summary: %d passed tests over 3 tests for hashtableInsertWithoutResizing().\n",score2);
    printf("Summary: %d passed tests over 2 tests for hashtableDestroy().\n",score3);
    printf("Summary: %d passed tests over 3 tests for hashtableDoubleSize().\n",score4);
    printf("Summary: %d passed tests over 3 tests for hashtableInsert().\n",score5);
    printf("Summary: %d passed tests over 2 tests for hashtableHasKey().\n",score6);
    printf("Summary: %d passed tests over 2 tests for hashtableGetValue().\n",score7);
    printf("Summary: %d passed tests over 2 tests for hashtableRemove().\n",score8);


    return 0;
}
