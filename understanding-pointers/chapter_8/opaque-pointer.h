
/**
 * Opaque Pointer
 *
 * An opaque pointer can be used to effect data encapsulation in C. One approach
 * declares a structure without any implementation details in a header file. Functions
 * are then defined to work with a specific implementation of the data structure in
 * an implementation file. A user of the data structure will see the declaration and the
 * functions' prototypes. However, the implementation is hidden.
 *
 * See below the example of an opaque pointer that is used to declare a linked list.
 */

typedef void *Data;
typedef struct _linkedList LinkedList;

LinkedList * getLinkedListInstance();

void removeLinkedListInstance(/* opaque pointer */ LinkedList* list);

void addNode(/* opaque pointer */ LinkedList *, Data);

Data removeNode(/* opaque pointer */ LinkedList *);

void traverseList(LinkedList* list, void (*functionPtr)(Data));
