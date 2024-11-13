
char* listToString(List l){
    char res1[1000];
    res1[0]='\0';
    Cell *current = l;
    while(current!=NULL){
        char strCell[100];
        if(current->key==NULL)
            sprintf(strCell,"(NULL,%d)",current->value);
        else
            sprintf(strCell,"(%s,%d)",current->key,current->value);
        strcat(res1,strCell);
        current = current->nextCell;
    }
    char *result = malloc((strlen(res1)+1)*sizeof(char));
    strcpy(result,res1);
    return result;
}


int test_hashtable_valid_witout_resizing(HashTable h, size_t nbKey,int* values,size_t size){
    char key[10];

    if(h.sizeTable != size){
        printf("Failed : the size of the hashtable is not the expected one.\n");
        printf("Expected size is %zu but the output size is %zu.\n",size,h.sizeTable);
        return 0;
    }
    if(h.table==NULL){
        printf("Failed : the field table is NULL.\n");
        return 0;
    }

    size_t counter=0;
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

    counter=0;
    for(size_t i=0;i<nbKey;i++){
        if(values[i]!=-1){
            counter++;
        }
    }
    if(h.numberOfPairs != counter){
        printf("Failed : the number of pairs in the hashtable (%zu) is different from the expected number of pairs (%zu).\n", h.numberOfPairs, counter);
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


int test_hashtableInsertWithoutResizing_known_result1(){
    printf("** Insert 10 elements in a hashtable of size 4 with distinct keys.\n");
    char key[10];
    HashTable h = hashtableCreate(4);
    for(int i=0;i<10;i++){
        sprintf(key,"key %d",i);
        hashtableInsertWithoutResizing(&h,key,i);
    }
    if(h.sizeTable != 4){
        printf("Failed : the size of the hashtable has been modified.\n");
        printf("Expected size is 4 but the output size is %zu.\n",h.sizeTable);
        return 0;
    }
    if(h.numberOfPairs != 10){
        printf("Failed : the number of pairs in the hashtable is not the expected value.\n");
        printf("Expected value is 10 but the output value is %zu.\n",h.numberOfPairs);
        return 0;
    }
    char *list0 = listToString(h.table[0]);
    char *list1 = listToString(h.table[1]);
    char *list2 = listToString(h.table[2]);
    char *list3 = listToString(h.table[3]);

    if(strcmp(list0,"(key 8,8)(key 7,7)(key 4,4)")!=0){
        printf("Failed : table[0] of the hashtable is not the expected list.\n");
        printf("Expected list: (key 8,8)(key 7,7)(key 4,4)\n whereas table[0]=%s\n",list0);
        return 0;
    }
    if(strcmp(list1,"(key 6,6)(key 1,1)(key 0,0)")!=0){
        printf("Failed : table[1] of the hashtable is not the expected list.\n");
        printf("Expected list: (key 6,6)(key 1,1)(key 0,0)\n whereas table[1]=%s\n",list1);
        return 0;
    }
    if(strcmp(list2,"(key 9,9)(key 3,3)")!=0){
        printf("Failed : table[2] of the hashtable is not the expected list.\n");
        printf("Expected list: (key 9,9)(key 3,3)\n whereas table[2]=%s\n",list2);
        return 0;
    }
    if(strcmp(list3,"(key 5,5)(key 2,2)")!=0){
        printf("Failed : table[3] of the hashtable is not the expected list.\n");
        printf("Expected list: (key 5,5)(key 2,2)\n whereas table[3]=%s\n",list3);
        return 0;
    }
    printf("Passed.\n");

    for(int i=0;i<4;i++){
        freeList(h.table[i]);
        h.table[i]=NULL;
    }
    free(h.table); h.table=NULL;
    free(list0); list0=NULL;
    free(list1); list1=NULL;
    free(list2); list2=NULL;
    free(list3); list3=NULL;
    return 1;
}


int test_hashtableInsertWithoutResizing_known_result2(){
    printf("** Insert 10 elements in a hashtable of size 4 with distinct keys and then update the value of existing keys.\n");
    char key[10];
    HashTable h = hashtableCreate(4);
    for(int i=0;i<10;i++){
        sprintf(key,"key %d",i);
        hashtableInsertWithoutResizing(&h,key,i);
    }
    hashtableInsertWithoutResizing(&h,"key 1",10);
    hashtableInsertWithoutResizing(&h,"key 2",20);
    hashtableInsertWithoutResizing(&h,"key 3",30);

    if(h.sizeTable != 4){
        printf("Failed : the size of the hashtable has been modified.\n");
        printf("Expected size is 4 but the output size is %zu.\n",h.sizeTable);
        return 0;
    }
    if(h.numberOfPairs != 10){
        printf("Failed : the number of pairs in the hashtable is not the expected value.\n");
        printf("Expected value is 10 but the output value is %zu.\n",h.numberOfPairs);
        return 0;
    }
    char *list0 = listToString(h.table[0]);
    char *list1 = listToString(h.table[1]);
    char *list2 = listToString(h.table[2]);
    char *list3 = listToString(h.table[3]);

    if(strcmp(list0,"(key 8,8)(key 7,7)(key 4,4)")!=0){
        printf("Failed : table[0] of the hashtable is not the expected list.\n");
        printf("Expected list: (key 8,8)(key 7,7)(key 4,4)\n whereas table[0]=%s\n",list0);
        return 0;
    }
    if(strcmp(list1,"(key 6,6)(key 1,10)(key 0,0)")!=0){
        printf("Failed : table[1] of the hashtable is not the expected list.\n");
        printf("Expected list: (key 6,6)(key 1,10)(key 0,0)\n whereas table[1]=%s\n",list1);
        return 0;
    }
    if(strcmp(list2,"(key 9,9)(key 3,30)")!=0){
        printf("Failed : table[2] of the hashtable is not the expected list.\n");
        printf("Expected list: (key 9,9)(key 3,30)\n whereas table[2]=%s\n",list2);
        return 0;
    }
    if(strcmp(list3,"(key 5,5)(key 2,20)")!=0){
        printf("Failed : table[3] of the hashtable is not the expected list.\n");
        printf("Expected list: (key 5,5)(key 2,20)\n whereas table[3]=%s\n",list3);
        return 0;
    }
    printf("Passed.\n");

    for(int i=0;i<4;i++){
        freeList(h.table[i]);
        h.table[i]=NULL;
    }
    free(h.table); h.table=NULL;
    free(list0); list0=NULL;
    free(list1); list1=NULL;
    free(list2); list2=NULL;
    free(list3); list3=NULL;
    return 1;
}

int test_hashtableInsertWithoutResizing_random_result(){
    size_t sizeTable = 10+rand()%90;
    int n = 100+rand()%500;
    int nbKeys = 200;

    printf("** Insert %d random pairs (key,value) in a hashtable of size %zu with possible repetions on the %d different keys.\n",n,sizeTable,nbKeys);
    int tabValue[nbKeys];
    for(int i=0;i<nbKeys;i++)
        tabValue[i]=-1;
    char key[20];
    HashTable h = hashtableCreate(sizeTable);

    size_t nbOfPairs =0;
    for(int i=0;i<n;i++){
        int r = rand()%nbKeys;
        sprintf(key,"key %d",r);
        if(tabValue[r]==-1)
            nbOfPairs++;
        tabValue[r] = rand() % 100;
        hashtableInsertWithoutResizing(&h,key,tabValue[r]);
    }
    if(test_hashtable_valid_witout_resizing(h,nbKeys,tabValue,sizeTable)==0){
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

int test_hashtableInsertWithoutResizing_results(){
    int score=test_hashtableInsertWithoutResizing_known_result1();
    score=test_hashtableInsertWithoutResizing_known_result2();
    score+=test_hashtableInsertWithoutResizing_random_result();
    return score;
}

int test_hashtableInsertWithoutResizing_vg(){
    int score=valgrind_test("hashtableInsertWithoutResizing","","Memory test for hashtableInsertWithoutResizing");
    return score;
}

int test_hashtableInsertWithoutResizing(){
    printf("----------------------------------------------\n");
    printf("Unit tests for hashtableInsertWithoutResizing \n");
    printf("----------------------------------------------\n");

    int score = test_hashtableInsertWithoutResizing_results();
    score+=test_hashtableInsertWithoutResizing_vg();
    return score;
}
