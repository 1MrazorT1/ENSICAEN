#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../../list/list.h"
#include<string.h>


int
main(int argc, char *argv[])
{
    int score = 0;
    List L = NULL;


    L = addKeyValueInList(L,NULL,0);
    L = addKeyValueInList(L,NULL,1);

    //free the list L
    free(L->nextCell->key);
    L->nextCell->key=NULL;
    free(L->nextCell);
    L->nextCell=NULL;
    free(L->key);
    L->key=NULL;
    free(L);
    L=NULL;

    L = addKeyValueInList(L,"K1",0);
    L = addKeyValueInList(L,"K2",1);

    //free the list L
    free(L->nextCell->key);
    L->nextCell->key=NULL;
    free(L->nextCell);
    L->nextCell=NULL;
    free(L->key);
    L->key=NULL;
    free(L);
    L=NULL;

    return 0;

}
