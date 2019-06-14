#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/file.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "measure.h"
#include "util.h"

/* given an array of ints and the size of array, find min and max values */
Result
findMinAndMax(int *subarray, int n)
{
  int i, min, max;
  min = max = subarray[0];
  Result result;

  for (i = 1; i < n; i++)
    {
      if (subarray[i] < min)
        {
          min = subarray[i];
        }
      if (subarray[i] > max)
        {
          max = subarray[i];
        }
    }

  result.minimum = min;
  result.maximum = max;
  return result;
}

/**
 * It creates an int array of the specific size.
 */
int *
createIntArray(int size)
{
  return (int *) malloc(sizeof(int) * size);
}

/**
 * This function returns the memory that was allocated by malloc.
 */
void
deleteArray(void *array)
{
  free(array);
}

/**
 * It initializes an int array with random  data.
 */
void
initWithRandomData(int *array, int size, int seed)
{
  char randomstate[8];
  initstate(seed, randomstate, 8);

  int i;
  for (i = 0; i < size; i++)
    {
      array[i] = random();
    }
}

/**
 * It prints the elements of the int array.
 */
void
printIntfArray(int *array, int size)
{
  int i;
  for (i = 0; i < size; i++)
    {
      printf("%d ", *array++);
    }
}

/*
 * setRanges()
 *
 * This function calculates the ranges of the array. Given the number
 * of elements and number of arrays, it generates numarrays ranges with
 * even number of elements or the last range will contain the remaining
 * of the division nelements / numarrays.
 *
 * Each Pair will contain in their properties:
 * 		first: starting point
 * 		second: the number of elements.
 */
void
setRanges(Pair ranges[], int nelements, int numarrays)
{

  int quantity = nelements / numarrays;
  int module = nelements % numarrays;

  ranges[0].first = 0;
  ranges[0].second = quantity;

  int i;
  int position = quantity;
  for (i = 1; i < numarrays; i++, position += quantity)
    {
      ranges[i].first = position;
      ranges[i].second = quantity;
    }

  if (i > 1)
    {
      ranges[i - 1].second += module;
    }
}

/* It saves the results in the given file. The file format is ASCII and
 *
 * the data has the following format:
 *
 *   %d %d
 *
 *  The first parameter contains the minimum and the second the maximum.
 */
void
saveResults(Result result, char *fileName)
{
  int fileDescriptor = creat(fileName, 0777);

  int n = 250;
  char buffer[n];
  int nChars = sprintf(buffer, "%d %d", result.minimum, result.maximum);

  int nWritten = write(fileDescriptor, buffer, nChars);
  fdatasync(fileDescriptor);

  if (nWritten <= 0 || nWritten != nChars)
    {
      printf("There was a error saving the file %s", fileName);
      printf("\nWritten %d expected %d", nWritten, nChars);
      exit(1);
    }
  close(fileDescriptor);
}
/*
 void saveResults(Result result, char *fileName) {
 FILE *file = fopen(fileName, "w+");

 fprintf(file, "%d %d", result.minimum, result.maximum);

 fclose(file);
 }
 */

/* It returns a number positive number if the file exists,
 otherwise it returns negative.
 */
int
fileExists(char *fileName)
{
  int fileDescriptor = open(fileName, O_RDONLY);

  if (fileDescriptor == -1)
    {
      return 0;
    }

  close(fileDescriptor);
  return 1;
}
/*
 int fileExists(char *fileName) {
 FILE *file;

 if ((file = fopen(fileName, "r")) == NULL) {
 return 0;
 }

 fclose(file);
 return 1;
 }
 */

/* It returns the a Result object that is store in the given File.
 In order to this function to succeed, it's necessary to validate
 that the file exists.

 The format of the string should be:

 "%d %d" The first parameter is minimum, the second parameter is maximum.
 */
Result
getResultsFromFile(char *fileName)
{
  int fileDescriptor = open(fileName, O_RDONLY);

  if (fileDescriptor == -1)
    {
      printf("\nError opening the file [%s]. Error [%d]", fileName, errno);
      exit(1);
    }

  int n = 250;
  char buffer[n];

  int nRead = read(fileDescriptor, buffer, n);
  if (nRead <= 0)
    {
      printf("\nThe file %s is EMPTY", fileName);
      exit(1);
    }

  int minimum, maximum;
  int nValues = sscanf(buffer, "%d %d", &minimum, &maximum);
  if (nValues != 2)
    {
      printf("\nThe format of the file %s is invalid", fileName);
      exit(1);
    }

  close(fileDescriptor);

  Result result;
  result.minimum = minimum;
  result.maximum = maximum;

  printf("\nData from file [%s]: [%d, %d]", fileName, result.minimum,
      result.maximum);
  return result;
}
/*Result getResultsFromFile(char *fileName) {
 FILE *file = fopen(fileName, "r");

 if (file == NULL) {
 printf("The file [%s] doesn't exist", fileName);
 exit(1);
 }

 Result result;
 int minimum, maximum;

 fscanf(file, "%d %d", &minimum, &maximum);
 fclose(file);

 result.minimum = minimum;
 result.maximum = maximum;
 return result;
 }
 */

/** It returns the Result object that is in the given string.

 The format of the string should be:

 "%d %d" The first parameter is minimum, the second parameter is maximum.
 */
Result
getResultsFromString(char *string)
{
  Result result;
  int minimum, maximum;

  sscanf(string, "%d %d", &minimum, &maximum);

  result.minimum = minimum;
  result.maximum = maximum;
  return result;
}

/*
 * Set the file name to results_ppid_pid. The fileName pointer has
 * the location of the file name.
 */
void
setFileName(char *fileName, int ppid, int pid)
{
  sprintf(fileName, "results_%d_%d", ppid, pid);
}

/*
 * This function defines the template to get the maximum and minimum elements.
 *
 * It receives a function that defines how the processes will be created and what they will do.
 */
void
executeTemplate(void
(*executeProcesses)(int, Pair[], int[]), int seed, int arraysize, int nprocess)
{
  // Create and initialize the array
  printfMessage("\nCreating array......");
  int *array = createIntArray(arraysize);
  if (array == NULL)
    {
      printfMessage("\nThe memory couldn't be allocated");
      exit(1);
    }

  printfMessage("\nInitializing array with random data.......");
  initWithRandomData(array, arraysize, seed);

  // Getting the ranges
  printfMessage("\nSetting the Ranges.......");
  Pair ranges[nprocess];
  setRanges(ranges, arraysize, nprocess);

  /* begin computation */
  mtf_measure_begin();

  // Creating the subprocess
  printfMessage("\nExecuting the processes......");
  executeProcesses(nprocess, ranges, array);

  // End of the computation
  mtf_measure_end();

  // Prints the execution time.
  printfMessage("\nExecution time: ");
  mtf_measure_print_seconds(1);

  deleteArray(array);
}

/** It prints a message. The message is not saved in the buffer.*/
void
printfMessage(char *msg)
{
  write(STDOUT_FILENO, msg, strlen(msg) + 1);
}
