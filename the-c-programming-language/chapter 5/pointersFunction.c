#include <stdio.h>


/*
	Pointer to Functions and Illegal Memory Access

	This program shows how to declare and use pointer to functions. In
	addition to this, it shows how to access to illegal memory location
	using arithmetic pointer.
*/


/*
	This function receives a generic array and print it.
*/
void printArray(void *array[], int numElements);

void printIntPointersArray(int *array[], int numElements);

/*
	Print the int values and access to illegal memory addresses.
*/
void printIntPointersOverflow(int *array[], int numElements);

int main() {

	// Pointer to a function
	void (*pFunction)(void *array[], int);

	// Assigning the function
	pFunction = printArray;

	printf("---------- Printing strings ----------\n");
	char *strings[] = {"An", "array", "of", "string", "pointers"};
	
	// Deferencing the function and calling it.
	(*pFunction)(strings, 5);

	printf("\n\n---------- Printing ints ----------\n");
	int val1 = 34;
	int val2 = 60;

	int *pInt1 = &val1;
	int *pInt2 = &val2;

	int *array[] = {pInt1, pInt2};

	// Print array without deferencing the ints.
	printArray(array, 2);

	// Print array deferencing the ints.
	printIntPointersArray(array, 2);


	printf("\n\n---------- Printing array of ints with and without overflow----------\n");

	int array1[] = {5, 6, 7};
	int array2[] = {8, 9, 10};

	int *arrayOfarrays[] = {array1, array2};

	// Print array deferencing the ints. It will only print the first element of each array.
	printIntPointersArray(arrayOfarrays, 2);

	printf("\n@@@@ Reading illegal memory @@@@\n");
	printIntPointersOverflow(arrayOfarrays, 2);
}

void printArray(void *array[], int numElements) {
	int i;
	for (i = 0; i < numElements; i++) {
		// If it is an array of characters, print the string,
		// otherwise it prints the address.
		printf(array[i]);
		printf("\n");
	}
}

void printIntPointersArray(int *array[], int numElements) {
	int i = 0;
	for (i = 0; i < numElements; i++) {
		printf("[%d] = %d\n", array[i], *array[i]);
	}
}

void printIntPointersOverflow(int *array[], int numElements) {
	int i;
	for (i = 0; i < numElements; i++) {
		int j;
		// Accessing to illegal memory addresses.
		for (j = 0; j < 10; j++) {
			printf("[%d] = %d\n", array[i] + j, *(array[i] + j));
		}
	}	
}









