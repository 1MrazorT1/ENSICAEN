
int test_hashtableDestroy_results(){
    int nbOfPairs = 20+rand()%100;
    size_t sizeTable = 5+ rand()%10;
    printf("** Insert %d elements in a hashtable of size %zu and then destroy it.\n",nbOfPairs,sizeTable);
    char key[10];
    HashTable h = hashtableCreate(sizeTable);
    for(int i=0;i<nbOfPairs;i++){
        sprintf(key,"key %d",i);
        hashtableInsertWithoutResizing(&h,key,i);
    }
    hashtableDestroy(&h);

    if(h.numberOfPairs!=0 || h.sizeTable!=0){
        printf("Failed: fields (sizeTable,numberOfPairs) should be (0,0) but are (%zu,%zu).\n",
                h.sizeTable,h.numberOfPairs);
        return 0;
    }
    if(h.table!=NULL){
        printf("Failed: field table should be NULL but is %p.\n",h.table);
        return 0;
    }
    printf("Passed!\n");
    return 1;
}

int test_hashtableDestroy_vg(){
    int score=valgrind_test("hashtableDestroy","","Memory test for hashtableDestroy");
    return score;
}

int test_hashtableDestroy(){
    printf("-----------------------------------\n");
    printf("Unit tests for hashtableDestroy \n");
    printf("-------------------------------------\n");

    int score = test_hashtableDestroy_results();
    score+=test_hashtableDestroy_vg();
    return score;
}
