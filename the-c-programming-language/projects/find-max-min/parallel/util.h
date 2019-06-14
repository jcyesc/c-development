
/* util.h
  
  This header contains the main data structures and function signature
  that are used across the application.

*/

  /* a struct that stores the min a max value. */
typedef struct result {
    int minimum;
    int maximum;
} Result;

/* a struct that stores two pair of values. */
typedef struct pair {
    int first;
    int second;
} Pair;

/* given an array of ints and the size of array, find min and max values */
Result findMinAndMax(int *subarray, int n);

/**
 * It creates an int array of the specific size.
 */
int * createIntArray(int size);

/**
 * This function returns the memory that was allocated by malloc.
 */
void deleteArray(void *array);

/**
 * It initializes an int array with random  data.
 */
void initWithRandomData(int array[], int size, int seed);

/**
 * It prints the elements of the int array.
 */
void printIntfArray(int *array, int size);

/*
 * setRanges()
 *
 * This function calculates the ranges of the array. Given the number
 * of elements and number of arrays, it generates numarrays ranges with
 * even number of elements or the last range will contain the remaining
 * of the division nelements / numarrays.
 */
void setRanges(Pair pairs[], int nelements, int numarrays);

/* It saves the results in the given file. The file format is ASCII and
   the data has the following format:

   %d %d

   The first parameter contains the minimum and the second the maximum.
*/
void saveResults(Result result, char *fileName);

/* It returns a number positive number if the file exists,
otherwise it returns negative.
*/
int fileExists(char *fileName);

/* It returns the a Result object that is store in the given File.
   In order to this function to succeed, it's necessary to validate
   that the file exists.
*/
Result getResults(char *fileName);

/*
 * Set the file name of the file to Results_ppid_pid.
 */
void setFileName(char *fileName, int ppid, int pid);



