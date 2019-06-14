#include <stdio.h>

#include "../../the-c-programming-language/datastructures/datastructures.h"

/**
 * This file shows how to use the linked list defined in datastructures.h
 * and linklist.c. In order to compile the program, the following command
 * is executed:
 *
 *      gcc datastructures.h linklist.c mainLinklist.c
 *      ./a.out
 */
int main() {
  printf("\nLINKED LIST\n");
  Linkedlist *linkedlist = (Linkedlist *) createlinkedlist();
  char *p[] = {"first", "second", "third", "fourth"};
  int numElements = 4;
  int i;
  for (i = 0; i < numElements; i++) {
    linkedlist->add(linkedlist, p[i]);
  }

  printf("Printing the list\n");
  linkedlist->print(linkedlist, STRING);

  printf("\n\nRemoving from the list\n");
  void *data = linkedlist->remove(linkedlist);
  printf("Removed element: %s", (char *)data);

  printf("\n\nPrinting the list after removing the first element\n");
  linkedlist->print(linkedlist, STRING);

  printf("\n\nInserting another element using a pointer to a function in the struct");
  linkedlist->add(linkedlist, "fifth");

  printf("\nPrinting the list after inserting another element\n");
  linkedlist->print(linkedlist, STRING);

  printf("\n\nDeleting the list\n");
  deletelinkedlist(linkedlist);
}
