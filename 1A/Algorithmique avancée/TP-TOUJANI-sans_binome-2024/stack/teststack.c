#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main() {
    Stack* s = createStack() ;
    //stackPrint(*s);

    // Add elements to the queue
    /*
    printf("\nAdd 1 to stack:\n");
    push(s, 1);
    stackPrint(*s);
    printf("\nAdd 2 to stack:\n");
    push(s, 2);
    stackPrint(*s);
    printf("\nAdd 3 to stack:\n");
    push(s, 3);
    stackPrint(*s);
    */
    // Remove an element from the stack
    /*
    int top = pop(s);
    printf("\npoped value: %d\n", top);
    // Print the elements in the stack
    printf("Updated stack:\n");
    stackPrint(*s);
    top = pop(s);
    printf("\npoped value: %d\n", top);
    // Print the elements in the stack
    printf("Updated stack:\n");
    stackPrint(*s);
    */
    /*
    printf("\nadd 4 to stack:\n");
    push(s, 4);
    stackPrint(*s);
    printf("\nTop value of the stack: %d\n",peek(*s));
    stackPrint(*s);
    */

    // Check if the stack is empty
    //printf("\nIs stack empty? %d\n", isStackEmpty(*s));

    // Remove all elements from the stack
    /*
    while (!isStackEmpty(*s)) {
        pop(s);
    }

    printf("\nFinal stack:\n");
    stackPrint(*s);

    // Check if the stack is empty
    printf("\nIs stack empty? %d\n", isStackEmpty(*s));
    */
    free(s);

    return 0;
}
