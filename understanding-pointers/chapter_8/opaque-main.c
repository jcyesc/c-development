#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "opaque-pointer.h"

/**
 * Opaque Pointer
 *
 * To execute this program run
 *
 * make opaque-main
 * ./opaque-main
 *
 */

typedef struct {
	char name[10];
	int age;
} Person;

void displayPerson(Person* person) {
	printf("Name: %s Age: %d \n", person->name, person->age);
}

int main() {
	Person *p1 = (Person *) malloc(sizeof(Person));
	strcpy(p1->name, "Michael");
	p1->age = 50;

	Person *p2 = (Person *) malloc(sizeof(Person));
	strcpy(p2->name, "Kevin");
	p2->age = 30;

	LinkedList* list = getLinkedListInstance();
	addNode(list, p1);
	addNode(list, p2);

	traverseList(list, (void (*)(Data))displayPerson);

	removeLinkedListInstance(list);

	return 0;
}
