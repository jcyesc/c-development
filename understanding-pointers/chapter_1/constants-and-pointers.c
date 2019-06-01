/**
 * Constants and Pointers
 *
 * Using the const keywork with pointers is a rich and powerful aspect of C.
 * It provides different types of protections for different problems sets.
 *
 * This program gives examples of:
 *
 * - Pointers to constant
 * - Constant pointers to nonconstants
 * - Constant pointers to constants
 * - Pointer to (constant pointer to constant)
 *
 * Execute the following commands:
 *
 * make constants-and-pointers
 * ./constants-and-pointers
 */

#include <stdio.h>

/**
 * Pointers to constant
 *
 * A pointer that points to a constant cannot be used to modify the value it
 * is referencing.
 *
 * if we have const int *pci;, the declaration of pci as a pointer to a
 * constant integer means:
 *
 *	- pci can be assigned to point to different constant integers
 *	- pci can be assigned to point do different nonconstant integers
 *	- pci can be dereferenced for reading purposes
 *	- pci cannot be dereferenced to change what it points to\\
 */
void pointers_to_constant() {
	printf("====================================\n");
	printf("pointers_to_constant()\n");
	printf("====================================\n");

	int num = 20;
	const int *pci = &num;
	printf("*pci is %d \n", *pci);

	// *pci = 30; // read-only variable is not assignable

	printf("Reassigning pci\n");
	const int anotherNumber = 90;
	pci = &anotherNumber;
	printf("*pci is %d \n", *pci);
}

/**
 * Constant pointers to nonconstants
 *
 * Constant pointers to nonconstants means that while the pointer cannot be
 * changed, the data pointed to can be modified.
 *
 */
void constant_pointers_to_nonconstants() {
	printf("====================================\n");
	printf("constant_pointers_to_nonconstants()\n");
	printf("====================================\n");

	int num;
	int *const cpi = &num;
	*cpi = 45;
	printf("*cpi is %d \n", *cpi);
	*cpi = 90; // Data can be changed
	printf("*cpi is %d \n", *cpi);

	// int anotherNumber = 90;
	// cpi = &anotherNumber; // cannot assign to variable 'cpi' with const-qualified type 'int *const'

	printf("Modifying constants\n");
	volatile const int limit = 500; // Try with volatile and without volatile
	printf("limit is %d (before being modified)\n", limit);
	// If cpi2 referenced the constant limit, the constant could be modified.
	int *const cpi2 = &limit; // warning: initializing 'int *const' with an expression of
							  // type 'const volatile int *'
    							  // discards qualifiers
	*cpi2 = 890;

	// Modifying the constant
	printf("limit is %d (after being modified)\n", limit);
	printf("limit is %p \n", &limit);
	printf("*cpi2 is %d \n", *cpi2);
	printf("*cpi2 is %p \n", cpi2);
}

/**
 * Constant pointers to constants
 *
 * A constant pointer to a constant is an infrequently used pointer type.
 * The pointer cannot be changed and the data it points to cannot be changed
 * through the pointer.
 */
void constant_pointers_to_constants() {
	printf("====================================\n");
	printf("constant_pointers_to_constants()\n");
	printf("====================================\n");

	const int limit = 89;
	const int * const cpci = &limit;

	printf("limit is %d \n", limit);
	printf("*cpci is %d \n", *cpci);
	// *cpci = 90; // error: read-only variable is not assignable
}

/**
 * Pointer to (constant pointer to constant)
 *
 * Pointers to constants can also have multiple levels of indirection.
 * Reading complex declarations from right to left helps clarify these types
 * of declarations:
 *
 * const int * const cpci = &limit;
 * const int * const * pcpci;
 *
 * Pointer to constant pointer to constant can be modified, however
 * the pointer it points and the constant can't be modified.
 *
 */
void constant_to_constant_pointer_to_constant() {
	printf("====================================\n");
	printf("constant_to_constant_pointer_to_constant()\n");
	printf("====================================\n");

	const int limit = 600;
	const int * const cpci = &limit; // constant pointer to constant integer
	const int * const * pcpci; // pointer to a constant pointer to constant integer
	pcpci = &cpci;

	printf("limit %d \n", limit);
	printf("*cpci %d \n", *cpci);
	printf("**pcpci %d \n", **pcpci);
}

int main() {
	pointers_to_constant();
	constant_pointers_to_nonconstants();
	constant_pointers_to_constants();
	constant_to_constant_pointer_to_constant();

	return 0;
}

