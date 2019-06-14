
/** 
 * This program finds the minimum and maximum values in a given
 *  array.
 * 
 * usage: ./findminmax_parallel <seed> <arraysize> <nprocess>
 *
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#include "../../../../the-c-programming-language/projects/find-max-min/parallel/measure.h"
#include "../../../../the-c-programming-language/projects/find-max-min/parallel/util.h"

/**
 * This function find the minimum and maximum in a array sequentially.
 */
void sequentialExecution(int seed, int size) {
	// Creating and initializing the array.
	int *array = createIntArray(size);
	initWithRandomData(array, size, seed);

	/* begin computation */
    mtf_measure_begin();
	Result result = findMinAndMax(array, size);

	// End of the computation
	mtf_measure_end();

	// Prints the execution time.
    printf("Execution time: ");
    mtf_measure_print_seconds(1);

	printf("Minimum %d, Maximum %d\n", result.minimum, result.maximum);

	deleteArray(array);
}

/* This function is in charge of reading the results from the files
   created by the children and find out what it is the minimum and
   maximum values.
  
*/
void processResultsByParent(int nprocess, int ppid, int pids[]) {
	int processresults[nprocess];
	int j;
	for (j = 0; j < nprocess; j++) {
		processresults[j] = -1;
	}

	char fileName[250];
	int processFiles = 0;
	Result finalResult;
	int k = 0;
	while (1) {
		if (processresults[k % nprocess] == -1) {
			// printf("Examing pid [%d]\n", pids[k % nprocess]);
			setFileName(fileName, ppid, pids[k % nprocess]);
			if (fileExists(fileName)) {
				Result result = getResults(fileName);
				printf("PARENT: Results from file %s: [%d, %d]\n",
					fileName, result.minimum, result.maximum);
				processFiles++;
				if (processFiles == 1) {
					finalResult.minimum = result.minimum;
					finalResult.maximum = result.maximum;
				} else {
					if (finalResult.minimum > result.minimum) {
						finalResult.minimum = result.minimum;
					}

					if (finalResult.maximum < result.maximum) {
						finalResult.maximum = result.maximum;
					}
				}
				remove(fileName);
				
				processresults[k % nprocess] = 1;
				if (processFiles == nprocess) {
					break; // Break the loop
				}
			}
		}
		k++;
	}

	printf("PARENT: Final RESULT Minimum %d, Maximum %d\n", finalResult.minimum, finalResult.maximum);
}

void createProcesses(int nprocess, Pair ranges[], int array[]) {
	int ppid = getpid();   // Parent pid
	char fileName[250];
	int pids[nprocess];

	int i;
	for (i = 0; i < nprocess; i++) {
		int newpid = fork();
		if (newpid == 0) {
			// Son Process
			int pid = getpid();
			Pair range = ranges[i];
			int *ptr = array;
			ptr += range.first;
			Result result = findMinAndMax(ptr, range.second);
			//printf("SON [%d] saving results [%d, %d]\n", pid, result.minimum, result.maximum);
			setFileName(fileName, ppid, pid);
			saveResults(result, fileName);
			exit(1);
		} else {
			// Parent process
			pids[i] = newpid; // It saves the son's pid.
		}
	}

	printf("\nPARENT [%d] is processing results\n", ppid);
	processResultsByParent(nprocess, ppid, pids);
}

void parallelExecution(int seed, int arraysize, int nprocess) {
		// Create and initialize the array
	int *array = createIntArray(arraysize);
	initWithRandomData(array, arraysize, seed);

	// Getting the ranges
	Pair ranges[nprocess];
	setRanges(ranges, arraysize, nprocess);

	/* begin computation */
    mtf_measure_begin();

	// Creating the subprocess
	createProcesses(nprocess, ranges, array);

	// End of the computation
	mtf_measure_end();

	// Prints the execution time.
    printf("Execution time: ");
    mtf_measure_print_seconds(1);

	deleteArray(array);
}

int main(int argc, char *argv[]) {
	// Verifies the command line arguments.
	if (argc != 4) {
		printf("usage: ./findminmax_parallel <seed> <arraysize> <nprocess>\n");
		return 1;
	}

	// Setting the parameters
	int seed = atoi(argv[1]);
	int arraysize = atoi(argv[2]);
	int nprocess = atoi(argv[3]);

	parallelExecution(seed, arraysize, nprocess);

	// sequentialExecution(seed, arraysize);

	return 0;
}

