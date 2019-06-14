/*
 * fork.c
 *
 * This program makes use of fork(). This system call creates processes. Basically it clones
 * the program, and if fork() returns ZERO, it means that this is the son, otherwise is the
 * parent process.
 *
 * NOTE: write() is used instead of printf() because is not buffered. If you change write() for
 * printf(), a delay in the output will be noticed.
 *
 */

#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {

	printf("\nSize of int %d", (int)sizeof(int));

	char *msg = "\nFork()";
	write(STDOUT_FILENO, msg, strlen(msg) + 1);

	int pid = fork();

	if (pid == 0) {
		msg = "\nSON: This is the son";
		write(STDOUT_FILENO, msg, strlen(msg) + 1);
		msg = "\nSON: Sleeping zzzzzz";
		write(STDOUT_FILENO, msg, strlen(msg) + 1);
		sleep(3);
	} else {
		msg = "\nPARENT: Waiting for the SON";
		write(STDOUT_FILENO, msg, strlen(msg) + 1);
		wait(NULL);
		msg = "\nPARENT: The wait is over";
		write(STDOUT_FILENO, msg, strlen(msg) + 1);
	}
}
