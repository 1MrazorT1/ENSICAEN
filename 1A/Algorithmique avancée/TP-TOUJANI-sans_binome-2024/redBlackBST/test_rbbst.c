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
#include "../rBST/rbst.h"
#include "redBlackBST.h"
#include "assert.h"


/**
 * \fn void testRedBlackBST()
 * \brief Test all the functions declared in redBlackBST.h
 *
 */
void testRedBlackBST(){

  // Test createEmptyRedBlackBST()
  RedBlackBST tree = createEmptyRedBlackBST();
  printf("tree == NULL : %d\n",tree == NULL);

  // Test insertNodeRedBlackBST() and heightRedBlackBST()
  int size=10;
  int values[size];
  uniformRandomPermutation(values,size);
  for (int i = 0; i < size; i++) printf("%d ",values[i]);
  printf("-----");
  for (int i = 0; i < size; i++) {
    printf("insert %d\n",values[i]);
    insertNodeRedBlackBST(&tree, values[i]);
    prettyPrintRedBlackBST(tree, 0);
    printf("-------\n");
  }
  printf("hauteur = %d\n", heightRedBlackBST(tree));
  // Test searchRedBlackBST()
  printf("searchRedBlackBST(tree, 7) != NULL : %d\n",searchRedBlackBST(tree, 7) != NULL);
  printf("searchRedBlackBST(tree, %d) != NULL : %d\n",size+1,searchRedBlackBST(tree, size+1) != NULL);

  // Test isRedBlackBST()
  printf("isRedBlackBST(tree) == 1 : %d\n",isRedBlackBST(tree) == 1);


  // Test freeRedBlackBST()
  freeRedBlackBST(tree);

}









/**
 * \fn void compare_data_structures()
 * \brief This function computes the average behaviour of the BST, RBST and red-black BST on uniform permutations and non-uniform permutations.
 *
 * This function computes the average behaviour of the BST, RBST and red-black BST
 * when the trees are randomly generated with uniform permutations and
 * non-uniform ones.
 *
 * The average time to build the trees, the average height of the obtained trees
 * and the average time to search for an element are computed and display in the
 * 6 situations (BST/RBST/red-black BST and uniform/non uniform).
 */
void compare_data_structures(int size, int nbTests){
    clock_t start, stop;
    clock_t  timeBuild=0, timeResearch=0;
    int valueHeight=0;

    printf("\nComparison between the data structures\n");
    printf("size of the permutations: %d\n", size);
    printf("number of tests: %d\n", nbTests);

    int permutation[size];

    BinarySearchTree bst = NULL;
    RBinarySearchTree rbst = NULL;
    RedBlackBST redBlackBst = NULL;

    for(int typeTree=0; typeTree<3; typeTree++){
        //typeTree=0 => BST
        //typeTree=1 => RBST
        //typeTree=2 => Red-Black tree
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
                else if(typeTree==1)
                    rbst = buildRBSTFromPermutation(permutation,size);
                else
                    redBlackBst = buildRedBlackBSTFromPermutation(permutation,size);
                stop = clock();
                timeBuild += stop-start;
                //measure of the height of the tree
                if(typeTree==0)
                    valueHeight += heightBST(bst);
                else if(typeTree==1)
                    valueHeight += heightRBST(rbst);
                else
                    valueHeight += heightRedBlackBST(redBlackBst);

                //Average complexity of a search using 1000 searches
                start = clock();
                for(int j=0; j<1000; j++){
                    int valueToFind = rand()%size;
                    if(typeTree==0)
                        searchBST(bst,valueToFind);
                    else if(typeTree==1)
                        searchRBST(rbst,valueToFind);
                    else
                        searchRedBlackBST(redBlackBst,valueToFind);
                }
                stop = clock();
                timeResearch += stop-start;

                // Free the memory
                freeBST(bst);
                bst=NULL;
                freeRBST(rbst);
                rbst=NULL;
                freeRedBlackBST(redBlackBst);
                redBlackBst=NULL;
            }
            // Display the results in the console
            if(typeTree==0)
                printf("Binary search tree ");
            else if (typeTree==1)
                printf("Randomized binary search tree ");
            else
                printf("Red-Black tree ");
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
 * \fn draw_graph_trees()
 * \brief This function computes the average behaviour of the BST, RBST and red-black BST with uniform permutations and non-uniform permutations.
 *
 * This function computes the average behaviour of the BST, RBST and red-black BST
 * when the trees are generated with uniform permutations and
 * non-uniform ones.
 *
 * The average time to build the trees, the average height of the obtained trees
 * and the average time to search for an element are computed and stored in
 * the file data.gnuplot for the various sizes display in the
 * 6 situations (bst/rbst/red-black BST, uniform/non uniform).
 */
void draw_graph_trees(int begin_size, int end_size, int step_size, int nbTests){
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
        RedBlackBST rbbst = NULL;

        for(int typeTree=0; typeTree<3; typeTree++){
            //typeTree=0 => BST
            //typeTree=1 => RBST
            //typetree=3 => red-black BST
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
                    switch(typeTree){
                        case 0 : bst = buildBSTFromPermutation(permutation,size); break;
                        case 1 : rbst = buildRBSTFromPermutation(permutation,size); break;
                        case 2 : rbbst = buildRedBlackBSTFromPermutation(permutation,size); break;
                    }
                    stop = clock();
                    timeBuild += stop-start;
                    //measure of the height of the tree
                    switch(typeTree){
                        case 0 : valueHeight += heightBST(bst); break;
                        case 1 : valueHeight += heightRBST(rbst); break;
                        case 2 : valueHeight += heightRedBlackBST(rbbst); break;
                    }
                    //Average complexity of a search using 1000 searches
                    start = clock();
                    for(int j=0; j<1000; j++){
                        int valueToFind = rand()%size;
                        switch(typeTree){
                            case 0 : searchBST(bst,valueToFind); break;
                            case 1 : searchRBST(rbst,valueToFind); break;
                            case 2 : searchRedBlackBST(rbbst,valueToFind); break;
                        }
                    }
                    stop = clock();
                    timeResearch += stop-start;
                    // Free the memory
                    freeBST(bst);
                    bst=NULL;
                    freeRBST(rbst);
                    rbst=NULL;
                    freeRedBlackBST(rbbst);
                    rbbst = NULL;
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
        testRedBlackBST();
        //compare_data_structures(5000, 1000);
        draw_graph_trees(1000,10000,500,1000);
        return 0;
}
