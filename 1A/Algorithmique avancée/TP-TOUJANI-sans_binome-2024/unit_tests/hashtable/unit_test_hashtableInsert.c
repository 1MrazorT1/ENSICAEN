int test_hashtable_valid(HashTable h, size_t nbKey,int* values){
    size_t size =1;
    char key[10];

    size_t counter=0;
    for(size_t i=0;i<nbKey;i++){
        if(values[i]!=-1){
            counter++;
        }
    }
    if(h.numberOfPairs != counter){
        printf("Failed : the number of pairs in the hashtable (%zu) is different from the expected number of pairs (%zu).\n", h.numberOfPairs, counter);
        return 0;
    }


    while(size<counter){
        size*=2;
    }
    if(h.sizeTable != size){
        printf("Failed : the size of the hashtable is not the expected one.\n");
        printf("Expected size is %zu but the output size is %zu.\n",size,h.sizeTable);
        return 0;
    }

    if(h.table==NULL){
        printf("Failed : the field table is NULL.\n");
        return 0;
    }

    counter=0;
    for(size_t i =0; i<h.sizeTable;i++){
        Cell *list = h.table[i];
        while(list!=NULL){
            counter++;
            list=list->nextCell;
        }
    }
    if(h.numberOfPairs != counter){
        printf("Failed : the number of pairs in the hashtable (%zu) is different from the field numberOfPairs (%zu).\n",counter, h.numberOfPairs);
        return 0;
    }


    for(size_t i=0;i<nbKey;i++){
        sprintf(key,"key %zu",i);
        size_t hashkey = murmurhash(key,strlen(key),h.sizeTable);
        Cell *cell = findKeyInList(h.table[hashkey],key);
        if(values[i]!=-1){
            if(cell==NULL || cell->value !=values[i]){
                printf("Failed : expected key not found or wrong value associated to the key.\n");
                printf("Perhaps an existing key is not update.\n");
                return 0;
            }
        }
        else{
            if(cell!=NULL){
                printf("Failed : unexpected key found in the hashtable.\n");
                return 0;
            }
        }
    }
    return 1;
}



int test_hashtableInsert_known_result1(){
    printf("** Insert 10 elements in a hashtable of initial size 1 with distinct keys.\n");
    char key[10];
    HashTable h = hashtableCreate(1);
    int values[10];
    for(int i=0;i<10;i++){
        sprintf(key,"key %d",i);
        values[i]=i;
        hashtableInsert(&h,key,i);
    }
    if(test_hashtable_valid(h,10,values)==0){
        return 0;
    }
    for(size_t i=0;i<h.sizeTable;i++){
        freeList(h.table[i]);
        h.table[i]=NULL;
    }
    free(h.table); h.table=NULL;
    printf("Passed!\n");
    return 1;
}


int test_hashtableInsert_known_result2(){
    printf("** Insert 10 elements in a hashtable of size 1 with distinct keys and then update the value of 3 existing keys.\n");
    char key[10];
    HashTable h = hashtableCreate(1);
    int values[10];
    for(int i=0;i<10;i++){
        sprintf(key,"key %d",i);
        values[i]=i;
        hashtableInsert(&h,key,i);
    }
    hashtableInsert(&h,"key 1",10);values[1]=10;
    hashtableInsert(&h,"key 2",20);values[2]=20;
    hashtableInsert(&h,"key 3",30);values[3]=30;

    if(test_hashtable_valid(h,10,values)==0){
        return 0;
    }
    for(size_t i=0;i<h.sizeTable;i++){
        freeList(h.table[i]);
        h.table[i]=NULL;
    }
    free(h.table); h.table=NULL;
    printf("Passed!\n");
    return 1;
}

int test_hashtableInsert_random_result(){
    int n = 100+rand()%500;
    int nbKeys = 100;

    printf("** Insert %d random pairs (key,value) in a hashtable of size 1 with possible repetions on the %d different keys.\n",n,nbKeys);
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
    if(test_hashtable_valid(h,nbKeys,tabValue)==0){
        return 0;
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

int test_hashtableInsert_results(){
    int score=test_hashtableInsert_known_result1();
    score=test_hashtableInsert_known_result2();
    score+=test_hashtableInsert_random_result();
    return score;
}

int test_hashtableInsert_vg(){
    int score=valgrind_test("hashtableInsert","","Memory test for hashtableInsert");
    return score;
}

int test_hashtableInsert(){
    printf("----------------------------------------------\n");
    printf("Unit tests for hashtableInsert \n");
    printf("----------------------------------------------\n");

    int score = test_hashtableInsert_results();
    score+=test_hashtableInsert_vg();
    return score;
}
