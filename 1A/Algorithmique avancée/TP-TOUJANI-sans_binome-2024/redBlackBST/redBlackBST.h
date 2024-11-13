/**
 * \file redBlackBST.h
 * \brief Data structure and functions related to Red-Black Binary Search Trees.
 * \author Loïck LHOTE
 * \version 0.1
 * \date janvier 2023
 *
 * Header file defining the data structure of a red-black binary search tree over integers and
 * declaring functions to manipulate them.
 *
 */

#ifndef REDBLACKBST_H_INCLUDED
#define REDBLACKBST_H_INCLUDED

/**
 * @brief Red color is 1
 */
#define RED 1
/**
 * @brief Black color is 0
 */
#define BLACK 0

/**
 * @brief A node in red-black binary search tree.
 */
typedef struct nodeRedBlackBST{
    /** The color of the node. */
    int color;
    /** The value stored in this node. */
    int value;
    /** Pointer to the left child of this node. */
    struct nodeRedBlackBST *leftBST;
    /** Pointer to the right child of this node. */
    struct nodeRedBlackBST *rightBST;
    /** Pointer to the father of this node. */
    struct nodeRedBlackBST *father;
} NodeRedBlackBST;

/**
 * @brief A randomized binary search tree is a pointer to the root node.
 */
typedef NodeRedBlackBST *RedBlackBST;


/**
 * @brief Create an empty red-black binary search tree.
 * @return A pointer to the root of the new empty tree (NULL pointer).
 */
RedBlackBST createEmptyRedBlackBST() ;

/**
 * @brief Free the memory of a red-black binary search tree.
 * @param tree Pointer to the root of the tree.
 */
void freeRedBlackBST(RedBlackBST tree);


/**
 * @brief Perform a left rotation on the Red-Black BST.
 * @param tree Pointer to the root node of the Red-Black BST.
 * @param node Pointer to the node to rotate around.
 * @return Pointer to the root node of the rotated Red-Black BST.
 */
RedBlackBST leftRotationRedBlackBST(RedBlackBST tree, NodeRedBlackBST *node);

/**
 * @brief Perform a right rotation on the Red-Black BST.
 * @param tree Pointer to the root node of the Red-Black BST.
 * @param node Pointer to the node to rotate around.
 * @return Pointer to the root node of the rotated Red-Black BST.
 */
RedBlackBST rightRotationRedBlackBST(RedBlackBST tree, NodeRedBlackBST *node);



/**
 * @brief Balance the Red-Black BST after inserting a red node at a leaf.
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
void balanceRedBlackBST(RedBlackBST *tree, NodeRedBlackBST *curr);


/**
 * @brief Insert a node in the Red-Black BST.
 * @param tree Pointer to the root node of the Red-Black BST.
 * @param value Value to be inserted in the Red-Black BST.
 *
 * The root of the tree can be modified so that we have a pointer on a RedBlackBST.
 */
void insertNodeRedBlackBST(RedBlackBST *tree, int value);



/**
 * @brief Compute the height of a red-black binary search tree.
 * @param tree Pointer to the root of the tree.
 * @return The height of the tree.
 */
int heightRedBlackBST(RedBlackBST tree) ;


/**
 * @brief Search for a value in a red-black binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to search for.
 * @return A pointer to the node containing the value, or NULL if the value is not in the tree.
 */
RedBlackBST searchRedBlackBST(RedBlackBST tree, int value);

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

int blackHeightRedBlackBST(RedBlackBST tree);

/**
 * @brief Test if a Red-Black BST is a valid Red-Black BST.
 * @param tree Pointer to the root node of the Red-Black BST.
 * @return 1 if the Red-Black BST is a valid Red-Black BST, 0 otherwise.
 */
int isRedBlackBST(RedBlackBST tree);


/**
 * @brief Build a red-black binary search tree from a given permutation.
 * @param permutation Array of integers representing the permutation
 * @param n size of the array
 * @return A red-black binary search tree built by successively inserting the elements of permutation.
 */
RedBlackBST buildRedBlackBSTFromPermutation(int *permutation,size_t n);


/**
 * @brief Print the elements of a binary search tree in a pretty format.
 * @param tree Pointer to the root of the tree.
 * @param space Space to be printed before the current element.
 */
void prettyPrintRedBlackBST(RedBlackBST tree, int space) ;


#endif // REDBLACKBST_H_INCLUDED


