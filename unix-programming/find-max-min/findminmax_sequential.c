/**
 * This program finds the minimum and maximum values in a given
 *  array.
 *
 * usage: ./findminmax_sequential <seed> <arraysize> <nprocess>
 *
 */

#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "measure.h"
#include "util.h"

/**
 * This function find the minimum and maximum in a array sequentially.
 */
void
sequentialExecution(int seed, int size)
{
  // Creating and initializing the array.
  printf("\nCreating array of %d elements ............", size);
  int *array = createIntArray(size);
  if (array == NULL)
    {
      printf("\nThe memory couldn't be allocated............");
      exit(1);
    }

  initWithRandomData(array, size, seed);

  printf("\nFinding the Max and Min ............");
  // begin computation
  mtf_measure_begin();
  Result result = findMinAndMax(array, size);

  // End of the computation
  mtf_measure_end();

  // Prints the execution time.
  printf("\nExecution time: ");
  mtf_measure_print_seconds(1);

  printf("Minimum %u, Maximum %u\n", result.minimum, result.maximum);

  deleteArray(array);
}

int
main(int argc, char *argv[])
{
  // Verifies the command line arguments.
  if (argc != 3)
    {
      printf("usage: ./findminmax_sequential <seed> <arraysize>\n");
      return 1;
    }

  char *msg = "\nExecuting Sequential program";
  write(STDOUT_FILENO, msg, strlen(msg) + 1);
  // This message is printf several times because the output is buffered
  // printf("%s", msg);

  // Setting the parameters
  int seed = atoi(argv[1]);
  int arraysize = atoi(argv[2]);

  sequentialExecution(seed, arraysize);

  return 0;
}

