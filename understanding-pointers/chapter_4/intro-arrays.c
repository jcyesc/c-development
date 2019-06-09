
#include <stdio.h>
#include <stdlib.h>

/**
 * Intro to arrays
 *
 * An array is a contiguous collection of homogeneous elements that can be accessed
 * using an index. By contiguous, we mean the elements of the array are adjacent to
 * one another in memory with no gaps between them. By homogeneous, we mean they are
 * all of the same type.
 *
 * Difference between arrays and pointers
 *
 * There is a difference when the sizeof operator is applied to an array and to a
 * pointer to the same array. Applying the sizeof operator to vector (int vector[5] = {1, 2, 3, 4, 5};)
 * will return 20, the number of bytes allocated to the array. Applying the sizeof operator
 * against pv (int *pv = vector) will return 4, the pointer's size.
 */

void one_dimensional_array() {
	printf("================================== \n");
	printf("one_dimensional_array() \n");
	int size = 5;
	int vector[size];

	printf("Size of the vector %lu \n", sizeof(vector));
	for (int i = 0; i < size; i++) {
		vector[i] = i * 6; // array notation
	}

	for (int i = 0; i < size; i++) {
		printf("%d ", *(vector + i)); // pointer notation
	}

	printf("\n");
}

void two_dimensional_arrays() {
	printf("================================== \n");
	printf("two_dimensional_arrays() \n");
	int matrix[2][3] = { { 1, 2, 3 }, { 4, 5, 6 } };

	printf("Size of the two dimensional array %lu \n", sizeof(matrix));

	for (int i = 0; i < 2; i++) {
		printf("&matriz[%d]: %p sizeof(matrix[%d]): %lu\n", i, &matrix[i], i,
				sizeof(matrix[i]));
	}
}

void malloc_and_one_dimensional_array() {
	printf("================================== \n");
	printf("malloc_and_one_dimensional_array() \n");

	int size = 5;
	int *pv = (int *) malloc(size * sizeof(int));
	for (int i = 0; i < size; i++) {
		pv[i] = i + 1;
	}

	for (int i = 0; i < size; i++) {
		printf("%d ", *(pv + i));
	}

	printf("\n");

	free(pv);
}

int main() {
	one_dimensional_array();

	two_dimensional_arrays();

	malloc_and_one_dimensional_array();
	return 0;
}

