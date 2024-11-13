/**
 * \file redBlackBST.c
 * \brief Implementation of the functions related to Red-Black Binary Search Trees.
 * \author Loïck LHOTE
 * \version 0.1
 * \date janvier 2023
 *
 * Header file defining the data structure of a red-black binary search tree over integers and
 * declaring functions to manipulate them.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "redBlackBST.h"




/**
 * @brief Create an empty red-black binary search tree.
 * @return A pointer to the root of the new empty tree (NULL pointer).
 */
RedBlackBST createEmptyRedBlackBST(){
    return NULL;
}

/**
 * @brief Free the memory of a red-black binary search tree.
 * @param tree Pointer to the root of the tree.
 */
void freeRedBlackBST(RedBlackBST tree){
    if(tree == NULL){
        return ;
    }
    if(tree->leftBST != NULL){
        freeRedBlackBST(tree->leftBST);
    }
    if(tree->rightBST != NULL){
        freeRedBlackBST(tree->rightBST);
    }
    freeRedBlackBST(tree->father);
    free(tree);
    return ;
}


/**
 * @brief Perform a left rotation on the Red-Black BST.
 * @param tree Pointer to the root node of the Red-Black BST.
 * @param node Pointer to the node to rotate around.
 * @return Pointer to the root node of the rotated Red-Black BST.
 */
RedBlackBST leftRotationRedBlackBST(RedBlackBST tree, NodeRedBlackBST *node){
    NodeRedBlackBST *rightChild = node->rightBST;
    node->rightBST = rightChild->leftBST;

    if (rightChild->leftBST != NULL)
        rightChild->leftBST->father = node;

    rightChild->father = node->father;

    if (node->father == NULL)
        tree = rightChild;
    else if (node->father->leftBST == node)
        node->father->leftBST = rightChild;
    else
        node->father->rightBST = rightChild;

    rightChild->leftBST = node;
    node->father = rightChild;

    return tree;
}




/**
 * @brief Perform a right rotation on the Red-Black BST.
 * @param tree Pointer to the root node of the Red-Black BST.
 * @param node Pointer to the node to rotate around.
 * @return Pointer to the root node of the rotated Red-Black BST.
 */
RedBlackBST rightRotationRedBlackBST(RedBlackBST tree, NodeRedBlackBST *node)
{
    NodeRedBlackBST *leftChild = node->leftBST;
    node->leftBST = leftChild->rightBST;

    if (leftChild->rightBST != NULL)
        leftChild->rightBST->father = node;

    leftChild->father = node->father;

    if (node->father == NULL)
        tree = leftChild;
    else if (node->father->leftBST == node)
        node->father->leftBST = leftChild;
    else
        node->father->rightBST = leftChild;

    leftChild->rightBST = node;
    node->father = leftChild;

    return tree;
}


/**
 * @brief Balance the Red-Black BST after inserting (or crating) a red node.
 * @param tree Pointer to the root node of the Red-Black BST. Be careful, the root may change after balancing.
 * @param curr Pointer to the node that was recently inserted. Be careful, the node to deal with may change after each operation.
 *
 * There are several cases:
 *   - if *curr is the root, then change its color in black
 *   - if the father of *curr is black, then it is finished
 *   - the father and the uncle are red (see course)
 *   - the uncle node is black and the current node is a right child (left rotation, see course)
 *   - the uncle node is black and the current node is a left child (right rotation, see course)
 */
void balanceRedBlackBST(RedBlackBST *tree, NodeRedBlackBST *curr)
{
    while(curr->father->color == 1){
        if(curr->father == curr->father->father->leftBST){
            NodeRedBlackBST *y = curr->father->father->rightBST;
            if(y->color == 1){
                curr->father->color = 0;
                y->color = 0;
                curr->father->father->color = ;
                curr = curr->father->father;
            }else if(curr == curr->father->rightBST){
                curr = curr->father;
                leftRotationRedBlackBST(tree, curr);
            }
            curr->father->color = 0;
            curr->father->father->color = 1;
            rightRotationRedBlackBST(tree, curr->father->father);
        }else{
            NodeRedBlackBST *y = curr->father->father->rightBST;
            if(y->color == 1){
                curr->father->color = 0;
                y->color = 0;
                curr->father->father->color = ;
                curr = curr->father->father;
            }else if(curr == curr->father->rightBST){
                curr = curr->father;
                rightRotationRedBlackBST(tree, curr);
            }
            curr->father->color = 0;
            curr->father->father->color = 1;
            leftRotationRedBlackBST(tree, curr->father->father);
        }
    }
    tree->root->color = 0;
}


/**
 * @brief Insert a node in the Red-Black BST.
 * @param tree Pointer to the root node of the Red-Black BST.
 * @param value Value to be inserted in the Red-Black BST.
 *
 * The root of the tree can be modified so that we have a pointer on a RedBlackBST.
 */
void insertNodeRedBlackBST(RedBlackBST *tree, int value)
{
    NodeRedBlackBST *y = createEmptyRedBlackBST();
    NodeRedBlackBST *x = *tree;
    NodeRedBlackBST *curr = createEmptyRedBlackBST()
    curr->value = value;
    while(*x != NULL){
        *y = *x;
        if(value < x->value){
            x = x->leftBST;
        }else{
            x = x->rightBST;
        }
    }
    curr->father = *y;
    if(y == NULL){
        *tree = *curr;
    }else if(curr->value < y->value){
        y->leftBST = *curr;
    }else{
        y->right = *curr;
    }
    curr->leftBST = NULL;
    curr->rightBST = NULL;
    curr->color = 1;
    balanceRedBlackBST(tree, curr)
}

/**
 * @brief Compute the height of a red-black binary search tree.
 * @param tree Pointer to the root of the tree.
 * @return The height of the tree.
 */
int heightRedBlackBST(RedBlackBST tree){
    if (tree == NULL) {
        return -1; // height of an empty tree is -1
    }
    int leftHeight = heightRedBlackBST(tree->leftBST);
    int rightHeight = heightRedBlackBST(tree->rightBST);
    if (leftHeight > rightHeight)
        return leftHeight + 1;
    else
        return rightHeight + 1;
}

/**
 * @brief Search for a value in a red-black binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to search for.
 * @return A pointer to the node containing the value, or NULL if the value is not in the tree.
 */
RedBlackBST searchRedBlackBST(RedBlackBST tree, int value){
    if (tree == NULL)
        return NULL; // value not in the tree
    else if (value < tree->value)
        return searchRedBlackBST(tree->leftBST, value);
    else if (value > tree->value)
        return searchRedBlackBST(tree->rightBST, value);
    else
        return tree; // value found in the tree
}


/**
* @brief Computes the black height of a red-black tree (counts also the root if it is black).
* @param node Pointer to the root node of the tree.
* @return The black height of the tree.
*
* It returns 1 plus the black height of the tree if the root is black or the black heiht with a red root.
* It returns -1 if the black height of the left and right subtrees of the root are different
* or equal to -1.
*
*/

int blackHeightRedBlackBST(RedBlackBST tree) {
  if (!tree) {
    return 1; // If the tree is empty, then the black height is 1.
  }
  int leftHeight = blackHeightRedBlackBST(tree->leftBST); // Recursively compute the black height of the left subtree.
  int rightHeight = blackHeightRedBlackBST(tree->rightBST); // Recursively compute the black height of the right subtree.

  if(leftHeight!=rightHeight) // the black height of the left and right subtrees must be equal
    return -1;
  if(leftHeight==-1)
    return -1;

  // If the left and right subtrees have the same black height and the root node is black, then the black height of the tree is increased by 1.
  if (tree->color == BLACK) {
    return leftHeight + 1;
  }
  return leftHeight;
}



/**
 * @brief Test if a Red-Black BST is a valid Red-Black BST.
 * @param tree Pointer to the root node of the Red-Black BST.
 * @return 1 if the Red-Black BST is a valid Red-Black BST, 0 otherwise.
 */
int isRedBlackBST(RedBlackBST tree)
{
    if(tree == NULL){
        return 1;
    }
    if(tree->color == 0){
        if((tree->rightBST != NULL) && (tree->leftBST != NULL)){
            if(tree->rightBST->color == tree->leftBST->color == 1){
                if(isRedBlackBST(tree->rightBST->rightBST) == isRedBlackBST(tree->rightBST->leftBST) == isRedBlackBST(tree->leftBST->rightBST) == isRedBlackBST(tree->leftBST->leftBST) == 1){
                    return 1;
                }
            }
        }
    }
    return 0;
}


/**
 * @brief Build a red-black binary search tree from a given permutation.
 * @param permutation Array of integers representing the permutation
 * @param n size of the array
 * @return A red-black binary search tree built by successively inserting the elements of permutation.
 */
RedBlackBST buildRedBlackBSTFromPermutation(int *permutation,size_t n){
    if (n == 0)
        return NULL;
    RedBlackBST tree = createEmptyRedBlackBST();
    for(int i=0;i<n;i++){
        insertNodeRedBlackBST(&tree, permutation[i]);
    }
    return tree;
}


/**
 * @brief Print the elements of a binary search tree in a pretty format.
 * @param tree Pointer to the root of the tree.
 * @param space Space to be printed before the current element.
 */
void prettyPrintRedBlackBST(RedBlackBST tree, int space) {
    if (tree == NULL) {
        return;
    }
    space += 10;

    prettyPrintRedBlackBST(tree->rightBST, space);

    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("[%d,%d]\n", tree->value, tree->color);

    prettyPrintRedBlackBST(tree->leftBST, space);
    return ;
}
