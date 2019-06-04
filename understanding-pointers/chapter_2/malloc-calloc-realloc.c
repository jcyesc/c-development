#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Memory allocation
 *
 * Several functions are available in stdlib.h for memory allocation:
 *
 * - malloc()	Allocates memory from the heap.
 * - realloc()	Reallocates memory to a larger or smaller amount based on a previously
 * 				allocated block of memory.
 * - calloc()	Allocates and zeros out memory from the heap.
 * - free()		Returns a block of memory to the heap.
 *
 * Dynamic memory is allocated from the heap. With succesive memory allocation calls,
 * there is not guarantee regarding the order of the memory or the continuity of memory
 * allocated. However, the memory allocated will be aligned according to the pointer's data type.
 * For example, a four-byte integer would be allocated on an address boundary evenly divisible.
 *
 */

void example_malloc() {
	printf("Allocating memory with malloc()\n");
	int *ptr = (int *) malloc(sizeof(int) * 1);
	*ptr = 89;
	printf("*ptr = %d \n", *ptr);

	free(ptr);
}

void example_calloc() {
	printf("\nAllocating memory with calloc()\n");
	int numberElem = 10;
	int *ptr = (int *) calloc(numberElem, sizeof(int));

	for (int i = 0; i < numberElem; i++) {
		printf("ptr[%d] = %d \n", i, *(ptr + i));
	}

	free(ptr);
}

void example_realloc() {
	printf("\nAllocating memory with realloc()\n");
	int numberElem = 16;
	char * string1 = (char *) malloc(16);
	char * string2;
	strcpy(string1, "0123456789AB");

	string2 = realloc(string1, 8);
	// NOTE that we are printing memory that is
	printf("string1 Value %p [%s]\n", string1, string1);
	printf("string2 Value %p [%s]\n", string2, string2);

	free(string1);
	if (string1 != string2) {
		free(string2);
	}
}

int main() {

	size_t size = sizeof(void *);
	printf("The size of void* is %lu \n", size);

	example_malloc();
	example_calloc();
	example_realloc();

	return 0;
}
