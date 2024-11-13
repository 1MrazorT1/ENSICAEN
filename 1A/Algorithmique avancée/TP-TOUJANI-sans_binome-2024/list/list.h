/**
 * @file list.h
 * @brief Header file for a linked list implementation
 *
 * This file contains the declaration of the linked list data structure
 * and its associated functions.
 *
 * @author Loïck Lhote
 * @date February 2023
 */

#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

/**
 * @brief Definition of the type string
 *
 */
typedef char *string;

/**
 * @brief Definition of a linked list cell and a linked list
 *
 * The structure contains the key (a string), the value (an integer),
 * and a pointer to the next cell in the list.
 * A linked list is just a pointer on the first cell (if it exists).
 */
typedef struct cell{
    string key; /**< Key of the cell */
    int value; /**< Value of the cell */
    struct cell *nextCell; /**< Pointer to the next cell in the list */
} Cell, *List;


/**
 * @brief Creates a new empty linked list
 *
 * @return A NULL pointer corresponding to the newly created linked list
 */
List newList();

/**
 * @brief Frees the memory used by a linked list
 *
 * @param L Pointer to the linked list to be freed
 */
void freeList(List L);


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

void printList(List L,int type);

/**
 * @brief Finds a key in a linked list
 *
 * @param L Pointer to the linked list to search in
 * @param key Key to search for
 *
 * @return A pointer to the first cell containing the key, or NULL if the key is not found
 */
Cell* findKeyInList(List L, string key);

/**
 * @brief Deletes a key from a linked list
 *
 * @param L Pointer to the linked list to search in
 * @param key Key to delete
 *
 * @return A pointer to the modified linked list
 *
 * Only the first occurrence of the key is deleted.
 */
List delKeyInList(List L, string key);

/**
 * @brief Adds a key-value pair to a linked list
 *
 * @param L Pointer to the linked list to add to
 * @param key Key to add
 * @param value Value to add
 *
 * @return A pointer to the modified linked list
 */
List addKeyValueInList(List L, string key, int value);


#endif
/* LIST_H_INCLUDED */
