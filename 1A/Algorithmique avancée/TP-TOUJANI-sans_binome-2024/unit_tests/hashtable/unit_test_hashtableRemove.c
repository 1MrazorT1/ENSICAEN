int test_hashtableRemove_results(){
    int n = 100+rand()%200;
    int nbKeys = 600;

    printf("** Insert %d random pairs (key,value) in a hashtable of size 1 with possible repetions on the %d different keys and then test the hashtableRemove function.\n",n,nbKeys);
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
        if(hashtableRemove(&h,key)==1){
            if(tabValue[i]==-1){
                printf("Failed: hashtableRemove returns 1 (found key and removed) whereas the key is not in the hashtable.\n");
                return 0;
            }
            else{
                if(hashtableHasKey(h,key)!=0){
                    printf("Failed: a key is still in the table after a call to hashtableRemove.\n");
                    return 0;
                }
                tabValue[i]=-1;
            }
        }
        else{
            if(tabValue[i]!=-1){
                printf("Failed: hashtableRemove returns 0 whereas the key is in the hashtable and must be removed.\n");
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

int test_hashtableRemove_vg(){
    int score=valgrind_test("hashtableRemove","","Memory test for hashtableRemove");
    return score;
}

int test_hashtableRemove(){
    printf("----------------------------------------------\n");
    printf("Unit tests for hashtableRemove \n");
    printf("----------------------------------------------\n");

    int score = test_hashtableRemove_results();
    score+=test_hashtableRemove_vg();
    return score;
}
