
#include <stdio.h>

/**
 * How to use offsetof() and container_of()
 *
 * These macros are defined in include/linux/kernel.h and include/linux/list.h
 *
 * These macros allows to offsets of elements in the struct and give the
 * address of the container struct given an element of the struct.
 */

// How to calculate offsets in struct' elements
#define offsetof(TYPE, MEMBER)	((size_t) & ((TYPE *)0)->MEMBER)

/**
 * list_entry() and container_of() - get the struct for this entry
 * @ptr:	the &struct list_head pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 */
#define container_of(ptr, type, member) ({				\
		const typeof ( ((type *) 0)->member) *__mptr = (ptr); \
		(type *)( (char *) __mptr - offsetof(type, member)); })

struct list_head {
	struct list_head *next;
	struct list_head *prev;
};

typedef struct {
	char name[10];
	int age;
	float weight;
	struct list_head list_name;
} person;

void print_person(person *ptr);
void print_person_offsets();

int main() {
	person p;
	p.age = 24;
	p.weight = 80.4f;
	p.name[0] = 'M';
	p.name[1] = 'i';
	p.name[2] = 'k';
	p.name[3] = 'e';
	p.name[4] = '\0';

	print_person(&p);
	print_person_offsets();

	person *ptr = (person *) container_of(&p.list_name, person, list_name);
	printf("\nPerson using container_of(): \n");
	print_person(ptr);

	// Black magic here (use of ({})). The result of the last expression
	// is assigned to the left hand side.
	int a = ({ int c = 90; c * 2;});
	printf("\nThe result is: %d\n", a);

	return 0;
}

/**
 * Prints the elements of the person and their memory addresses.
 *
 * Output example:
 *
 * Person's memory address 140732899609216
 * Person's name Mike (memory address 140732899609216)
 * Person's age 24 (memory address 140732899609228)
 * Person's weight 80.40 (memory address 140732899609232)
 */
void print_person(person *ptr) {
	printf("Person's memory address %zu", (size_t) ptr);
	printf("\nPerson's name %s (memory address %zu)", ptr->name, (size_t) &ptr->name);
	printf("\nPerson's age %d (memory address %zu)", ptr->age, (size_t) &ptr->age);
	printf("\nPerson's weight %.2f (memory address %zu)", ptr->weight, (size_t) &ptr->weight);
}

/**
 * Prints the offsets of the struct person's elements.
 *
 * Output example:
 *
 * struct person's offsets
 * Name's offset 0
 * Age's offset 12
 * Weight's offset 16
 */
void print_person_offsets() {
	printf("\n\nstruct person's offsets");
	size_t offset_name = ((size_t) & ((person *)0)->name);
	size_t offset_age = ((size_t) & ((person *)0)->age);
	// the offset macro can simplify the work
	size_t offset_weight = offsetof(person, weight);

	printf("\nName's offset %zu",offset_name);
	printf("\nAge's offset %zu", offset_age);
	printf("\nWeight's offset %zu", offset_weight);
	printf("\n");
}

