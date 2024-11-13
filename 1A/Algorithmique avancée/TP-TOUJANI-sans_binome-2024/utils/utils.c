/**
 * \file utils.c
 * \brief Functions that are useful for the practical work on BST.
 * \author Loïck LHOTE
 * \version 0.1
 * \date janvier 2023
 *
 * Source code of the functions declared in utils.h
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "utils.h"

/**
 * \fn int intComparator ( const void * first, const void * second )
 * \brief Necessary function for qsort to compare integers.
 * \param first pointer to the first integer to compare
 * \param second pointer to the second integer to compare
 * \return the difference first-second.
 *
 */
int intComparator ( const void * first, const void * second ) {
    int firstInt = * (const int *) first;
    int secondInt = * (const int *) second;
    return firstInt - secondInt;
}


/**
 * \fn void uniformRandomPermutation(int *permutation, size_t n )
 * \brief Generate a random uniform permutation of {0,1,..,n-1}.
 * \param permutation
 * \parblock
 * Array of n integers, already allocated. The array is modified
 * so  that at the end, it constains all the integers over {0,...n-1},
 * each of tem only once.
 * \endparblock
 * \param n The size of the permutation (over {0,...,n-1}).
 *
 * Warning: the function srand must be called before using this function.
 */
void uniformRandomPermutation(int *permutation, size_t n ){
    // Initialize permutation
    for (size_t i = 0; i < n; i++)
        permutation[i]=(int) i;
    // Iterate through the array
    for (size_t i = 0; i < n - 1; i++) {
        // Generate a random index between i and n-1
        size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
        // Swap the current element with the element at the random index
        int t = permutation[j];
        permutation[j] = permutation[i];
        permutation[i] = t;
    }
}

/**
 * \fn void biaisedRandomPermutation(int *permutation, size_t n )
 * \brief Generate a biaised random permutation of {0,1,..,n-1}.
 * \param permutation
 * \parblock
 * Array of n integers, already allocated. The array is modified
 * so  that at the end, it constains all the integers over {0,...n-1},
 * each of tem only once.
 * \endparblock
 * \param n The size of the permutation (over {0,...,n-1}).
 *
 * Generate a biaised random permutation of {0,1,..,n-1} in the
 * following way: a uniform random permutation if first generated and
 * then, the first q=n/10 elements are sorted.
 *
 * Warning: the function srand must be called before using this function.
 */
void biaisedRandomPermutation(int *permutation, size_t n ){
    uniformRandomPermutation(permutation,n);
    int nDiv10 = n/10;
    qsort(permutation,nDiv10,sizeof(int),intComparator);
}



