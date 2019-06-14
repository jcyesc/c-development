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

/* This function is in charge of reading the results from the files
 created by the children and find out what it is the minimum and
 maximum values.

 */
void
processResultsByParent(int nprocess, int ppid, int pids[])
{
  int processresults[nprocess];
  int j;
  for (j = 0; j < nprocess; j++)
    {
      processresults[j] = -1;
    }

  char fileName[250];
  int processFiles = 0;
  Result finalResult;
  int k = 0;
  while (1)
    {
      if (processresults[k % nprocess] == -1)
        {
          //printf("Examing pid [%d]\n", pids[k % nprocess]);
          setFileName(fileName, ppid, pids[k % nprocess]);
          if (fileExists(fileName))
            {
              Result result = getResultsFromFile(fileName);
              //printf("PARENT: Results from file %s: [%d, %d]\n",
              //	fileName, result.minimum, result.maximum);
              processFiles++;
              if (processFiles == 1)
                {
                  finalResult.minimum = result.minimum;
                  finalResult.maximum = result.maximum;
                }
              else
                {
                  if (finalResult.minimum > result.minimum)
                    {
                      finalResult.minimum = result.minimum;
                    }

                  if (finalResult.maximum < result.maximum)
                    {
                      finalResult.maximum = result.maximum;
                    }
                }
              remove(fileName);

              processresults[k % nprocess] = 1;
              if (processFiles == nprocess)
                {
                  break; // Break the loop
                }
            }
        }
      k++;
    }

  printf("\nPARENT: FINAL RESULT [%d, %d]\n", finalResult.minimum,
      finalResult.maximum);
}

void
createProcesses(int nprocess, Pair ranges[], int array[])
{
  int ppid = getpid();   // Parent pid
  char fileName[250];
  int pids[nprocess];

  int i;
  for (i = 0; i < nprocess; i++)
    {
      int newpid = fork();
      if (newpid == 0)
        {
          // Son Process
          int pid = getpid();
          Pair range = ranges[i];
          int *ptr = array;
          ptr += range.first;
          Result result = findMinAndMax(ptr, range.second);
          printf("\nSON [%d] saving results [%d, %d]", pid, result.minimum,
              result.maximum);
          setFileName(fileName, ppid, pid);
          saveResults(result, fileName);
          exit(1);
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

          // Parent process
          pids[i] = newpid; // It saves the son's pid.
        }
    }

  // Only the parent waits for the children.
  wait(NULL);
  printf("\nPARENT [%d] is processing results\n", ppid);
  processResultsByParent(nprocess, ppid, pids);
}

int
main(int argc, char *argv[])
{
  // Verifies the command line arguments.
  if (argc != 4)
    {
      printf("usage: ./findminmax_parallel <seed> <arraysize> <nprocess>\n");
      return 1;
    }

  char *msg = "\nExecuting Parallel program";
  write(STDOUT_FILENO, msg, strlen(msg) + 1);
  // This message is printf several times because the output is buffered
  // printf("%s", msg);

  // Setting the parameters
  int seed = atoi(argv[1]);
  int arraysize = atoi(argv[2]);
  int nprocess = atoi(argv[3]);

  executeTemplate(createProcesses, seed, arraysize, nprocess);

  return 0;
}

