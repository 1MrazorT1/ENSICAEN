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

int main(int argc, char* argv[]){
    srand(time(NULL));

    if(argc<2)
        return -1;
    if(strcmp(argv[1],"hashtableCreate") ==0){
        test_hashtableCreate_results();
    }
    if(strcmp(argv[1],"hashtableInsertWithoutResizing") ==0){
        test_hashtableInsertWithoutResizing_results();
    }
    if(strcmp(argv[1],"hashtableDestroy") ==0){
        test_hashtableDestroy_results();
    }
    if(strcmp(argv[1],"hashtableDoubleSize") ==0){
        test_hashtableDoubleSize_results();
    }
    if(strcmp(argv[1],"hashtableInsert") ==0){
        test_hashtableInsert_results();
    }
    if(strcmp(argv[1],"hashtableHasKey") ==0){
        test_hashtableHasKey_results();
    }
    if(strcmp(argv[1],"hashtableGetValue") ==0){
        test_hashtableGetValue_results();
    }
    if(strcmp(argv[1],"hashtableRemove") ==0){
        test_hashtableRemove_results();
    }

    return EXIT_SUCCESS;
}
