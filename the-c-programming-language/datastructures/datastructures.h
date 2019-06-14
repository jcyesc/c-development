
/******************************************************************************
 * This header defines the methods and data structures for the linked list and
 * stack.
 ******************************************************************************/

/**
 * It defines the available data types for printing.
 */
typedef enum {STRING, INT, DOUBLE} datatype;

/*****************************************************************
 *
 *
 * LINKED LIST : DATA STRUCTURES AND METHODS
 *
 *
 *****************************************************************/

/**
 * Struct of the node list. It contains a pointer to the data
 * and a pointer to the next node.
 */
typedef struct nodelist {
   void *data;
   struct nodelist *next;
} Nodelist;

/**
 * Struct of the linked list. It contains the pointer to the first
 * node of the linked list.
 */
typedef struct linkedlist {
  Nodelist *root;
  // It adds an element to the linked list.
  void (*add)(struct linkedlist *, void *);
  // It removes the element at the front (the last element inserted)
  void *(*remove)(struct linkedlist *);
  // It prints the linked list.
  void (*print)(struct linkedlist *, datatype);

} Linkedlist;

/* It creates a linked list. */
Linkedlist* createlinkedlist();

/* It deletes the linked list and all its nodes. */
void deletelinkedlist(Linkedlist *list);

/*****************************************************************
* END LINKED LIST DEFINITION
*****************************************************************/

/*****************************************************************
 *
 *
 * STACK : DATA STRUCTURES AND METHODS
 *
 *
 *****************************************************************/

/**
 * Struct of the stack. It contains a linked list to keep track of
 * the elements. It also contains the pointers to the pop, push and
 * isEmpty functions.
 */
typedef struct stack {
  Linkedlist *list;
  // It pops the top element from the stack.
  void *(*pop)(struct stack *);
  // It pushes the element at the top of the stack.
  void (*push)(struct stack *, void *);
  /* It returns 0 if the stack is empty, otherwise it returns a number
  greater than 0. */
  int (*isempty)(struct stack *);
  // It prints the elemets in the stack.
  void (*print)(struct stack *, datatype);
} Stack;

/* It creates a linked list. */
Stack* createstack();

/* It deletes the linked list and all its nodes. */
void deletestack(Stack *stack);

/*****************************************************************
* END STACK DEFINITION
*****************************************************************/
