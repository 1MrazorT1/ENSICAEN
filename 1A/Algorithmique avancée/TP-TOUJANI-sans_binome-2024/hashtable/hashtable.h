/**
 * @file hashtable.h
 * @brief Header file for a hash table implementation  based on linked list
 *
 * This file contains the declaration of the hash table data structure
 * and its associated functions.
 *
 * @author Loïck Lhote
 * @date march 2023
 */


#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include "../list/list.h"

/**
 * @brief Definition of a hash table data structure
 *
 * The structure contains the size of the table of list [sizeTable], the number of pairs
 * (key,value)  stored in the hash table [numberOfPairs], dans
 * the table of List of pairs [table].
 */
typedef struct hashtable{
    size_t sizeTable;
    size_t numberOfPairs;
    List *table;
} HashTable;

/**
 * @brief Hash function murmurhash
 *
 * @param key string representing the key to hash
 * @param sizeKey length of the string key
 * @param maxValue maximum value (excluded) that must return the hash function
 * @return the hash code of the kez between 0 and maxValue-1
 */
size_t murmurhash(string key, size_t sizeKey, size_t maxValue);


/**
 * Create a new hash table with the given size.
 *
 * @param sizeTable the size of the table
 * @return an empty hash table with the convenient table size
 */
HashTable hashtableCreate(size_t sizeTable);

/**
 * Free the memory used by the input hash table (given with a pointer).
 * The fields sizeTable and numberOfPairs are set to 0.
 * The memory used by the table of lists is freed and
 * the table is set to NULL.
 * However, the memory to store the data structure is not freed.
 * It must be done outside the function.
 * @param hashtable hash table to free
 */
void hashtableDestroy(HashTable *hashtable);


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
void hashtableInsertWithoutResizing(HashTable *hashtable, string key, int value);


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
HashTable hashtableDoubleSize(HashTable hashtable);


/**
 * Insert a new key-value pair into the hash table. The table
 * has to be resized if necessary. If the key is
 * already in the hash table, the old value is replaced
 * by the input value.
 *
 * @param hashtable pointer on the hash table to insert into.
 * @param key the key for the new pair
 * @param value the value for the new pair
 *
 * Note that since the fields of the hash table
 * will change, it is necessary to use
 * a pointer on the hash table.
 *
 * Pay attention to the memory !
 */
void hashtableInsert(HashTable *hashtable, string key,  int value);

/**
 * Test if a key is in the hash table.
 * @param hashtable the hash table to search in, supposed to be non null
 * @param key the key to search for
 * @return 1 if the key is in the table, 0 otherwise.
 */
int hashtableHasKey(HashTable hashtable, string key);


/**
 * Get the value associated with the given key.
 * The key is supposed to be in the hash table.
 * @param hashtable the hash table to search in
 * @param key the key to search for
 * @return the value associated to the key
 */
int hashtableGetValue(HashTable hashtable, string key);


/**
 * Remove the key-value pair with the given key from the hash table.
 *
 *
 * @param hashtable the hash table to remove from
 * @param key the key of the pair to remove
 * @return 0 if the key was not in the hash table, 1 otherwise
 */
int hashtableRemove(HashTable *hashtable, string key);

/**
 * @brief Prints the contents of a hash table
 *
 * @param hashtable Hash table to be printed
 */
void hashtablePrint(HashTable hashtable) ;

/**
 * Prints the number of words and distinct words in the file
 * "potter-clean.txt"
 *
 */
void countDistinctWordsInBook();

#endif // HASHTABLE_H_INCLUDED
