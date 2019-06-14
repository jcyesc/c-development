#include <stdio.h>

#include "../../the-c-programming-language/datastructures/datastructures.h"

/**
 * This files shows how to use the stack defined in datastructures.h
 * and stack.c. In order to compile the program, the following command
 * is executed:
 *
 *     gcc datastructures.h linklist.c stack.c mainStack.c
 *     ./a.out
 */
int main() {
  printf("\nSTACK\n");
  Stack *stack = createstack();
  printf("\nPushing elements to the stack\n"); 
  stack->push(stack, "first");
  stack->push(stack, "second");
  stack->push(stack, "third");

  stack->print(stack, STRING);

  printf("\n\nPopping one element from the stack:\n");
  char *element = (char *)stack->pop(stack);
  printf("Pop element: %s\n", element);

  printf("\nPushing another element");
  stack->push(stack, "fourth");
  stack->print(stack, STRING);

  printf("\n\nDeleting the stack\n");
  deletestack(stack);
  return 1;
}
