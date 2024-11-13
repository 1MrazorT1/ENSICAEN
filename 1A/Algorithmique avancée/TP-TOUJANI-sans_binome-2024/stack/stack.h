/**
 * @file stack.h
 * @brief Header file for the Stack data structure.
 */

#ifndef STACK_H
#define STACK_H
#include "../list/list.h"

/**
 * @brief The Stack data structure. It is only a list.
 */

typedef List Stack;

/**
 * @brief Creates a new stack with no elements.
 *
 * @return A pointer to the new stack.
 */
Stack* createStack();

/**
 * @brief Pushes an element onto the top of the stack.
 *
 * @param stack The stack to push onto.
 * @param data The data to push onto the stack.
 */
void push(Stack* stack, int data);

/**
 * @brief Pops an element from the top of the stack.
 *
 * @param stack The stack to pop from.
 *
 * @return The data from the top element of the stack.
 */
int pop(Stack* stack);

/**
 * @brief Peeks at the top element of the stack without removing it.
 *
 * @param stack The stack to peek at.
 *
 * @return The data from the top element of the stack.
 */
int peek(Stack stack);

/**
 * @brief Checks whether the stack is empty.
 *
 * @param stack The stack to check.
 *
 * @return 1 if the stack is empty, 0 otherwise.
 */
int isStackEmpty(Stack stack);

/**
 * @brief Prints the contents of the stack to stdout.
 *
 * @param stack The stack to print.
 */
void stackPrint(Stack stack);

#endif /* STACK_H */
