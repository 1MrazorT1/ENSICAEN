
int test_hashtableCreate_results(){
    int score = 0;
    HashTable h;


    printf("** Creating a HashTable with sizeTable=0 \n");
    h = hashtableCreate(0);
    if (h.sizeTable==0 && h.numberOfPairs==0 && h.table == NULL) {
        printf("Passed.\n");
        score++;
    } else {
        printf("Failed: fields (sizeTable,numberOfPairs,table) should be (0,0,%p) but are (%zu,%zu,%p).\n",
                NULL, h.sizeTable,h.numberOfPairs,h.table);
    }

    printf("** Creating a HashTable with sizeTable=10 \n");
    h = hashtableCreate(10);
    if (h.sizeTable!=10 || h.numberOfPairs!=0 || h.table == NULL) {
        printf("Failed: fields (sizeTable,numberOfPairs,table) should be (10,0,not NULL) but are (%zu,%zu,%p).\n",
                h.sizeTable,h.numberOfPairs,h.table);
    }
    else {
        int i=0;
        for(i=0;i<10;i++){
            if (h.table[i] != NULL) {
                printf("Failed: the lists in field table are not initialized.\n");
                break;
            }
        }
        if(i==10){
            printf("Passed.\n");
            score++;
        }
    }

    free(h.table); h.table=NULL;
    return score;
}

int test_hashtableCreate_vg(){
    int score=valgrind_test("hashtableCreate","","Memory test for hashtableCreate");
    return score;
}

int test_hashtableCreate(){
    printf("-----------------------------------\n");
    printf("Unit tests for hashtableCreate \n");
    printf("-------------------------------------\n");

    int score = test_hashtableCreate_results();
    score+=test_hashtableCreate_vg();
    return score;
}
