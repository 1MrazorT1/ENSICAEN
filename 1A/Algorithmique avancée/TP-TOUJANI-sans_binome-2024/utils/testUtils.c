/**
 * \file global_test.c
 * \brief Test functions for BST
 * \author Loïck LHOTE
 * \version 0.1
 * \date janvier 2023
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"


/**
 * \fn void testUtils()
 * \brief Test all the functions declared in utils.h
 *
 */
void testUtils() {
    int array[] = {4, 3, 2, 1, 5};
    int n = 5;
    int permutation[100];

    // Use of qsort and intComparator
    qsort(array, n, sizeof(int), intComparator);
    // Affiche le tableau trié et la permutation générée
    printf("Tableau trié : ");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }

    // Use of uniformRandomPermutation
    uniformRandomPermutation(permutation, 100);
    printf("\nPermutation aléatoire uniforme: ");
    for (int i = 0; i < 100; i++) {
        printf("%d ", permutation[i]);
    }

    // Use of biaisedRandomPermutation
    biaisedRandomPermutation(permutation, 100);
    printf("\nPermutation aléatoire biaisée : ");
    for (int i = 0; i < 100; i++) {
        printf("%d ", permutation[i]);
    }

}



/**
 * \fn int main(void)
 * \brief Test all the functions of the practical work
 *declared in utils.h
 */
int main(void){
        srand(time(NULL));
        testUtils();
        return 0;
}
