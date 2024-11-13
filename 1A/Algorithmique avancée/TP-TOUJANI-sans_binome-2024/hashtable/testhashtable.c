/**
 * @file testhashtable.c
 * @brief Test program for the hash table data structure
 *
 * This file contains a program that tests the hash table data structure
 * and its associated functions.
 *
 * @author Loïck Lhote
 * @date merch 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include <string.h>

void testMurmurhash(){
    printf("---- Test murmurhash ----\n");
    int maxvalue = 5;
    int step=100;
    int nbsteps = 10;
    for(int value=0;value<nbsteps*step;value+=step){
       char key[10];
        sprintf(key,"%d",value);
        printf("hash code <%d for '%s':",maxvalue,key);
        printf("%zu\n",murmurhash(key,strlen(key),maxvalue));
    }
    printf("---- Fin test murmurhash ----\n");
}

void testCreateAndPrint(){
    //test for hashtableCreate and hashtablePrint
    printf("---- Test create and print ----\n");

    HashTable table= hashtableCreate(4);
    hashtablePrint(table);
    printf("---- Fin Test create and print ----\n");
}


void testHashtableInsertWithoutResizing(){
    printf("---- Test InsertWithoutResizing ----\n");

    int nbsteps=5;
    int step =100;
    HashTable table = hashtableCreate(4);
    hashtablePrint(table);
    for(int value=0;value<nbsteps*step;value+=step){
        char key[10];
        sprintf(key,"%d",value);
        hashtableInsertWithoutResizing(&table,key,value);
        hashtablePrint(table);
    }
    printf("---- Fin test InsertWithoutResizing ----\n");

}


void testHashtableDestroy(){
    printf("---- Test hashtableDestry ----\n");

    int nbsteps=5;
    int step =100;
    HashTable table = hashtableCreate(4);
    hashtablePrint(table);
    for(int value=0;value<nbsteps*step;value+=step){
        char key[10];
        sprintf(key,"%d",value);
        hashtableInsertWithoutResizing(&table,key,value);
    }
    printf("Before destroy:\n");
    hashtablePrint(table);
    printf("After destroy:\n");
    hashtableDestroy(&table);
    hashtablePrint(table);
    printf("---- Fin Test hashtableDestry ----\n");

}

void testHashtableDoubleSize(){
    printf("---- Test hashtableDoubleSize ----\n");

    int nbsteps=5;
    int step =100;
    HashTable table = hashtableCreate(4);
    hashtablePrint(table);
    for(int value=0;value<nbsteps*step;value+=step){
        char key[10];
        sprintf(key,"%d",value);
        hashtableInsertWithoutResizing(&table,key,value);
    }
    printf("Before double size:\n");
    hashtablePrint(table);
    printf("After double size:\n");
    HashTable newTable = hashtableDoubleSize(table);
    printf("Initial table\n");
    hashtablePrint(table);
    printf("New table\n");
    hashtablePrint(newTable);

    printf("---- Fin Test hashtableDoubleSize ----\n");

}

void testHashtableInsert(){
    printf("---- Test hashtableInsert ----\n");

    int nbsteps=10;
    int step =100;
    HashTable table = hashtableCreate(4);
    for(int value=0;value<nbsteps*step;value+=step){
        char key[10];
        sprintf(key,"%d",value);
        hashtableInsert(&table,key,value);
        hashtablePrint(table);
    }

    printf("---- Fin Test hashtableInsert ----\n");

}

void testHashtableHasKey(){
    printf("---- Test hashtableHasKey ----\n");

    int nbsteps=10;
    int step =100;
    HashTable table = hashtableCreate(4);
    for(int value=0;value<nbsteps*step;value+=step){
        char key[10];
        sprintf(key,"%d",value);
        hashtableInsert(&table,key,value);
    }
    hashtablePrint(table);
    for(int value=0;value<nbsteps*step*2;value+=step){
        char key[10];
        sprintf(key,"%d",value);
        if(hashtableHasKey(table,key))
            printf("Table has key '%s'\n",key);
        else
            printf("Table hasn't key '%s'\n",key);

    }

    printf("---- Fin Test hashtableHasKey ----\n");

}

void testHashtableGetValue(){
    printf("---- Test hashtableGetValue ----\n");

    int nbsteps=10;
    int step =100;
    HashTable table = hashtableCreate(4);
    for(int value=0;value<nbsteps*step;value+=step){
        char key[10];
        sprintf(key,"%d",value);
        hashtableInsert(&table,key,value);
    }
    hashtablePrint(table);
    for(int value=0;value<nbsteps*step;value+=step){
        char key[10];
        sprintf(key,"%d",value);
        printf(" '%s' : %d\n",key,hashtableGetValue(table,key));
    }

    printf("---- Fin Test hashtableGetValue ----\n");

}

void testHashtableRemove(){
    printf("---- Test hashtableRemove ----\n");

    int nbsteps=10;
    int step =100;
    HashTable table = hashtableCreate(4);
    for(int value=0;value<nbsteps*step;value+=step){
        char key[10];
        sprintf(key,"%d",value);
        hashtableInsert(&table,key,value);
    }
    hashtablePrint(table);
    for(int value=0;value<nbsteps*step;value+=(step/2)){
        char key[10];
        sprintf(key,"%d",value);
        int test = hashtableRemove(&table,key);
        if(test){
            printf("Key '%s' removed with success.\n",key);
            hashtablePrint(table);
        }
        else{
            printf("Fail to remove key '%s'.\n",key);
            hashtablePrint(table);
        }
    }

    printf("---- Fin Test hashtableRemove ----\n");

}

void testCountDistinctWordsInBook(){
    printf("---- Test countWordsInBook ----\n");
    countDistinctWordsInBook();
    printf("---- Fin Test countWordsInBook ----\n");

}


int main() {

    testMurmurhash();
    //testCreateAndPrint();
    //testHashtableInsertWithoutResizing();
    //testHashtableDestroy();
    //testHashtableDoubleSize();
    //testHashtableInsert();
    //testHashtableGetValue();
    //testHashtableRemove();
    //testCountDistinctWordsInBook();


    return 0;
}
