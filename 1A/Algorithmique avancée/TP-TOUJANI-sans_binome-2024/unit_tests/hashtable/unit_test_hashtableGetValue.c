int test_hashtableGetValue_results(){
    int n = 200+rand()%500;
    int nbKeys = 50;

    printf("** Insert %d random pairs (key,value) in a hashtable of size 1 with possible repetions on the %d different keys and then test the hashtableGetValue function.\n",n,nbKeys);
    int tabValue[nbKeys];
    for(int i=0;i<nbKeys;i++)
        tabValue[i]=-1;
    char key[20];
    HashTable h = hashtableCreate(1);

    size_t nbOfPairs =0;
    for(int i=0;i<n;i++){
        int r = rand()%nbKeys;
        sprintf(key,"key %d",r);
        if(tabValue[r]==-1)
            nbOfPairs++;
        tabValue[r] = rand() % 100;
        hashtableInsert(&h,key,tabValue[r]);
    }

    for(int i=0;i<nbKeys;i++){
        sprintf(key,"key %d",i);
        if(tabValue[i]!=-1){
            if(hashtableGetValue(h,key)!=tabValue[i]){
                printf("Failed: the function does not return the expected value.\n");
                return 0;
            }
        }
    }



    for(size_t i=0;i<h.sizeTable;i++){
        freeList(h.table[i]);
        h.table[i]=NULL;
    }
    free(h.table);
    h.table=NULL;
    printf("Passed!\n");
    return 1;
}

int test_hashtableGetValue_vg(){
    int score=valgrind_test("hashtableGetValue","","Memory test for hashtableGetValue");
    return score;
}

int test_hashtableGetValue(){
    printf("----------------------------------------------\n");
    printf("Unit tests for hashtableGetValue \n");
    printf("----------------------------------------------\n");

    int score = test_hashtableGetValue_results();
    score+=test_hashtableGetValue_vg();
    return score;
}
