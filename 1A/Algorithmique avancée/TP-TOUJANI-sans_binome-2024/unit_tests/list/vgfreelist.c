#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../../list/list.h"
#include<string.h>

int
main(int argc, char *argv[])
{
    int nbCells = atoi(argv[1]);
    int nullKey = atoi(argv[2]);

    List l=NULL;
    for(int i=0;i<nbCells;i++){
        Cell* current = malloc(sizeof(Cell));
        char key[50];
        sprintf(key,"%d key(s)",i);
        if(nullKey==0){
            current->key=malloc((strlen(key)+1)*sizeof(char));
            sprintf(current->key,key);
        }
        else
            current->key=NULL;
        current->value=i;
        current->nextCell = l;
        l=current;
    }
    freeList(l);
    l=NULL;
}
