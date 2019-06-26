#include <stdio.h>

/**
 * One-Dimensional arrays
 *
 * There are two ways to pass one-dimensional arrays:
 *
 * 1- Array notation
 * 2. Pointer notation
 *
 * To execute, run the following command:
 *
 * make one-dimensional-array
 * ./one-dimensional-array
 */

/* Using array notation */
void displayArrayUsingArrayNotation(int arr[], int size) {
	printf("displayArrayUsingArrayNotation() \n");
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}

	printf("\n");
}

/* Using pointer notation */
void displayArrayUsingPointerNotation(int* arr, int size) {
	printf("displayArrayUsingPointerNotation() \n");
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);  // This also works *(arr + i)
	}

	printf("\n");
}

int main() {
	int vector[5] = { 1, 2, 3, 4, 5 };
	int size = 5;
	displayArrayUsingArrayNotation(vector, size);

	displayArrayUsingPointerNotation(vector, size);

	return 0;
}
