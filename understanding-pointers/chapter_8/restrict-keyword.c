
#include <stdio.h>

/**
 * restrict Keyword
 *
 * C compilers assume pointers are aliased by default. Using the restrict
 * keyword when declaring a pointer tells the compiler that the pointer is not
 * aliased. This gives the signal to the compiler to generate optimized code. It
 * also means that the programmer should not alias the pointers, otherwise, the
 * results of the operation are undefined.
 *
 * When a pointer is marked as restrict, the compiler might not reload the value
 * at the address that the pointer is pointing for optimization reasons.
 */


void add(size_t size, double * restrict arr1, const double * restrict arr2) {
	for (int i = 0; i < size; i++) {
		arr1[i] += arr2[i];
	}
}

void display(size_t size,  const double * const arr) {
	for (int i = 0; i < size; i++) {
		printf("%f ", arr[i]);
	}

	printf("\n");
}

int main() {
	double vector1[] = {1.1, 2.2, 3.3, 4.4};

	/**
	 * Due we are using restrict, the results might sometimes work correctly
	 * when there are several alias for a pointer.
	 */
	size_t size = 4;
	double *vector3 = vector1;
	add(size, vector1, vector3);
	display(size, vector1);
	add(size, vector1, vector1);
	display(size, vector1);

	return 0;
}


