/**
 * @file list.c
 * @brief Implementation file for a linked list
 *
 * This file contains the implementation of the linked list data structure
 * and its associated functions.
 *
 * @author Loïck Lhote
 * @date February 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/**
 * @brief Creates a new linked list
 *
 * @return A pointer to the newly created linked list
 */
List newList() {
    return NULL;
}

/**
 * @brief Frees the memory used by a linked list
 *
 * @param L Pointer to the linked list to be freed
 */
void freeList(List L) {
    if (L==NULL){
        free(L);
    }else{
        if(L->nextCell==NULL){
            free(L->nextCell);
        }else{
            freeList(L->nextCell);
            free(L->nextCell);
        }
    }
    return;
}

/**
 * @brief Prints the contents of a linked list
 *
 * @param L Pointer to the linked list to be printed
 * @param type If type==0, prints only the values, otherwise print the couples (key,vlaue)
 *
 * Prints the linked list in the following way if k!=0:
 * [(key 1, value 1),(key 2, value 2), … ,(key k, value k)]
 * Prints the linked list in the following way if k==0:
 * [value 1,value 2,…,value k]
 */

void printList(List L, int type) {
    Cell *cell;
    if(L==NULL){
        printf("[]");
        return;
    }
    if(type==0){
        printf("[");
        printf("%d",L->value);
        cell=L->nextCell;
        while(cell!=NULL){
            printf(", ");
            printf(" %d",cell->value);
            cell=cell->nextCell;
        }
        printf("]");
    }else{
        printf("[(");
        printf("%s",L->key);
        printf(" ,");
        printf("%d",L->value);
        printf(" )");
        cell=L->nextCell;
        while(cell!=NULL){
            printf(" ,(");
            if(cell->key==NULL){
                printf("%s","NULL");
            }else{
                printf("%s",cell->key);
            }
            printf(" ,");
            printf("%d",cell->value);
            printf(" )");
            cell=cell->nextCell;
        }
        printf("]");
    }
    return;
}

/**
 * @brief Finds a key in a linked list
 *
 * @param L Pointer to the linked list to search in
 * @param key Key to search for
 *
 * @return A pointer to the first cell containing the key, or NULL if the key is not found
 */
Cell* findKeyInList(List L, string key) {
    Cell *c;
    if(L==NULL){
        return NULL;
    }
    c=L;
    if(key==NULL){
        while(c!=NULL){
            if(c->key==NULL){
                return(c);
            }
            c=c->nextCell;
        }
    }
    while(c!=NULL){
        if(c->key==NULL){
            c=c->nextCell;
        }else{
            if(strcmp(c->key,key)==0){
                return(c);
            }
            c=c->nextCell;
        }
    }
    /*free(c);*/
    return NULL;
}

/**
 * @brief Deletes a key from a linked list
 *
 * @param L Pointer to the linked list to search in
 * @param key Key to delete
 *
 * @return A pointer to the modified linked list
 * Only the first occurrence of the key is deleted.
 */
List delKeyInList(List L, string key) {
    List avant,apres;
    if(L==NULL){
        return NULL;
    }
    if(key==NULL){
        if(L->key==NULL){
            return(L->nextCell);
        }
    }else{
        if(strcmp(L->key,key)==0){
            return(L->nextCell);
        }
    }
    avant=malloc(sizeof(List));
    avant->key=malloc(sizeof(L->key));
    apres=malloc(sizeof(List));
    apres->key=malloc(sizeof(L->key));
    if(key==NULL){
        if(L->key==NULL){
            avant->key=L->key;
        }else{
            strcpy(avant->key,L->key);
        }
        avant->value=L->value;
        avant->nextCell=NULL;
        apres=L->nextCell;
        while((apres!=NULL)&&(apres->key!=NULL)){
            avant=addKeyValueInList(avant,apres->key,apres->value);
            apres=apres->nextCell;
        }
        if((apres!=NULL)&&(apres->key==NULL)){
            List temp;
            temp=malloc(sizeof(List));
            temp=apres->nextCell;
            /*free(apres);
            apres=malloc(sizeof(List));*/
            apres=temp;
            /*free(temp);*/
            while(apres!=NULL){
                avant=addKeyValueInList(avant,apres->key,apres->value);
                apres=apres->nextCell;
            }
            free(L);
            free(apres);
            return(avant);
        }else{
            free(avant);
            free(apres);
            return(L);
        }
    }else{
        if(L->key==NULL){
            avant->key=L->key;
        }else{
            avant->key=malloc(sizeof(L->key));
            apres->key=malloc(sizeof(L->key));
            strcpy(avant->key,L->key);
        }
        avant->value=L->value;
        avant->nextCell=NULL;
        apres=L->nextCell;
        while((apres!=NULL)&&(strcmp(apres->key,key)!=0)){
            avant=addKeyValueInList(avant,apres->key,apres->value);
            apres=apres->nextCell;
        }
        if((apres!=NULL)&&(strcmp(apres->key,key)==0)){
            List temp;
            temp=malloc(sizeof(List));
            temp=apres->nextCell;
            /*free(apres);
            apres=malloc(sizeof(List));*/
            apres=temp;
            /*free(temp);*/
            while(apres!=NULL){
                avant=addKeyValueInList(avant,apres->key,apres->value);
                apres=apres->nextCell;
            }
            free(L);
            free(apres);
            return(avant);
        }else{
            free(avant);
            free(apres);
            return(L);
        }
    }
    /*if(key==NULL){
        if(L->key!=NULL){
            delKeyInList(L->nextCell,key);
        }else{
            L=L->nextCell;
            return(L);
        }
    }else{
        if(L->key==NULL){
            delKeyInList(L->nextCell,key);
        }else{
            if(strcmp(L->key,key)!=0){
                delKeyInList(L->nextCell,key);
            }else{
                L=L->nextCell;
                return(L);
            }
        }
    }*/
    return NULL;
}

/**
 * @brief Adds a key-value pair to a linked list
 *
 * @param L Pointer to the linked list to add to
 * @param key Key to add
 * @param value Value to add
 *
 * @return A pointer to the modified linked list
 *
 * The key-value pair is added at the beginning of the list
 */

 List addKeyValueInList(List L, string key, int value) {
    Cell *c=L;
    Cell *new_cell;
    new_cell=malloc(sizeof(Cell));
    if(key==NULL){
        new_cell->key=NULL;
        new_cell->value=value;
        new_cell->nextCell=c;
        L=new_cell;
        return L;
    }
    new_cell->key=malloc(strlen(key));
    strcpy(new_cell->key,key);
    new_cell->value=value;
    new_cell->nextCell=c;
    L=new_cell;
    return L;
}


