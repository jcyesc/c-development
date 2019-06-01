/**
 * Pointer-Related types
 *
 * When working with pointers, there are 4 pointer-related types:
 *
 * size_t: Created to provide a safe type for sizes.
 *
 * ptrdiff_t: Created to handle pointer arithmetic.
 *
 * intptr_t: It is used for storing pointer addresses of int variables.
 *
 * uintprt_t: It is used for storing pointer addresses of unsigned int variables.
 *
 * Execute
 *
 * make pointer-related-types
 * ./pointer-related-types
 *
 */

#include <stdio.h>

int main() {
	printf("Pointer related types\n");

	size_t size = sizeof(void *);

	printf("sizeof(void *) = %lu byte(s)\n", size);
	printf("sizeof(char) = %lu byte(s)\n", sizeof(char));
	printf("sizeof(int) = %lu byte(s)\n", sizeof(int));
	printf("sizeof(int *) = %lu byte(s)\n", sizeof(int *));
	printf("sizeof(unsigned int) = %lu byte(s)\n", sizeof(unsigned int));
	printf("sizeof(unsigned int *) = %lu byte(s)\n", sizeof(unsigned int *));
	printf("sizeof(long) = %lu byte(s)\n", sizeof(long));
	printf("sizeof(long *) = %lu byte(s)\n", sizeof(long *));

	// Using intptr to store pointer addresses of long.
	// int number = 7; // Try this, with a pointer to long, you'll see a big number
	long number = 7;
	intptr_t *ptr = &number;

	printf("\nUsing intptr_t, the value of number is: %ld \n", *ptr);

	return 0;
}
