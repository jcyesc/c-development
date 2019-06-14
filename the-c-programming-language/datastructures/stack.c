#include <stdio.h>
#include <stdlib.h>

#include "../../the-c-programming-language/datastructures/datastructures.h"

/**
 * STACK
 *
 * This file contains the definition and implementation of the main
 * stack methods (pop, push). It uses a linklist internally.
 *
 */

/* It prints the content of the stack. */
//void print(Stack *stack,  datatype type);

/**
 * It pops an element from the stack. Before popping an element,
 * make sure that is not empty.
 *
 */
void * pop(Stack *stack) {
  Linkedlist *list = stack->list;
  void *tmp = list->remove(list);
  return tmp;
}

/**
 * It pushes an element to the stack. 
 */
void push(Stack *stack, void *data) {
  Linkedlist *list = stack->list;
  list->add(list, data);
}

/**
 * It checks if the stack is empty or not. It returns
 * true if not empty, otherwise false.
 *
 */
int isempty(Stack *stack) {
	if (stack->list->root == NULL) {
		return 1;
	}

	return 0;
}

/* It prints the content of the stack. */
void print(Stack *stack, datatype type) {
  stack->list->print(stack->list, type);
}

/* It creates a stack and the internal linked list and sets up the
 * function to pointers.
 */
Stack* createstack() {
  Stack *stack = (Stack *) malloc(sizeof(Stack));
  stack->list = createlinkedlist();
  // Setting the function to pointers.
  stack->pop = pop;
  stack->push = push;
  stack->isempty = isempty;
  stack->print = print;

  return stack;
}

/* It deletes the stack and the internal linked list and all its nodes. */
void deletestack(Stack *stack) {
  deletelinkedlist(stack->list);
  free(stack);
}
