#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../../list/list.h"
#include <string.h>


void write_scores_to_file(int score){
    FILE* file = fopen("score.log","a");
    if(file!=NULL){
        fprintf(file,"%d\n",score);
    }
    fclose(file);
}


int valgrind_test(char* execfile, char* parameters, char* comment){
    char bashcommand[200];
    sprintf(bashcommand,"sh bashscript.sh %s %s",execfile, parameters);

    char logvalgrind[100];
    sprintf(logvalgrind, "log-%s.out",execfile);

    char scorevalgrind[100];
    sprintf(scorevalgrind, "score-%s.out",execfile);

    printf("** Check the memory with valgrind: ./%s %s [%s]\n",execfile,parameters,comment);
    //printf("%s\n",bashcommand);
    int status = system(bashcommand);
    if (status == -1) {
        printf("Error while executing \"%s\".\n",bashcommand);
        printf("Test failed.\n");
        return 0;
    }
    FILE* data = fopen(scorevalgrind,"r");
    if(data==NULL){
        printf("Fail to open file %s during the test.\n",scorevalgrind);
        printf("Test failed.\n");
        return 0;
    }
    if(fscanf(data,"%d",&status)==EOF)
    {
        printf("Fail to read in file %s during the test.\n",scorevalgrind);
        printf("Test failed.\n");
        return 0;
    }
    fclose(data);
    if (status != 0) {
        printf("Valgrind has detected memory errors. See %s for details. \n",logvalgrind);
        printf("Test failed.\n");
        return 0;
    }
    sprintf(bashcommand,"rm -f %s",logvalgrind);
    system(bashcommand);
    sprintf(bashcommand,"rm -f %s",scorevalgrind);
    system(bashcommand);
    printf("Successful test.\n");
    return 1;
}

void buildExampleList(List tabList[7]){
    int i = 7;

    i--;
    tabList[i]=malloc(sizeof(Cell));
    tabList[i]->key = NULL;
    tabList[i]->value=i;
    tabList[i]->nextCell=NULL;

    i--;
    tabList[i]=malloc(sizeof(Cell));
    tabList[i]->key = malloc(3*sizeof(char));
    sprintf(tabList[i]->key,"K%d",4);
    tabList[i]->value=i;
    tabList[i]->nextCell=tabList[i+1];

    i--;
    tabList[i]=malloc(sizeof(Cell));
    tabList[i]->key = malloc(3*sizeof(char));
    sprintf(tabList[i]->key,"K%d",1);
    tabList[i]->value=i;
    tabList[i]->nextCell=tabList[i+1];

    i--;
    tabList[i]=malloc(sizeof(Cell));
    tabList[i]->key = malloc(3*sizeof(char));
    sprintf(tabList[i]->key,"K%d",4);
    tabList[i]->value=i;
    tabList[i]->nextCell=tabList[i+1];


    i--;
    tabList[i]=malloc(sizeof(Cell));
    tabList[i]->key = malloc(3*sizeof(char));
    sprintf(tabList[i]->key,"K%d",i);
    tabList[i]->value=i;
    tabList[i]->nextCell=tabList[i+1];

    i--;
    tabList[i]=malloc(sizeof(Cell));
    tabList[i]->key = NULL;
    tabList[i]->value=i;
    tabList[i]->nextCell=tabList[i+1];

    i--;
    tabList[i]=malloc(sizeof(Cell));
    tabList[i]->key = malloc(3*sizeof(char));
    sprintf(tabList[i]->key,"K%d",2);
    tabList[i]->value=i;
    tabList[i]->nextCell=tabList[i+1];

}

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
/* --------------------------
 * --------------------------
 * newList tests
 * --------------------------
 * --------------------------
 */

int test_newList_NULL(){
    printf("** Check it returns NULL\n");
    for(int i=0;i<100;i++)
        if (newList()!=NULL){
            printf("Error: newList() does not return NULL pointer.\n");
            printf("Test failed.\n");
            //write_scores_to_file(0);
            return 0;
        }
    printf("Successful test.\n");
    //write_scores_to_file(1);
    return 1;
}

int test_newList_valgrind(){
    int score = valgrind_test("vgnewlist","","[no memory for empty list?]");
    //write_scores_to_file(score);
    return score;
}



int test_newList() {
    int score=0;
    printf("-----------------------------------\n");
    printf("Unit test for newList()\n");
    printf("-------------------------------------\n");
    score+=test_newList_NULL();
    score+=test_newList_valgrind();
    printf("Summary: %d successful tests over 2 tests for newList().\n",score);
    return score;
}


/* --------------------------
 * --------------------------
 * freeList tests
 * --------------------------
 * --------------------------
 */




int test_freeList_with_cells(int nbCells, int nullKey){
    char *execfile = "vgfreelist";
    char parameters[100];
    sprintf(parameters,"%d %d",nbCells,nullKey);
    char comment[200];
    if(nullKey==0)
        sprintf(comment,"[list with %d cell(s) and no null key(s)]",nbCells);
    else
        sprintf(comment,"[list with %d cell(s) and null key(s)]",nbCells);
    int score = valgrind_test(execfile,parameters,comment);
    //write_scores_to_file(score);
    return score;
}


int  test_freeList(){
    int score=0;
    printf("-----------------------------------\n");
    printf("Unit tests for freeList()\n");
    printf("-------------------------------------\n");
    score+=test_freeList_with_cells(0,0);
    score+=test_freeList_with_cells(1,0);
    score+=test_freeList_with_cells(1,1);
    score+=test_freeList_with_cells(100,0);
    score+=test_freeList_with_cells(100,1);
    printf("Summary: %d successful tests over 5 tests for freeList().\n",score);
    return score;
}


/* --------------------------
 * --------------------------
 * printList tests
 * --------------------------
 * --------------------------
 */

int test_printList_with_cells(int nbCells, int nullKey, int outputType){
    char *execfile = "vgprintlist";
    char parameters[100];
    sprintf(parameters,"%d %d %d",nbCells,nullKey,outputType);
    char comment[200];

    char snullkey[30];
    if(nullKey==0)
        sprintf(snullkey,"%s", "no null key(s)");
    else
        sprintf(snullkey,"%s", "null key(s)");
    char soutputtype[30];
    if(outputType==0)
        sprintf(soutputtype,"%s", "print value(s)");
    else
        sprintf(soutputtype,"%s", "print couples (key,value)");

    sprintf(comment,"[list with %d cell(s) and %s, %s]",nbCells,snullkey,soutputtype);
    int score = valgrind_test(execfile,parameters,comment);
    //write_scores_to_file(score);
    return score;
}

int compare_file_text(int nbCells, int nullKey, int outputType, char* solution){
    char snullkey[30];
    if(nullKey==0)
        sprintf(snullkey,"%s", "no null key(s)");
    else
        sprintf(snullkey,"%s", "null key(s)");
    char soutputtype[30];
    if(outputType==0)
        sprintf(soutputtype,"%s", "print value(s)");
    else
        sprintf(soutputtype,"%s", "print couples (key,value)");

    printf("** Test output format:  [list with %d cell(s) and %s, %s]\n",nbCells,snullkey,soutputtype);

    FILE *output = fopen("output.txt","r");
    if(output==NULL){
        printf("Fail to open file output.txt during the test.\n");
        printf("Test failed.\n");
        return 0;
    }
    char line[1000];
    int i=0;
    char letter = fgetc(output);
    while ( (!feof( output )) && (i<999)  ) {
        line[i]=letter;
        letter = fgetc(output);
        i++;
    }
    line[i]='\0';
    fclose(output);
    if(strcmp(solution,line)==0){
        printf("Successful test\n");
        //write_scores_to_file(1);
        return 1;
    }
    printf("Test failed:\n");
    printf("Output:\n %s\n",line);
    printf("Solution:\n %s\n",solution);
    //write_scores_to_file(0);
    return 0;
}


int test_printList(){
    int score=0;
    printf("-----------------------------------\n");
    printf("Unit tests for printList()\n");
    printf("-------------------------------------\n");
    score+=test_printList_with_cells(0,0,0);
    score+=compare_file_text(0,0,0,"[]");

    score+=test_printList_with_cells(1,0,0);
    score+=compare_file_text(1,0,0,"[0]");

    score+=test_printList_with_cells(1,1,0);
    score+=compare_file_text(1,1,0,"[0]");

    score+=test_printList_with_cells(10,0,0);
    score+=compare_file_text(10,0,0,"[9,8,7,6,5,4,3,2,1,0]");

    score+=test_printList_with_cells(10,1,0);
    score+=compare_file_text(10,1,0,"[9,8,7,6,5,4,3,2,1,0]");

    score+=test_printList_with_cells(0,0,1);
    score+=compare_file_text(0,0,1,"[]");

    score+=test_printList_with_cells(1,0,1);
    score+=compare_file_text(1,0,1,"[(0 key(s),0)]");

    score+=test_printList_with_cells(1,1,1);
    score+=compare_file_text(1,1,1,"[(NULL,0)]");

    score+=test_printList_with_cells(5,0,1);
    score+=compare_file_text(5,0,1,"[(4 key(s),4),(3 key(s),3),(2 key(s),2),(1 key(s),1),(0 key(s),0)]");

    score+=test_printList_with_cells(5,1,1);
    score+=compare_file_text(5,1,1,"[(NULL,4),(NULL,3),(NULL,2),(NULL,1),(NULL,0)]");

    printf("Summary: %d successful tests over 20 tests for printList().\n",score);
    return score;
}

/* --------------------------
 * --------------------------
 * findKeyInList tests
 * --------------------------
 * --------------------------
 */




int test_findKeyInList_result(){
    List tabList[7];
    buildExampleList(tabList);

    int score=0;
    printf("** Find a nul key in an empty list:\n");
    printf("Key=NULL    list = NULL\n");
    List result = findKeyInList(NULL,NULL);
    if(result==NULL){
        printf("test passed.\n");
        score+=1;
    }
    else
        printf("test failed.\n");

    printf("** Find a nul key in a non empty list not containing a null key:\n");
    tabList[4]->nextCell = NULL;
    result = findKeyInList(tabList[2],NULL);
    printf("Key=NULL    list = ");
    printList(tabList[2],1);
    if(result==NULL){
        printf("\ntest passed.\n");
        score+=1;
    }
    else
        printf("\ntest failed.\n");


    printf("** Find a nul key in a non empty list containing a null key:\n");
    tabList[4]->nextCell = tabList[5];
    result = findKeyInList(tabList[2],NULL);
    printf("Key=NULL    list = ");
    printList(tabList[2],1);
    if(result==tabList[6]){
        printf("\ntest passed.\n");
        score+=1;
    }
    else
        printf("\ntest failed.\n");
    result = findKeyInList(tabList[0],NULL);
    printf("Key=NULL    list = ");
    printList(tabList[0],1);
    if(result==tabList[1]){
        printf("\ntest passed.\n");
        score+=1;
    }
    else
        printf("\ntest failed.\n");


    printf("** Find a non nul key in an empty list:\n");
    printf("Key=\"K2\"    list = NULL\n");
    result = findKeyInList(NULL,"K2");
    if(result==NULL){
        printf("test passed.\n");
        score+=1;
    }
    else
        printf("test failed.\n");

    printf("** Find a non nul key in a non empty list not containing the key:\n");
    result = findKeyInList(tabList[0],"K3");
    printf("Key=\"K3\"    list = ");
    printList(tabList[0],1);
    if(result==NULL){
        printf("\ntest passed.\n");
        score+=1;
    }
    else
        printf("\ntest failed.\n");

    printf("** Find a non nul key in a non empty list containing the key:\n");
    result = findKeyInList(tabList[0],"K4");
    printf("Key=\"K4\"    list = ");
    printList(tabList[0],1);
    if(result==tabList[3]){
        printf("\ntest passed.\n");
        score+=1;
    }
    else
        printf("\ntest failed.\n");
    //free the memory
    for(int i=0;i<7;i++){
        free(tabList[i]->key);
        tabList[i]->key=NULL;
        tabList[i]->nextCell=NULL;
        free(tabList[i]);
        tabList[i]=NULL;
    }
    //write_scores_to_file(score);
    return score;

}




int test_findKeyInList_memory(){
    int score = valgrind_test("vgfindkeylist","","[Memory test for testing the 7 previous cases]");
    //write_scores_to_file(score);
    return score;
}



int test_findKeyInList(){
    int score=0;
    printf("-----------------------------------\n");
    printf("Unit tests for findKeyInList()\n");
    printf("-------------------------------------\n");
    score+=test_findKeyInList_result();
    score+=test_findKeyInList_memory();
    printf("Summary: %d successful tests over 8 tests for findKeyInList().\n",score);
    return score;
}

/* --------------------------
 * --------------------------
 * delKeyInList tests
 * --------------------------
 * --------------------------
 */

int test_delKeyInList_result(){
    List tabList[7];
    buildExampleList(tabList);
    /* [(K2,0),(NULL,1),(K2,2),(K4,3),(K1,4),(K4,5),(NULL,6)] */

    List result;
    int score=0;
    char *strListBefore;
    char *strListAfter;
    char strExpected[200];

// *********************************
    printf("** del a nul key in an empty list:\n");
    printf("Key=NULL    list = NULL\n");
    result = delKeyInList(NULL,NULL);
    if(result==NULL){
        printf("test passed.\n");
        score+=1;
    }
    else{
        printf("\ntest failed.\n");
        printf("Fix the bug before continuing.\n");
        //write_scores_to_file(score);
        return score;
    }

// *********************************
    printf("** Del a nul key in a non empty list not containing a null key:\n");
    tabList[4]->nextCell = NULL;
    printf("Key=NULL    list = ");
    printList(tabList[2],1);
    strListBefore = listToString(tabList[2]);
    result = delKeyInList(tabList[2],NULL);
    strListAfter = listToString(tabList[2]);
    if(strcmp(strListBefore,strListAfter)==0){
        printf("\ntest passed.\n");
        score+=1;
    }
    else{
        printf("\ntest failed.\n");
        printf("Fix the bug before continuing.\n");
        //write_scores_to_file(score);
        return score;
    }
    tabList[4]->nextCell = tabList[5];
    free(strListBefore); strListBefore = NULL;
    free(strListAfter); strListAfter = NULL;

// *********************************
    printf("** Del a nul key in a non empty list containing a null key:\n");
    printf("Key=NULL    list = ");
    printList(tabList[2],1);
    sprintf(strExpected,"%s","(K2,2)(K4,3)(K1,4)(K4,5)");
    result = delKeyInList(tabList[2],NULL);
    strListAfter = listToString(result);
    if(strcmp(strExpected,strListAfter)==0){
        printf("\ntest passed.\n");
        score+=1;
    }
    else{
        printf("\ntest failed.\n");
        printf("Expected result: %s\n",strExpected);
        printf("Obtained result: %s\n",strListAfter);
        printf("Fix the bug before continuing.\n");
        //write_scores_to_file(score);
        return score;
    }
    tabList[6]=NULL;
    free(strListAfter); strListAfter = NULL;

// *********************************

    printf("** del a non nul key in an empty list:\n");
    printf("Key=ABC    list = NULL\n");
    result = delKeyInList(NULL,"ABC");
    if(result==NULL){
        printf("test passed.\n");
        score+=1;
    }
    else{
        printf("\ntest failed.\n");
        printf("Fix the bug before continuing.\n");
        //write_scores_to_file(score);
        return score;
    }

// *********************************

    printf("** Del a non nul key in a non empty list not containing the key:\n");
    printf("Key=ABC    list = ");
    printList(tabList[0],1);
    strListBefore = listToString(tabList[0]);
    result = delKeyInList(tabList[2],"ABC");
    strListAfter = listToString(tabList[0]);
    if(strcmp(strListBefore,strListAfter)==0){
        printf("\ntest passed.\n");
        score+=1;
    }
    else{
        printf("\ntest failed.\n");
        printf("Fix the bug before continuing.\n");
        //write_scores_to_file(score);
        return score;
    }
    free(strListBefore); strListBefore = NULL;
    free(strListAfter); strListAfter = NULL;


// *********************************

    printf("** Del a non nul key in a non empty list containing the key:\n");
    printf("Key=K4    list = ");
    printList(tabList[0],1);
    sprintf(strExpected,"%s","(K2,0)(NULL,1)(K2,2)(K1,4)(K4,5)");
    result = delKeyInList(tabList[0],"K4");
    strListAfter = listToString(result);
    if(strcmp(strExpected,strListAfter)==0){
        printf("\ntest passed.\n");
        score+=1;
    }
    else{
        printf("\ntest failed.\n");
        printf("Expected result: %s\n",strExpected);
        printf("Obtained result: %s\n",strListAfter);
        printf("Fix the bug before continuing.\n");
        //write_scores_to_file(score);
        return score;
    }
    tabList[3]=NULL;
    free(strListAfter); strListAfter = NULL;


// *********************************
    printf("** Del the first key of the list:\n");
    printf("Key=K2    list = ");
    printList(tabList[0],1);
    sprintf(strExpected,"%s","(NULL,1)(K2,2)(K1,4)(K4,5)");
    result = delKeyInList(tabList[0],"K2");
    strListAfter = listToString(result);
    if(strcmp(strExpected,strListAfter)==0){
        printf("\ntest passed.\n");
        score+=1;
    }
    else{
        printf("\ntest failed.\n");
        printf("Expected result: %s\n",strExpected);
        printf("Obtained result: %s\n",strListAfter);
        printf("Fix the bug before continuing.\n");
        //write_scores_to_file(score);
        return score;
    }
    tabList[0]=NULL;
    free(strListAfter); strListAfter = NULL;


// *********************************
    printf("** Del the last key of the list:\n");
    printf("Key=K4    list = ");
    printList(tabList[1],1);
    sprintf(strExpected,"%s","(NULL,1)(K2,2)(K1,4)");
    result = delKeyInList(tabList[1],"K4");
    strListAfter = listToString(result);
    if(strcmp(strExpected,strListAfter)==0){
        printf("\ntest passed.\n");
        score+=1;
    }
    else{
        printf("\ntest failed.\n");
        printf("Expected result: %s\n",strExpected);
        printf("Obtained result: %s\n",strListAfter);
        printf("Fix the bug before continuing.\n");
        //write_scores_to_file(score);
        return score;
    }
    tabList[5]=NULL;
    free(strListAfter); strListAfter = NULL;
    //free the memory
    for(int i=0;i<7;i++){
        if(tabList[i]!=NULL){
            free(tabList[i]->key);
            tabList[i]->key=NULL;
            tabList[i]->nextCell=NULL;
            free(tabList[i]);
            tabList[i]=NULL;
        }
    }


    //write_scores_to_file(score);
    return score;

}

int test_delKeyInList_memory(){
    int score = valgrind_test("vgdelkeylist","","[Memory test for testing delKeyInList]");
    //write_scores_to_file(score);
    return score;
}




int test_delKeyInList(){
    int score=0;

    printf("-----------------------------------\n");
    printf("Unit tests for delKeyInList()\n");
    printf("-------------------------------------\n");
    score+=test_delKeyInList_result();
    score+=test_delKeyInList_memory();
    printf("Summary: %d successful tests over 9 tests for delKeyInList().\n",score);
    return score;

}

/* --------------------------
 * --------------------------
 * addKeyValueInList tests
 * --------------------------
 * --------------------------
 */

int test_addList_result(){
    int score = 0;
    List L = NULL;

    char *strListAfter;
    char strExpected[200];


    printf("** Add a null key in an empty list:");
    L = addKeyValueInList(L,NULL,0);
    strListAfter =listToString(L);
    sprintf(strExpected,"%s","(NULL,0)");
    if(strcmp(strExpected,strListAfter)==0){
        printf("\ntest passed.\n");
        score+=1;
    }
    else{
        printf("\ntest failed.\n");
        printf("Expected result: %s\n",strExpected);
        printf("Obtained result: %s\n",strListAfter);
        printf("Fix the bug before continuing.\n");
        //write_scores_to_file(score);
        return score;
    }
    free(strListAfter);
    strListAfter=NULL;


    printf("** Add a null key in a non empty list:");
    L = addKeyValueInList(L,NULL,1);
    strListAfter =listToString(L);
    sprintf(strExpected,"%s","(NULL,1)(NULL,0)");
    if(strcmp(strExpected,strListAfter)==0){
        printf("\ntest passed.\n");
        score+=1;
    }
    else{
        printf("\ntest failed.\n");
        printf("Expected result: %s\n",strExpected);
        printf("Obtained result: %s\n",strListAfter);
        printf("Fix the bug before continuing.\n");
        //write_scores_to_file(score);
        return score;
    }
    free(strListAfter);
    strListAfter=NULL;

    //free the list L
    free(L->nextCell->key);
    L->nextCell->key=NULL;
    free(L->nextCell);
    L->nextCell=NULL;
    free(L->key);
    L->key=NULL;
    free(L);
    L=NULL;

    printf("** Add a non null key in an empty list:");
    char keyToAdd[10];
    sprintf(keyToAdd,"%s","K1");
    L = addKeyValueInList(L,keyToAdd,0);
    strListAfter =listToString(L);
    sprintf(strExpected,"%s","(K1,0)");
    if(strcmp(strExpected,strListAfter)==0){
        printf("\ntest passed.\n");
        score+=1;
    }
    else{
        printf("\ntest failed.\n");
        printf("Expected result: %s\n",strExpected);
        printf("Obtained result: %s\n",strListAfter);
        printf("Fix the bug before continuing.\n");
        //write_scores_to_file(score);
        return score;
    }
    free(strListAfter);
    strListAfter=NULL;

    printf("** Verification that a deep a copy has been when adding a key:");
    sprintf(keyToAdd,"%s","K1bis");
    strListAfter =listToString(L);
    sprintf(strExpected,"%s","(K1,0)");
    if(strcmp(strExpected,strListAfter)==0){
        printf("\ntest passed.\n");
        score+=1;
    }
    else{
        printf("\ntest failed.\n");
        printf("Expected result: %s\n",strExpected);
        printf("Obtained result: %s\n",strListAfter);
        printf("A deep copy of the key must be done. Fix the bug before continuing.\n");
        //write_scores_to_file(score);
        return score;
    }
    free(strListAfter);
    strListAfter=NULL;

    printf("** Add a non null key in a non empty list:");
    sprintf(keyToAdd,"%s","K2");
    L = addKeyValueInList(L,keyToAdd,1);
    strListAfter =listToString(L);
    sprintf(strExpected,"%s","(K2,1)(K1,0)");
    if(strcmp(strExpected,strListAfter)==0){
        printf("\ntest passed.\n");
        score+=1;
    }
    else{
        printf("\ntest failed.\n");
        printf("Expected result: %s\n",strExpected);
        printf("Obtained result: %s\n",strListAfter);
        printf("Fix the bug before continuing.\n");
        //write_scores_to_file(score);
        return score;
    }
    free(strListAfter);
    strListAfter=NULL;


    printf("** Verification that a deep a copy has been when adding a key:");
    sprintf(keyToAdd,"%s","K2bis");
    strListAfter =listToString(L);
    sprintf(strExpected,"%s","(K2,1)(K1,0)");
    if(strcmp(strExpected,strListAfter)==0){
        printf("\ntest passed.\n");
        score+=1;
    }
    else{
        printf("\ntest failed.\n");
        printf("Expected result: %s\n",strExpected);
        printf("Obtained result: %s\n",strListAfter);
        printf("A deep copy of the key must be done. Fix the bug before continuing.\n");
        //write_scores_to_file(score);
        return score;
    }
    free(strListAfter);
    strListAfter=NULL;

    //free the list L
    free(L->nextCell->key);
    L->nextCell->key=NULL;
    free(L->nextCell);
    L->nextCell=NULL;
    free(L->key);
    L->key=NULL;
    free(L);
    L=NULL;

    //write_scores_to_file(score);
    return score;
}


int test_addList_memory(){
    int score = valgrind_test("vgaddkeylist","","[Memory test for addKeyValueInList]");
    //write_scores_to_file(score);
    return score;
}


int test_addKeyValueInList(){
    int score=0;

    printf("-----------------------------------\n");
    printf("Unit tests for addKeyValueInList()\n");
    printf("-------------------------------------\n");
    score+=test_addList_result();
    score+=test_addList_memory();
    printf("Summary: %d successful tests over 7 tests for addKeyValueInList().\n",score);
    return score;
}




int main() {
    system("clear");
    system("rm -f score.log");
    int score1 = test_newList();
    int score2 = test_freeList();
    int score3 = test_printList();
    int score4 = test_findKeyInList();
    int score5 = test_delKeyInList();
    int score6 = test_addKeyValueInList();
    system("rm -f output.txt");
    printf("-----------------------------------\n");
    printf("Summary of the unit tests \n");
    printf("-------------------------------------\n");
    printf("Summary: %d successful tests over 2 tests for newList().\n",score1);
    printf("Summary: %d successful tests over 5 tests for freeList().\n",score2);
    printf("Summary: %d successful tests over 20 tests for printList().\n",score3);
    printf("Summary: %d successful tests over 8 tests for findKeyInList().\n",score4);
    printf("Summary: %d successful tests over 9 tests for delKeyInList().\n",score5);
    printf("Summary: %d successful tests over 7 tests for addKeyValueInList().\n",score6);

    return 0;
}
