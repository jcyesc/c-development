/*
 * PIPES
 *
 * Creating "pipelines" with the C programming language can be a bit more
 * involved than our simple shell example. To create a simple pipe with C,
 * we make use of the pipe() system call. It takes a single argument, which is
 * an array of two integers, and if successful, the array will contain two new
 * file descriptors to be used for the pipeline. After creating a pipe, the
 * process typically spawns a new process (remember the child inherits open file
 * descriptors).
 *
 * The first integer in the array (element 0) is set up and opened for reading,
 * while the second integer (element 1) is set up and opened for writing.
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

void printMessage(char *msg);


int
main(void)
{
  int fd[2], nbytes;
  pid_t childpid;
  char string[] = "Hello, world!\n";
  char readbuffer[80];

  pipe(fd);

  if ((childpid = fork()) == -1)
    {
      perror("fork");
      exit(1);
    }

  if (childpid == 0)
    {
      printMessage("Child sleeping\n");
      sleep(10);
      /* Child process closes up input side of pipe */
      close(fd[0]);
      printMessage("Child writing\n");
      /* Send "string" through the output side of pipe */
      write(fd[1], string, (strlen(string) + 1));
      close(fd[1]);
      exit(0);
    }
  else
    {
      /* Parent process closes up output side of pipe */
      printMessage("Parent executing\n");
      close(fd[1]);
      printMessage("Parent reading\n");
      /* Read in a string from the pipe */
      nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
      printf("Received string: %s", readbuffer);

      close(fd[0]);
    }

  //nanosleep
  //select
  return (0);
}

void printMessage(char *msg)
{
  write(STDOUT_FILENO, msg, strlen(msg));
}
