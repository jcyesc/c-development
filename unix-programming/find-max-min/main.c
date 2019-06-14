/*
 * main.c
 *      Author: jcyescas
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "measure.h"
#include "util.h"

int main(int argc, char *argv[]) {
	testingSavingResults();
	return 0;
}

void testingSetFileName() {
	char fileName[250];

	setFileName(fileName, 23, 24);

	printf("\n%s", fileName);
}

void testingGetResults() {
	char *fileName = "data.txt";

	Result result;
	result.minimum = 223;
	result.maximum = 343;

	saveResults(result, fileName);

	Result current = getResultsFromFile(fileName);
	printf("\nResults [%d, %d]", current.minimum, current.maximum);
}

void testingFileExists() {
	char *file = "file.txt";

	if (fileExists(file)) {
		printf("File exists: %s", file);
	} else {
		printf("File doesn't exist: %s", file);
	}
}

void testingSavingResults() {
	Result result;
	result.minimum = 23;
	result.maximum = 111113232;

	printf("Saving data");
	saveResults(result, "file.txt");
}

void testingSetRanges() {
	int numarrays = 3;
	int nelements = 101;
	Pair ranges[numarrays];

	printf("Num arrays[%d], elements[%d]", numarrays, nelements);
	setRanges(ranges, nelements, numarrays);

	int i;
	for (i = 0; i < numarrays; i++) {
		printf("\nRanges[start-position, quantity] [%d, %d]", ranges[i].first,
				ranges[i].second);
	}
}

void testingCreatingArray() {
	printf("\nCreating array\n");
	int size = 10;
	int *ptr = createIntArray(size);

	initWithRandomData(ptr, size, 1);

	printIntfArray(ptr, size);

	deleteArray(ptr);
}

void testingFindMinAndMax() {
	int a[5] = { 5, 4, 3, 2, 1 };
	int *ptr = a;
	Result result;
	result = findMinAndMax(ptr, 5);
	printf("\nResult [%d, %d]", result.minimum, result.maximum);

	result = findMinAndMax(++ptr, 4);
	printf("\nResult [%d, %d]", result.minimum, result.maximum);

	result = findMinAndMax(++ptr, 3);
	printf("\nResult [%d, %d]", result.minimum, result.maximum);
}
