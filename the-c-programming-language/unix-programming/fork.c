#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

/*
    Upon successful completion, fork() returns a value of 0 to the child
    process and returns the process ID of the child process to the parent
    process.  Otherwise, a value of -1 is returned to the parent process, no
    child process is created, and the global variable errno is set to indi-
    cate the error.
*/

int main() {

	int pid = fork();

	if (pid == 0) {
		printf("SON: %d\n", pid);
		//exit(0);
	} else {
		printf("FATHER, SON'S PID: %d\n", pid);
	}

	printf("Executing code, PID: %d\n", pid);
	return 0;
}