/**
 * \file bst.c
 * \brief Implementation of classical functions for BST
 * \author Loïck LHOTE
 * \version 0.1
 * \date janvier 2023
 *
 * Source code of the functions declared in bst.h.
 * Thes functions are to manipulate binary search trees.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "bst.h"


/**
 * @brief Create an empty binary search tree.
 * @return A pointer to the root of the new empty tree (NULL pointer).
 */
BinarySearchTree createEmptyBST() {
    return NULL;
}

/**
 * @brief Free the memory of a binary search tree.
 * @param tree Pointer to the root of the tree.
 */
void freeBST(BinarySearchTree tree) {
    if(tree==NULL){
        return;
    }
    if(tree->rightBST!=NULL){
        freeBST(tree->rightBST);
    }else if(tree->leftBST!=NULL){
        freeBST(tree->leftBST);
    }else{
        free(tree);
    }
    return;
}


/**
 * @brief Add a value to a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to add.
 * @return A pointer to the root of the modified tree.
 */
BinarySearchTree addToBST(BinarySearchTree tree, int value) {
    if(tree==NULL){
        BinarySearchTree branch = createEmptyBST();
        branch->value=value;
        branch->leftBST=NULL;
        branch->rightBST=NULL;
        return(branch);
    }
    if(tree->value<value){
        tree->rightBST=addToBST(tree->rightBST,value);
    }
    if(tree->value>value){
        tree->leftBST=addToBST(tree->leftBST,value);
    }
    return tree;
}


/**
 * @brief Compute the height of a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @return The height of the tree.
 */
int heightBST(BinarySearchTree tree) {
    if(tree==NULL){
        return(-1);
    }else{
        int leftHeight=0;
        int rightHeight=0;
        leftHeight=leftHeight + heightBST(tree->leftBST);
        rightHeight=rightHeight + heightBST(tree->rightBST);
        if(rightHeight > leftHeight){
            return(rightHeight+1);
        }else{
            return(leftHeight+1);
        }
    }
}

/**
 * @brief Search for a value in a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to search for.
 * @return A pointer to the node containing the value, or NULL if the value is not in the tree.
 */
BinarySearchTree searchBST(BinarySearchTree tree, int value) {
    if(tree==NULL){
        return NULL;
    }else if(tree->value==value){
        return(tree);
    }else if(tree->value < value){
        return searchBST(tree->rightBST, value);
    }
    return searchBST(tree->leftBST, value);
}


/**
 * @brief Delete the root of a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @return A pointer to the root of the modified tree.
 */
BinarySearchTree deleteRootBST(BinarySearchTree tree) {
    return deleteFromBST(tree,tree->value);
}


/**
 * @brief Delete a value from a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to delete.
 * @return A pointer to the root of the modified tree.
 */
BinarySearchTree deleteFromBST(BinarySearchTree tree, int value) {
    if(tree==NULL){
        return tree;
    }
    if(tree->value < value){
        tree->rightBST=deleteFromBST(tree->rightBST, value);
        return tree;
    }
    if(tree->value > value){
        tree->leftBST=deleteFromBST(tree->leftBST, value);
        return tree;
    }
    if((tree->leftBST==NULL)&&(tree->rightBST==NULL)){
        freeBST(tree);
        return createEmptyBST();
    }
    if(tree->leftBST==NULL){
        freeBST(tree->leftBST);
        return(tree->rightBST);
    }
    if(tree->rightBST==NULL){
        freeBST(tree->rightBST);
        return(tree->leftBST);
    }
    BinarySearchTree noeudMax=createEmptyBST();
    noeudMax=tree->leftBST;
    while(noeudMax->rightBST!=NULL){
        noeudMax=noeudMax->rightBST;
    }
    int valeurMax=noeudMax->value;
    tree->leftBST=deleteFromBST(tree->leftBST, valeurMax);
    tree->value=valeurMax;
    return tree;
}

/**
 * @brief Build a binary search tree from a given permutation.
 * @param permutation Array of integers representing the permutation
 * @param n size of the array
 * @return A binary such tree built by successively inserting the elements of permutation.
 */
BinarySearchTree buildBSTFromPermutation(int *permutation,size_t n) {
    BinarySearchTree tree=createEmptyBST();
    for(int i=0; i<n; i++){
        tree=addToBST(tree, permutation[i]);
    }
    return tree;
}

/**
 * @brief Print the elements of a binary search tree in a pretty format.
 * @param tree Pointer to the root of the tree.
 * @param space Space to be printed before the current element.
 */
void prettyPrintBST(BinarySearchTree tree, int space) {
    if (tree == NULL) {
        return;
    }
    space += 10;

    prettyPrintBST(tree->rightBST, space);

    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", tree->value);

    prettyPrintBST(tree->leftBST, space);
}

/**

Quelles conclusions pouvez-vous tirer des résultats d’expériences que vous obtenez ?

... Répondre ici.


*/
