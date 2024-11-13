

int test_hashtableDoubleSize_main_function(size_t size, size_t nbElements){
    printf("** Double size of a hashtable of size %zu containing %zu elements.\n",size,nbElements);
    char key[20];
    HashTable h = hashtableCreate(size);
    for(size_t i=0;i<nbElements;i++){
        sprintf(key,"key %zu",i);
        hashtableInsertWithoutResizing(&h,key,i);
    }
    HashTable newh = hashtableDoubleSize(h);

    if(newh.sizeTable != 2*size){
        printf("Failed : the size of the new hashtable should be %zu but is %zu.\n",2*size,newh.sizeTable);
        return 0;
    }
    if(newh.numberOfPairs != nbElements){
        printf("Failed : the field numberOfPairs in the new hashtable should be %zu but is %zu.\n",nbElements, newh.numberOfPairs);
        return 0;
    }
    size_t counter=0;
    for(size_t i =0; i<newh.sizeTable;i++){
        Cell *list = newh.table[i];
        while(list!=NULL){
            counter++;
            list=list->nextCell;
        }
    }
    if(newh.numberOfPairs != counter){
        printf("Failed : the number of pairs in the new hashtable (%zu) is different from the field numberOfPairs (%zu).\n",counter, newh.numberOfPairs);
        return 0;
    }

    for(size_t i=0;i<nbElements;i++){
        sprintf(key,"key %zu",i);
        size_t hashkey = murmurhash(key,strlen(key),newh.sizeTable);
        Cell *cell = findKeyInList(newh.table[hashkey],key);
        if(cell ==NULL || cell->value!=(int) i){
            printf("Failed : table[%zu of the hashtable is not the expected list.\n",hashkey);
            printf("Couple (%s,%zu) not in the list table[%zu]\n",key,i,hashkey);
            return 0;
        }
    }


    printf("Passed.\n");
    hashtableDestroy(&h);
    hashtableDestroy(&newh);
    return 1;

}


int test_hashtableDoubleSize_results(){
    int score = test_hashtableDoubleSize_main_function(8,  10);
    score += test_hashtableDoubleSize_main_function(100, 200);
    return score;

}


int test_hashtableDoubleSize_vg(){
    int score=valgrind_test("hashtableDoubleSize","","Memory test for hashtableDoubleSize");
    return score;
}

int test_hashtableDoubleSize(){
    printf("----------------------------------------------\n");
    printf("Unit tests for test_hashtableDoubleSize \n");
    printf("----------------------------------------------\n");

    int score = test_hashtableDoubleSize_results();
    score+=test_hashtableDoubleSize_vg();
    return score;
}
