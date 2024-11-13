/**
 * \file utils.h
 * \brief Functions that are useful for the practical work on BST.
 * \author Loïck LHOTE
 * \version 0.1
 * \date janvier 2023
 *
 * Header file that declares functions that are useful for completing the practical
 * work on binary search tree.
 */


#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stdlib.h>



/**
 * \fn int intComparator ( const void * first, const void * second )
 * \brief Necessary function for qsort to compare integers.
 * \param first pointer to the first integer to compare
 * \param second pointer to the second integer to compare
 * \return the difference first-second.
 *
 */
int intComparator ( const void * first, const void * second );


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
 *
 */
void uniformRandomPermutation(int *permutation, size_t n );

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
void biaisedRandomPermutation(int *permutation, size_t n );


#endif // UTILS_H_INCLUDED
