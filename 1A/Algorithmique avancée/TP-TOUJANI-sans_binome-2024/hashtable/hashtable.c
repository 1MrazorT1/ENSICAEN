/**
 * @file hashtable.c
 * @brief Source file for a hash table implementation  based on linked list
 *
 * This file contains the implementation of the hash table data structure
 * and its associated functions.
 *
 * @author Loïck Lhote
 * @date march 2023
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "hashtable.h"
#include "../list/list.h"

 /**
 * @brief Used in the murmurhash hash function
 */
#define ROTL32(x,y)    ((x << y) | (x >> (32 - y)))

 /**
 * @brief Hash function murmurhash
 *
 * @param key string representing the key to hash
 * @param sizeKey length of the string key
 * @param maxValue maximum value (excluded) that must return the hash function
 * @return the hash code of the key between 0 and maxValue-1
 */

size_t murmurhash(string key, size_t sizeKey, size_t maxValue)
{
    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;
    const uint32_t r1 = 15;
    const uint32_t r2 = 13;
    const uint32_t m = 5;
    const uint32_t n = 0xe6546b64;
    uint32_t hash = 0;
    uint32_t k = 0;

    for (size_t i = 0; i < sizeKey / 4; i++) {
        k = ((uint32_t *)key)[i];
        k *= c1;
        k = ROTL32(k, r1);
        k *= c2;

        hash ^= k;
        hash = ROTL32(hash, r2);
        hash = hash * m + n;
    }

    // Handle the last few bytes of the input string
    k = 0;
    uint8_t *tail = (uint8_t *)key + (sizeKey & ~3);
    switch (sizeKey & 3) {
        case 3:
            k ^= tail[2] << 16;
        case 2:
            k ^= tail[1] << 8;
        case 1:
            k ^= tail[0];
            k *= c1;
            k = ROTL32(k, r1);
            k *= c2;
            hash ^= k;
    }

    // Finalize the hash value
    hash ^= sizeKey;
    hash ^= hash >> 16;
    hash *= 0x85ebca6b;
    hash ^= hash >> 13;
    hash *= 0xc2b2ae35;
    hash ^= hash >> 16;

    return hash % maxValue;
}


/**
 * @brief Prints the contents of a hash table
 *
 * @param hashtable Hash table to be printed
 */
void hashtablePrint(HashTable hashtable) {
    printf("---Hash Table:\n");
    printf("Size: %zu\n", hashtable.sizeTable);
    printf("Number of Pairs: %zu\n", hashtable.numberOfPairs);
    if(hashtable.table!=NULL){
        for (size_t i = 0; i < hashtable.sizeTable; i++) {
            printf("%zu: ", i);
            printList(hashtable.table[i],0);
            printf("\n");
        }
    }
    else
        printf("NULL table\n");
    printf("---\n");
}
/**
 * Create a new hash table with the given size.
 *
 * @param sizeTable the size of the table
 * @return an empty hash table with the convenient table size
 */
HashTable hashtableCreate(size_t sizeTable) {
    HashTable hashtable;
    hashtable->sizeTable=sizeTable;
    hashtable->table=malloc(sizeof(List)*sizeTable);
    for(int i=0;i<sizeTable;i++){
        hashtable->table[i]=malloc(sizeof(list));
    }
    return hashtable;
}
/**
 * Insert a new key-value pair into the hash table but the insertion
 * is done without resizing the table. If the key is
 * already in the hash table, the old value is replaced
 * by the input value.
 *
 * @param hashtable pointer on the hash table to insert into.
 * @param key the key for the new pair
 * @param value the value for the new pair
 *
 * The pointer is supposed to be not null.
 * Note that since the fields of the hash table
 * will change, it is necessary to use
 * a pointer on the hash table.
 */
void hashtableInsertWithoutResizing(HashTable *hashtable, string key, int value){
    int indice=-1;
    int cell_number=0;
    Cell cell=malloc(sizeof(Cell));
    cell->key=NULL;
    while((strcmp(cell->key,key)==0)&&(indice<hashtable->sizeTable)){
        if(cell->nextCell!=NULL){
            cell=cell->nextCell;
            cell_number=cell_number+1;
        }else{
            indice=indice+1;
            cell=hashtable->table[i];
            cell_number=0;
        }
    }
    if(indice==hashtable->sizeTable){
        printf("ERROR! KEY NOT INCLUDED IN THE TABLE!");
        return;
    }
    hashtable->table[indice]=addKeyValueInList(hashtable->table[indice],key,value);
    return;
}


/**
 * Free the memory used by the given hash table (given with a pointer).
 * The fields sizeTable and numberOfPairs are set to 0.
 * The memory used by the table of lists is freed and
 * the table is set to NULL.
 * However, the memory to store the data structure is not freed.
 * It must be done outside the function.
 * @param hashtable hash table to free
 */
void hashtableDestroy(HashTable *hashtable) {
    for(int i=0;i<hashtable->sizeTable;i++){
        freeList(hashtable->table[i]);
    }
    free(hashtable->table);
    hashtable->sizeTable=0;
    hashtable->numberOfPairs=0;
    hashtable->table=NULL;
    return;
}

/**
 * Returns a new hash table whose table size is the double
 * of the input hashtable and that contains all the pairs
 * of the input hash table.
 *
 * @param hashtable input hash table
 * @return the new hash table with the same pairs but with a double size table
 *
 * The input  hash table is not removed from the memory
 */
HashTable hashtableDoubleSize(HashTable hashtable) {
    HashTable newHashtable;
    newHashtable->sizeTable=hashtable->sizeTable*2;
    newHashtable->table=malloc(sizeof(list)*newHashtable->sizeTable);
    newHashtable->numberOfPairs=hashtable->numberOfPairs;
    newHashtable->table=malloc(sizeof(hashtable->table)*2);
    for(int i=0;i<hashtable->sizeTable;i++){
        newHashtable->table[i]=malloc(sizeof(list));
        newHashtable->table[i]=hashtable->table[i];
    }
    return newHashtable;
}


/**
 * Insert a new key-value pair into the hash table. The table
 * has to be resized if necessary. If the key is
 * already in the hash table, the old value is replaced
 * by the input value.
 *
 * @param hashtable pointer on the hash table to insert into, supposed not to be null.
 * @param key the key for the new pair
 * @param value the value for the new pair
 *
 * Note that since the fields of the hash table
 * will change, it is necessary to use
 * a pointer on the hash table.
 *
 * Pay attention to the memory !
 */
void hashtableInsert(HashTable *hashtable, string key,  int value){
    int i=0;
    while((sizeof(hashtable->table[i])>=hashtable->numberOfPairs)&&(i<hashtable->sizeTable)){
        i=i+1;
    }
    if(i>=hashtable->sizeTable){
        hashtable->sizeTable=hashtable->sizeTable+1;
        hashtable->table=malloc(sizeof(list)*hashtable->sizeTable);
        hashtable->table[hashtable->sizeTable-1]=addKeyValueInList(hashtable->table[hashtable->sizeTable-1],key,value);
    }else{
        hashtable->table[i]=addKeyValueInList(hashtable->table[i],key,value);
    }
    return;
}

/**
 * Test if a key is in the hash table.
 * @param hashtable the hash table to search in
 * @param key the key to search for
 * @return 1 if the key is in the table, 0 otherwise.
 */
int hashtableHasKey(HashTable hashtable, string key){
    Cell cell=malloc(sizeof(Cell));
    for(int i=0;i<hashtable->sizeTable;i++){
        cell=hashtable->table[i];
        while(cell!=NULL){
            if(strcmp(cell->key,key)==0){
                free(cell);
                return(1);
            }
            cell=cell->nextCell;
        }
    }
    return 0;
}


/**
 * Get the value associated with the given key.
 * The key is supposed to be in the hash table.
 * @param hashtable the hash table to search in
 * @param key the key to search for
 * @return the value associated to the key
 */
int hashtableGetValue(HashTable hashtable, string key){
    int valeur;
    Cell cell=malloc(sizeof(Cell));
    for(int i=0;i<hashtable->sizeTable;i++){
        cell=hashtable->table[i];
        while(cell!=NULL){
            if(strcmp(cell->key,key)==0){
                valeur=cell->value;
                free(cell);
                return(valeur);
            }
            cell=cell->nextCell;
        }
    }
    return 0;
}


/**
 * Remove the key-value pair with the given key from the hash table.
 *
 *
 * @param hashtable the hash table to remove from
 * @param key the key of the pair to remove
 * @return 0 if the key was not in the hash table, 1 otherwise
 */
int hashtableRemove(HashTable *hashtable, string key){
    Cell cell=malloc(sizeof(Cell));
    for(int i=0;i<hashtable->sizeTable;i++){
        cell=hashtable->table[i];
        j=0;
        while(cell!=NULL){
            if(strcmp(cell->key,key)==0){
                cell=cell->nextCell;
                for(int k=0;k<j;k++){
                    Cell new_cell=malloc(sizeof(Cell));
                    strcpy(hashtable->table[i]->key,new_cell->key);
                    new_cell->value=hashtable->table[i]->value;
                    new_cell->nextCell=cell;
                    cell=new_cell;
                }
                hashtable->table[i]=cell;
                return(1)
            }
            j=j+1
            cell=cell->nextCell;
        }
    }
    return 0;
}


/**
 * Prints the number of words and distinct words in the file
 * "potter-clean.txt"
 *
 */
void countDistinctWordsInBook(){
    return;
}
