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
#include "../bst/bst.h"
#include "rbst.h"



/**
 * \fn void testRbst()
 * \brief Test all the functions declared in rbst.h
 *
 */
void testRBst(){
    // Create an example RBST
    // Test addToRBST and prettyPrintRBST
    RBinarySearchTree tree = createEmptyRBST();
    printf("Empty tree\n");
    prettyPrintRBST(tree,4);
    printf("add 1\n");
    tree = addToRBST(tree, 1);
    prettyPrintRBST(tree,4);
    printf("add 2\n");
    tree = addToRBST(tree, 2);
    prettyPrintRBST(tree,4);
    printf("add 3\n");
    tree = addToRBST(tree, 3);
    prettyPrintRBST(tree,4);
    printf("add 4\n");
    tree = addToRBST(tree, 4);
    prettyPrintRBST(tree,4);
    printf("add 5\n");
    tree = addToRBST(tree, 5);
    prettyPrintRBST(tree,4);
    printf("add 6\n");
    tree = addToRBST(tree, 6);
    prettyPrintRBST(tree,4);
    printf("add 7\n");
    tree = addToRBST(tree, 7);
    prettyPrintRBST(tree,4);

    // Test searchRBST()
    printf("*************************\n");
    RBinarySearchTree searchResult = searchRBST(tree, 2);
    if (searchResult == NULL)
        printf("2 has not been found...");
    else if (searchResult->value ==2)
        printf("2 has been found !");
    else
        printf("Something is wrong!");
    printf("\n");

    searchResult = searchRBST(tree, 16);
    if (searchResult == NULL)
        printf("16 has not been found...");
    else if (searchResult->value ==16)
        printf("16 has been found !");
    else
        printf("Something is wrong!");
    printf("\n");

    printf("*************************\n");
    printf("The height of the tree is %d.",heightRBST(tree));
    printf("\n");

    // Split the RBST according to the value 4
    RBinarySearchTree inf, sup;
    /*
    splitRBST(tree, 4, &inf, &sup);

    printf("*************************\n");
    // Print the elements of the INF tree
    printf("Split tree with respect to 4:");
    printf("Inf tree: ");
    prettyPrintRBST(inf,4);
    printf("\n");
    // Print the elements of the SUP tree
    printf("Sup tree: ");
    prettyPrintRBST(sup,4);
    printf("\n");
    printf("*************************\n");
    */

    int permutation[]={0,1,2,3,4,5,6,7,8,9};
    RBinarySearchTree tree2 = buildRBSTFromPermutation(permutation,10);
    printf("Buit with a permutation");
    prettyPrintRBST(tree2,4);

    // free memory
    freeRBST(inf);
    freeRBST(sup);
    free(tree2);

}


/**
 * \fn void compare_bst_rbst()
 * \brief This function computes the average behaviour of the BST and RBST uniform permutations and non-uniform permutations.
 *
 * This function computes the average behaviour of the BST and RBST
 * when the tree are random generated with uniform permutations and
 * non-uniform ones.
 *
 * The average time to build the trees, the average height of the obtained trees
 * and the average time to search for an element are computed and display in the
 * 4 situations (BST/RBST and uniform/non uniform).
 */
void compare_bst_rbst(int size, int nbTests){
    clock_t start, stop;
    clock_t  timeBuild=0, timeResearch=0;
    int valueHeight=0;

    printf("\nComparison between the data structures\n");
    printf("size of the permutations: %d\n", size);
    printf("number of tests: %d\n", nbTests);

    int permutation[size];

    BinarySearchTree bst = NULL;
    RBinarySearchTree rbst = NULL;

    for(int typeTree=0; typeTree<2; typeTree++){
        //typeTree=0 => BST
        //typeTree=1 => RBST
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
                if(typeTree==0)
                    bst = buildBSTFromPermutation(permutation,size);
                else
                    rbst = buildRBSTFromPermutation(permutation,size);
                stop = clock();
                timeBuild += stop-start;
                //measure of the height of the tree
                if(typeTree==0)
                    valueHeight += heightBST(bst);
                else
                    valueHeight += heightRBST(rbst);
                //Average complexity of a search using 1000 searches
                start = clock();
                for(int j=0; j<1000; j++){
                    int valueToFind = rand()%size;
                    if(typeTree==0)
                        searchBST(bst,valueToFind);
                    else
                        searchRBST(rbst,valueToFind);
                }
                stop = clock();
                timeResearch += stop-start;
                // Free the memory
                freeBST(bst);
                bst=NULL;
                freeRBST(rbst);
                rbst=NULL;
            }
            // Display the results in the console
            if(typeTree==0)
                printf("Binary search tree ");
            else
                printf("Randomized binary search tree ");
            if(random == 0)
                printf("with uniform distribution:\n");
            else
                printf("with non uniform distribution:\n");
            printf("  -> The average time to build is : %lf \n", (double) timeBuild / nbTests);
            printf("  -> The average height is : %lf\n", (double) valueHeight / nbTests);
            printf("  -> The average time to perform searches is : %lf\n", (double) timeResearch / nbTests);

        }

    }

}


/**
 * \fn draw_graph_rbst()
 * \brief This function computes the average behaviour of the BST and RBST with uniform permutations and non-uniform permutations.
 *
 * This function computes the average behaviour of the BST and RBST
 * when the tree are generated with uniform permutations and
 * non-uniform ones.
 *
 * The average time to build the trees, the average height of the obtained trees
 * and the average time to search for an element are computed and stored in
 * the file data.gnuplot for the various sizes display in the
 * 4 situations (bst/rbst, uniform/non uniform).
 */
void draw_graph_rbst(int begin_size, int end_size, int step_size, int nbTests){
    clock_t start, stop;
    clock_t  timeBuild=0, timeResearch=0;
    int valueHeight=0;

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
        BinarySearchTree bst = NULL;
        RBinarySearchTree rbst = NULL;

        for(int typeTree=0; typeTree<2; typeTree++){
            //typeTree=0 => BST
            //typeTree=1 => RBST
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
                    if(typeTree==0)
                        bst = buildBSTFromPermutation(permutation,size);
                    else
                        rbst = buildRBSTFromPermutation(permutation,size);
                    stop = clock();
                    timeBuild += stop-start;
                    //measure of the height of the tree
                    if(typeTree==0)
                        valueHeight += heightBST(bst);
                    else
                        valueHeight += heightRBST(rbst);
                    //Average complexity of a search using 1000 searches
                    start = clock();
                    for(int j=0; j<1000; j++){
                        int valueToFind = rand()%size;
                        if(typeTree==0)
                            searchBST(bst,valueToFind);
                        else
                            searchRBST(rbst,valueToFind);
                    }
                    stop = clock();
                    timeResearch += stop-start;
                    // Free the memory
                    freeBST(bst);
                    bst=NULL;
                    freeRBST(rbst);
                    rbst=NULL;
                }
                fprintf(inputFile, " %.2lf %.2lf %.2lf ",(double) timeBuild / nbTests,(double) valueHeight / nbTests,(double) timeResearch / nbTests );
            }

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
        testRBst();
        compare_bst_rbst(1000, 1000);
        //draw_graph_rbst(1000,10000,500,1000);
        return 0;
}
