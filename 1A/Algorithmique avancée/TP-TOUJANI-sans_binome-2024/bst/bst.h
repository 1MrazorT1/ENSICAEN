/**
 * \file bst.h
 * \brief Data structure and functions related to Binary Search Trees (BST).
 * \author Loïck LHOTE
 * \version 0.1
 * \date janvier 2023
 *
 * Header file defining the data structure of a binary search tree over integers and
 * declaring functions to manipulate them.
 *
 */

#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED


/**
 * @brief A node in a binary search tree.
 */
typedef struct node{
    /** The value stored in this node. */
    int value;
    /** Pointer to the left child of this node. */
    struct node *leftBST;
    /** Pointer to the right child of this node. */
    struct node *rightBST;
} NodeBST;

/**
 * @brief A binary search tree is a pointer to the root node.
 */
typedef NodeBST *BinarySearchTree;


/**
 * @brief Create an empty binary search tree.
 * @return A pointer to the root of the new empty tree (NULL pointer).
 */
BinarySearchTree createEmptyBST() ;

/**
 * @brief Free the memory of a binary search tree.
 * @param tree Pointer to the root of the tree.
 */
void freeBST(BinarySearchTree tree);

/**
 * @brief Add a value to a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to add.
 * @return A pointer to the root of the modified tree.
 */
BinarySearchTree addToBST(BinarySearchTree tree, int value);

/**
 * @brief Compute the height of a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @return The height of the tree.
 */
int heightBST(BinarySearchTree tree) ;


/**
 * @brief Search for a value in a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to search for.
 * @return A pointer to the node containing the value, or NULL if the value is not in the tree.
 */
BinarySearchTree searchBST(BinarySearchTree tree, int value);


/**
 * @brief Delete the root of a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @return A pointer to the root of the modified tree.
 */
BinarySearchTree deleteRootBST(BinarySearchTree tree);

/**
 * @brief Delete a value from a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to delete.
 * @return A pointer to the root of the modified tree.
 */
BinarySearchTree deleteFromBST(BinarySearchTree tree, int value);


/**
 * @brief Build a binary search tree from a given permutation.
 * @param permutation Array of integers representing the permutation
 * @param n size of the array
 * @return A binary such tree built by successively inserting the elements of permutation.
 */
BinarySearchTree buildBSTFromPermutation(int *permutation,size_t n) ;


/**
 * @brief Print the elements of a binary search tree in a pretty format.
 * @param tree Pointer to the root of the tree.
 * @param space Space to be printed before the current element.
 */
void prettyPrintBST(BinarySearchTree tree, int space) ;


#endif // BST_H_INCLUDED
