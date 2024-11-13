#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../../list/list.h"
#include<string.h>

void buildExampleList(List* tabList){
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

int
main(int argc, char *argv[])
{
    List *tabList = malloc(7*sizeof(List));
    buildExampleList(tabList);
    List list = tabList[0];
    printList(list,1);
    list = delKeyInList(list,NULL);
    list = delKeyInList(list,"K4");
    list = delKeyInList(list,"K1");
    list = delKeyInList(list,"K4");
    list = delKeyInList(list,"K2");
    list = delKeyInList(list,NULL);
    list = delKeyInList(list,"K2");

    for(int i=0;i<7;i++){
        tabList[i]=NULL;
    }
    free(tabList);
    tabList=NULL;
    return 0;

}
