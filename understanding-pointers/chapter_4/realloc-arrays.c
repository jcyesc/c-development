#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Using the realloc Function to Resize an Array.
 *
 * We can resize an existing array created using malloc() with the
 * realloc() function. The C standard C99 supports variable length arrays.
 * In some situations, this may prove to be a better solution than using
 * the realloc() function. If you are not using C99, then the realloc()
 * function will need to be used. Also, variable length arrays can only be
 * declared as a member of a function. If the array is needed longer than
 * the function's duration, then realloc() will need to be used.
 */

/**
 * Reads characters from standard input and assign them to a buffer. The
 * buffer will contain all of the characters read in except for a terminating
 * return character. Since we do not know how many characters the user will
 * input, we do not know how long the buffer should be. We will use the
 * realloc function to allocate additional space by a fixed increment amount.
 *
 * Notice that we did not free buffer if realloc was successful because
 * realloc will copy the original buffer to the new buffer and free up the
 * old buffer. If we have tried to free buffer, then it would normally
 * result in the program termination because we tried to free the same block
 * of memory twice.
 *
 */
char *getLine(void) {
	const size_t sizeIncrement = 10;
	char* buffer = malloc(sizeIncrement);
	char* currentPosition = buffer;
	size_t maximumLength = sizeIncrement;
	size_t length = 0;
	int character;

	if (currentPosition == NULL) {
		return NULL;
	}

	while (1) {
		character = fgetc(stdin);
		if (character == '\n') {
			break;
		}

		if (++length >= maximumLength) {
			char *newBuffer = realloc(buffer, maximumLength += sizeIncrement);

			if (newBuffer == NULL) {
				free(buffer);
				return NULL;
			}

			currentPosition = newBuffer + (currentPosition - buffer);
			buffer = newBuffer;
		}
		*currentPosition++ = character;
	}

	*currentPosition = '\0';
	return buffer;
}

/**
 * The realloc function can also be used to decrease the amount of space used by
 * a pointer. To illustrate its use, the trim function shown below will remove
 * leading blanks in a string.
 */
char* trim(char *phrase) {
	char* old = phrase;
	char* new = phrase;

	while(*old == ' ') {
		old++;
	}

	while(*old) {
		// *(new++) = *(old++);
		*new++ = *old++;
	}
	*new = 0;
	return (char *) realloc(phrase, strlen(phrase) + 1);
}

int main() {
	printf("Enter one line: ");
	char *line = getLine();
	printf("The input is: '%s' \n", line);

	char *buffer = (char *) malloc(strlen(" cat") + 1);
	strcpy(buffer, "  cat");
	buffer = trim(buffer);
	printf("After trim '%s' \n", buffer);

	return 0;
}








