
#include <stdio.h>

/*
	Command-line Arguments

	In environments that support C, there is a way to pass command-line arguments
	or parameters to a program when it begins executing. When main is called,
	it is called with two arguments. The first (conventionally called argc, for
	argument count) is the number of command-line arguments the program was
	invoked with; the second (argv, for argument vector) is a pointer to an array
	of character strings that contain the arguments, one per string.
*/

int main(int argc, char *argv[]) {

	printf("\n--------------- Program Name ---------------\n");
	printf("%s", argv[0]);

	printf("\n--------------- Command line Arguments ---------------\n");
	int i;
	printf("[");
	for (i = 1; i < argc; i++) {
		printf("%s%s", argv[i], (i < argc - 1) ? ", " : "");
	}
	printf("]");
	printf("\n");
	return 0;
}