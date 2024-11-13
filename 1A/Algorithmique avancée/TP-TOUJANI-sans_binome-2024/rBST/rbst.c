/**
 * \file rbst.c
 * \brief Implementation of the functions related to Randomized Binary Search Trees (RBST).
 * \author Loïck LHOTE
 * \version 0.1
 * \date janvier 2023
 *
 * Header file defining the data structure of a randomized binary search tree over integers and
 * declaring functions to manipulate them.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "rbst.h"

/**
 * @brief Create an empty binary search tree.
 * @return A pointer to the root of the new empty tree (NULL pointer).
 */
RBinarySearchTree createEmptyRBST(){
    return NULL;
}

/**
 * @brief Free the memory of a binary search tree.
 * @param tree Pointer to the root of the tree.
 */
void freeRBST(RBinarySearchTree tree){
    if(tree==NULL){
        return;
    }
    if(tree->rightRBST!=NULL){
        freeBST(tree->rightRBST);
    }else if(tree->leftRBST!=NULL){
        freeBST(tree->leftRBST);
    }else{
        free(tree);
    }
    return;
}

/**
 * @brief Compute the size of a randomized binary search tree.
 * @param tree Pointer to the root of the tree.
 * @return The number of nodes in the tree.
 */
int sizeOfRBST(RBinarySearchTree tree) {
    int size=0;
    if(tree==NULL){
        return size;
    }else{
        size = size + 1;
    }
    if((tree->leftRBST != NULL) || (tree->rightRBST != NULL)){
        if(sizeOfRBST(tree->leftRBST) > sizeOfRBST(tree->rightRBST)){
            size = size + sizeOfRBST(tree->leftRBST);
        }else{
            size = size + sizeOfRBST(tree->rightRBST);
        }
    }
    return size;
}

/**
 * @brief Split a randomized binary search tree into two parts according to a value.
 * @param tree The RBST to split.
 * @param value The value to split the tree on.
 * @param inf Pointer to a randomized BST that will store the final tree containing the elements strictly smaller than value.
 * @param sup Pointer to a randomized BST that will store the final tree containing the elements greater or equal to value.
 *
 * Split a randomized binary search tree into two parts according to a value.
 *
 * Be carful: the RBST tree is modified during the process but the inf and sub parts contain together
 * all the nodes of tree.
 */
void splitRBST(RBinarySearchTree tree, int value, RBinarySearchTree* inf, RBinarySearchTree* sup) {
    if(tree == NULL){
        *inf = createEmptyRBST();
        *sup = createEmptyRBST();
    }
    if(tree->value == value){
        *inf = tree->leftRBST;
        *sup = tree->rightRBST;
        tree->leftRBST = NULL;
        tree->rightRBST = NULL;
    }
    if(tree->value < value){
        *inf = tree;
        splitRBST(tree->rightRBST, value, &((*inf)->rightRBST), sup);
    }
    if(tree->value > value){
        *sup = tree;
        splitRBST(tree->leftRBST, value, inf, &((*sup)->leftRBST));
    }
}

/**
 * @brief Insert a value at the root of a randomized binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to insert.
 * @return A pointer to the root of the modified tree.
 */
RBinarySearchTree insertAtRoot(RBinarySearchTree tree, int value) {
    if(tree == NULL){
        RBinarySearchTree *res = createEmptyRBST();
        *res->value = value;
        *res->leftRBST = NULL;
        *res->rightRBST = NULL;
        *res->size = 1;
        return *res;
    }
    if(((double)rand() / RAND_MAX) == (1/(sizeOfRBST(tree) + 1))){
        RBinarySearchTree *inf, *sup;
        *inf = createEmptyRBST();
        *sup = createEmptyRBST();
        splitRBST(tree, value, inf, sup);
        RBinarySearchTree *res = createEmptyRBST();
        *res->leftRBST = *inf;
        *res->rightRBST = *sup;
        return *res;
    }else{
        if(tree->value < value){
            insertAtRoot(tree->rightRBST, value);
        }else if(tree->value > value){
            insertAtRoot(tree->leftRBST, value);
        }else if(tree->value == value){
            insertAtRoot(tree, value);
        }
    }
}


/**
 * @brief Add a value to a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to add.
 * @return A pointer to the root of the modified tree.
 */
RBinarySearchTree addToRBST(RBinarySearchTree tree, int value){
    if(tree == NULL){
        RBinarySearchTree *res = createEmptyRBST();
        *res->value = value;
        *res->leftRBST = NULL;
        *res->rightRBST = NULL;
        *res->size = 1;
        return *res;
    }
    if(tree->value < value){
        insertAtRoot(tree->rightRBST, value);
    }else if(tree->value > value){
        insertAtRoot(tree->leftRBST, value);
    }else if(tree->value == value){
        insertAtRoot(tree, value);
    }
    return NULL;
}


/**
 * @brief Compute the height of a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @return The height of the tree.
 */
int heightRBST(RBinarySearchTree tree) {
    if(tree == NULL){
        return(-1);
    }else{
        int leftHeight = 0;
        int rightHeight = 0;
        leftHeight = leftHeight + height(tree->leftRBST);
        rightHeight = rightHeight + height(tree->rightRBST);
        if(rightHeight > leftHeight){
            return(rightHeight + 1);
        }else{
            return(leftHeight + 1);
        }
    }
}

/**
 * @brief Search for a value in a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to search for.
 * @return A pointer to the node containing the value, or NULL if the value is not in the tree.
 */
RBinarySearchTree searchRBST(RBinarySearchTree tree, int value){
    if(tree == NULL){
        return NULL;
    }else if(tree->value == value){
        return(tree);
    }else if(tree->value < value){
        return searchBST(tree->rightRBST, value);
    }
    return searchBST(tree->leftRBST, value);
    return NULL;
}

/**
 * @brief Build a randomized binary search tree from a given permutation.
 * @param permutation Array of integers representing the permutation
 * @param n size of the array
 * @return A random binary such tree built by successively inserting the elements of permutation.
 */
RBinarySearchTree buildRBSTFromPermutation(int *permutation,size_t n) {
    RBinarySearchTree tree=createEmptyRBST();
    for(int i=0; i<n; i++){
        tree=addToRBST(tree, permutation[i]);
    }
    return tree;
}

/**
 * @brief Print the elements of a binary search tree in a pretty format.
 * @param tree Pointer to the root of the tree.
 * @param space Space to be printed before the current element.
 */
void prettyPrintRBST(RBinarySearchTree tree, int space) {
    if (tree == NULL) {
        return;
    }
    space += 10;

    prettyPrintRBST(tree->rightRBST, space);

    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("[%d,%d]\n", tree->value, tree->size);

    prettyPrintRBST(tree->leftRBST, space);
    return ;
}
