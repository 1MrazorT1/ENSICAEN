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
#include "../utils/utils.h"
#include "bst.h"



/**
 * \fn void testBst()
 * \brief Test all the functions declared in bst.h
 *
 */
void testBst() {
    printf("************************\n");
    // create an empty tree
    BinarySearchTree bst = createEmptyBST();
    prettyPrintBST(bst,4);
    printf("************************\n");

    // add elements to the tree
    bst = addToBST(bst, 5);
    bst = addToBST(bst, 3);
    bst = addToBST(bst, 2);
    bst = addToBST(bst, 4);
    bst = addToBST(bst, 7);
    bst = addToBST(bst, 6);
    bst = addToBST(bst, 8);
    prettyPrintBST(bst,4);
    printf("************************\n");

    // Test searchBST()
    printf("*************************\n");
    BinarySearchTree searchResult = searchBST(bst, 2);
    if (searchResult == NULL)
        printf("2 has not been found...");
    else if (searchResult->value ==2)
        printf("2 has been found !");
    else
        printf("Something is wrong!");
    printf("\n");

    searchResult = searchBST(bst, 16);
    if (searchResult == NULL)
        printf("16 has not been found...");
    else if (searchResult->value ==16)
        printf("16 has been found !");
    else
        printf("Something is wrong!");
    printf("\n");

    //Test height
    printf("*************************\n");
    printf("The height of the tree is %d.",heightBST(bst));
    printf("\n");


    printf("************************\n");

    // delete the root of the tree
    bst = deleteRootBST(bst);
    prettyPrintBST(bst,4);
    printf("************************\n");


    // delete a value from the tree
    bst = deleteFromBST(bst, 6);
    prettyPrintBST(bst,4);
    printf("************************\n");


    // free the memory of the tree
    freeBST(bst);

    //test the generation of a tree using a permutation
    int permutation[] = {3,2,4,6,9,7,8,0,1,5};
    bst = buildBSTFromPermutation(permutation,10);
    prettyPrintBST(bst,4);
    printf("************************\n");

    // free the memory of the tree
    freeBST(bst);


}



/**
 * \fn void compare_data_structures()
 * \brief This function computes the average behaviour of the BST with uniform permutations and non-uniform permutations.
 *
 * This function computes the average behaviour of the BST
 * when the tree are generated with uniform permutations and
 * non-uniform ones.
 *
 * The average time to build the trees, the average height of the obtained trees
 * and the average time to search for an element are computed and display in the
 * 2 situations (uniform/non uniform).
 */
void compare_bst(int size, int nbTests){
    clock_t start, stop;
    clock_t  timeBuild=0, timeResearch=0;
    int valueHeight=0;

    printf("\nComparison between the data structures\n");
    printf("size of the permutations: %d\n", size);
    printf("number of tests: %d\n", nbTests);

    int permutation[size];

    BinarySearchTree bst = NULL;

        for(int random=0; random<2;random++){
            //random=0 => uniform
            //random=1 => biaised
            timeBuild =0;
            timeResearch = 0;
            valueHeight =0;
            for(int i=0; i<nbTests;i++){
                // generation of the permutation
                if(random == 0)
                    uniformRandomPermutation(permutation,size);
                else
                    biaisedRandomPermutation(permutation,size);
                //measure of the time to buid the tree
                start = clock();
                bst = buildBSTFromPermutation(permutation,size);
                stop = clock();
                timeBuild += stop-start;
                //measure of the height of the tree
                valueHeight += heightBST(bst);
                //Average complexity of a search using 1000 searches
                start = clock();
                for(int j=0; j<1000; j++){
                    int valueToFind = rand()%size;
                    searchBST(bst,valueToFind);
                }
                stop = clock();
                timeResearch += stop-start;
                // Free the memory
                freeBST(bst);
                bst=NULL;
            }
            // Display the results in the console
            printf("Binary search tree ");
            if(random == 0)
                printf("with uniform distribution:\n");
            else
                printf("with non uniform distribution:\n");
            printf("  -> The average time to build is : %lf \n", (double) timeBuild / nbTests);
            printf("  -> The average height is : %lf\n", (double) valueHeight / nbTests);
            printf("  -> The average time to perform searches is : %lf\n", (double) timeResearch / nbTests);

        }


}


/**
 * \fn draw_graph_bst()
 * \brief This function computes the average behaviour of the BST with uniform permutations and non-uniform permutations.
 *
 * This function computes the average behaviour of the BST
 * when the tree are generated with uniform permutations and
 * non-uniform ones.
 *
 * The average time to build the trees, the average height of the obtained trees
 * and the average time to search for an element are computed and stored in
 * the file data.gnuplot for the various sizes display in the
 * 2 situations (uniform/non uniform).
 */
void draw_graph_bst(int begin_size, int end_size, int step_size, int nbTests){
    clock_t start, stop;
    clock_t  timeBuild=0, timeResearch=0;
    int valueHeight=0;


    BinarySearchTree bst = NULL;

    FILE * inputFile;
    inputFile = fopen( "data.gnuplot", "w" );
    if ( inputFile == NULL ) {
        printf( "Cannot open file %s\n", "data.gnuplot" );
        exit( 0 );
    }
    printf("beginning graph....\n");
    for(int size = begin_size;size <= end_size;size+=step_size){
        int permutation[size];
        fprintf(inputFile,"%d",size);
        for(int random=0; random<2;random++){
            //random=0 => uniform
            //random=1 => biaised
            timeBuild =0;
            timeResearch = 0;
            valueHeight =0;
            for(int i=0; i<nbTests;i++){
                // generation of the permutation
                if(random == 0)
                    uniformRandomPermutation(permutation,size);
                else
                    biaisedRandomPermutation(permutation,size);
                //measure of the time to buid the tree
                start = clock();
                bst = buildBSTFromPermutation(permutation,size);
                stop = clock();
                timeBuild += stop-start;
                //measure of the height of the tree
                valueHeight += heightBST(bst);
                //Average complexity of a search using 1000 searches
                start = clock();
                for(int j=0; j<1000; j++){
                    int valueToFind = rand()%size;
                    searchBST(bst,valueToFind);
                }
                stop = clock();
                timeResearch += stop-start;
                // Free the memory
                freeBST(bst);
                bst=NULL;
            }
            fprintf(inputFile, " %.2lf %.2lf %.2lf ",(double) timeBuild / nbTests,(double) valueHeight / nbTests,(double) timeResearch / nbTests );
        }
        fprintf(inputFile,"\n");
    }
    fclose(inputFile);
}



/**
 * \fn int main(void)
 * \brief Test all the functions of the practical work
 *declared in utils.h
 */
int main(void){
        srand(time(NULL));
        testBst();
        //uncomment when necessary
        //compare_bst(1000,1000);
        //draw_graph_bst(1000,20000,1000,1000);
        return 0;
}
