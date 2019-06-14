/**
 * This program finds the minimum and maximum values in a given
 *  array.
 *
 * usage: ./findminmax_parallel <seed> <arraysize> <nprocess>
 *
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "measure.h"
#include "util.h"

void
createProcesses(int nprocess, Pair ranges[], int array[])
{
  int ppid = getpid();   // Parent pid
  int pids[nprocess];

  Result results[nprocess];
  int filedescriptors[nprocess][2];
  int nbytes;

  int i;
  char readbuffer[250];
  for (i = 0; i < nprocess; i++)
    {

      // Creating the pipe
      pipe(filedescriptors[i]);
      // Cloning the father
      int newpid = fork();
      if (newpid == 0)
        {
          /* Child process closes up input side of pipe */
          close(filedescriptors[i][0]);

          // Son Process
          int pid = getpid();
          Pair range = ranges[i];
          int *ptr = array;
          ptr += range.first;
          Result result = findMinAndMax(ptr, range.second);
          sprintf(readbuffer, "%d %d", result.minimum, result.maximum);

          // printfMessage("\nSend string: ");
          // printfMessage(readbuffer);

          write(filedescriptors[i][1], readbuffer, (strlen(readbuffer) + 1));
          close(filedescriptors[i][1]);
          exit(0);
        }
      else
        {
          if (newpid == -1)
            {
              // #define	ENOMEM		12		/* Cannot allocate memory */
              printf("\nThere was a problem creating the process. ERROR [%d]",
                  errno);
              exit(1);
            }

          close(filedescriptors[i][1]);

          // Parent process
          pids[i] = newpid; // It saves the son's pid.

        }
    }

  for (i = 0; i < nprocess; i++)
    {
      nbytes = read(filedescriptors[i][0], readbuffer, sizeof(readbuffer));

      // printfMessage("\nReceived string: ");
      // printfMessage(readbuffer);

      results[i] = getResultsFromString(readbuffer);

      close(filedescriptors[i][0]);
    }

  printf("\nPARENT [%d] is processing results\n", ppid);

  Result finalResult = results[0];
  printf("\nPartial Result 0 [%d, %d]", results[0].minimum, results[0].maximum);
  for (i = 1; i < nprocess; i++)
    {
      printf("\nPartial Result %d [%d, %d]", i, results[i].minimum,
          results[i].maximum);
      if (finalResult.minimum > results[i].minimum)
        {
          finalResult.minimum = results[i].minimum;
        }
      if (finalResult.maximum < results[i].maximum)
        {
          finalResult.maximum = results[i].maximum;
        }
    }

  printf("\n\nFINAL RESULT [%d, %d]", finalResult.minimum, finalResult.maximum);
}

int
main(int argc, char *argv[])
{
  // Verifies the command line arguments.
  if (argc != 4)
    {
      printf("usage: ./findminmax_pipes <seed> <arraysize> <nprocess>\n");
      return 1;
    }

  printfMessage("\nExecuting using PIPES\n");
  // This message is printf several times because the output is buffered
  // printf("%s", msg);

  // Setting the parameters
  int seed = atoi(argv[1]);
  int arraysize = atoi(argv[2]);
  int nprocess = atoi(argv[3]);

  executeTemplate(createProcesses, seed, arraysize, nprocess);

  return 0;
}

