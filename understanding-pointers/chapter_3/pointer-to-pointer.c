
#include <stdio.h>
#include <stdlib.h>

/**
 * Passing a Pointer to a Pointer
 *
 * When a pointer is passed to a function, it is passed by value. If we want to modify the
 * original pointer and not the copy of the pointer, we need to pass it as a pointer to
 * a pointer.
 */


void allocateArray(int **arr, int size, int value) {
	*arr = (int *) malloc(size * sizeof(int));
	if (*arr != NULL) {
		for(int i =0; i < size; i++) {
			*(*arr + i) = value;
		}
	}
}

/**
 * The free function does not check the pointer passed to see whether
 * it is NULL and does not set the pointer to NULL before it returns. Setting
 * a pointer to NULL after freeing is a good practice.
 *
 * The saferFree function calls the free function that actually deallocates
 * the memory. Its parameter is declared as a pointer to a pointer to void. Using
 * a pointer to a pointer allows us to modify the pointer passed.
 */
void saferFree(void **pp) {
	if (pp != NULL && *pp != NULL) {
		free(*pp);
		*pp = NULL;
	}
}

#define safeFree(p) saferFree((void **) & (p))

int main() {
	printf("Pointer to Pointers\n");

	int size = 5;
	int *vector = NULL;
	allocateArray(&vector, size, 45);

	for (int i = 0; i < size; i++) {
		printf("vector[%d] = %d \n", i, vector[i]);
	}

	safeFree(vector);

	return 0;
}


