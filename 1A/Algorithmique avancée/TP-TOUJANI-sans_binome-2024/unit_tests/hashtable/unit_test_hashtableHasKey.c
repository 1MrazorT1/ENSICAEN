int test_hashtableHasKey_results(){
    int n = 100+rand()%500;
    int nbKeys = 600;

    printf("** Insert %d random pairs (key,value) in a hashtable of size 1 with possible repetions on the %d different keys and then test the hashtableHasKey function.\n",n,nbKeys);
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
        if(hashtableHasKey(h,key)==1){
            if(tabValue[i]==-1){
                printf("Failed: a key found in the hashtable whereas it shouldn't.\n");
                return 0;
            }
        }
        else{
            if(tabValue[i]!=-1){
                printf("Failed: a key not found in the hashtable whereas it should.\n");
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

int test_hashtableHasKey_vg(){
    int score=valgrind_test("hashtableHasKey","","Memory test for hashtableHasKey");
    return score;
}

int test_hashtableHasKey(){
    printf("----------------------------------------------\n");
    printf("Unit tests for hashtableHasKey \n");
    printf("----------------------------------------------\n");

    int score = test_hashtableHasKey_results();
    score+=test_hashtableHasKey_vg();
    return score;
}
