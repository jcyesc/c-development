#include <stdio.h>
#include <stdlib.h>

// It contains the data structures for the list.
#include "../../the-c-programming-language/datastructures/datastructures.h"

/**
 * LINKED LIST
 *
 * This file contains the definition and implementation of the main
 * linked list methods. The linked list in this particular implementation
 * insert all the elements at the begiNning of the list.
 *
 */

/*
 * It removes the first node from the linked list and returns
 * the data. If the list is empty, it returns null
 */
void * removeData(Linkedlist *linkedlist) {
  void *tmp = NULL;
  if (linkedlist->root != NULL) {
    Nodelist *node = linkedlist->root;
    // assigning the new root
    linkedlist->root = node->next;
    // Getting the data.
    tmp = node->data;
    // releasing the memory
    free(node);

  }

  return tmp;
}

/**
 * It prints the elements of the linked list. It treats the elements
 * as pointer to strings.
 */
void printList(Linkedlist *linkedlist, datatype type) {
  Nodelist *tmp;
  printf("{");
  for (tmp = linkedlist->root; tmp != NULL; tmp = tmp->next) {
    switch (type) {
      case STRING:
        printf("%s", (char *) tmp->data);
        break;
      case INT:
        printf("%d", *((int *) tmp->data));
        break;
      case DOUBLE:
        printf("%f", *((double *) tmp->data));
        break;
    }

    if (tmp->next != NULL) {
      printf(", ");
    }
  }
  printf("}");
}

/**
 * It creates a node of  the list. It receives a pointer to the data
 * and allocaates memory for the new node.
 */
Nodelist* createnodelist(void *data) {
  Nodelist *nodelist = (Nodelist *) malloc(sizeof(Nodelist));
  nodelist->data = data;
  return nodelist;
}

/**
 * It inserts a new node at the begining of the list. The new node
 * contains the pointer to the data.
 */
void insert(Linkedlist *linkedlist, void *data) {
  Nodelist *newNode = createnodelist(data);
  newNode->next = linkedlist->root;
  linkedlist->root = newNode;
}

/**
 * It creates a linked list. First, it allocates the memory for the
 * empty linked list and then initializes the root with null.
 */
Linkedlist* createlinkedlist() {
  Linkedlist *list = (Linkedlist *) malloc(sizeof(Linkedlist));
  list->root = NULL;
  list->add = insert;
  list->remove = removeData;
  list->print = printList;
  return list;
}

/**
 * It deletes the linked list and all the nodes that belongs to the
 * linked list.
 */
void deletelinkedlist(Linkedlist *list) {
  Nodelist *tmp;
  Nodelist *node;
  for (node = list->root; node != NULL; node = tmp) {
    tmp = node->next;
    free(node);
  }

  free(list);
}
