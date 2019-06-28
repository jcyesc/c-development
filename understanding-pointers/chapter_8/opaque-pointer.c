
#include <stdlib.h>
#include "opaque-pointer.h"

typedef struct _node {
	Data * data;
	struct _node* next;
} Node;

struct _linkedList {
	Node* head;
};

LinkedList * getLinkedListInstance() {
	LinkedList* list = (LinkedList *) malloc(sizeof(LinkedList));
	list->head = NULL;

	return list;
}

void removeLinkedListInstance(LinkedList* list) {
	Node *tmp = list->head;
	while(tmp != NULL) {
		// Potential memory leak because data could have elements
		// pointing to other objects created using malloc.
		free(tmp->data);
		Node *current = tmp;
		tmp = tmp->next;
		free(current);
	}

	free(list);
}

void addNode(LinkedList *list, Data data) {
	Node *node = (Node *) malloc(sizeof(Node));
	node->data = data;
	if(list->head == NULL) {
		list->head = node;
		node->next = NULL;
	} else {
		node->next = list->head;
		list->head = node;
	}
}

Data removeNode(LinkedList *list) {
	if(list->head == NULL) {
		return NULL;
	} else {
		Node *tmp = list->head;
		list->head = list->head->next;
		Data* data = tmp->data;
		free(tmp);

		return data;
	}
}

void traverseList(LinkedList* list, void (*functionPtr)(Data)) {
	Node *tmp = list->head;

	while(tmp != NULL) {
		functionPtr(tmp->data);
		tmp = tmp->next;
	}
}

