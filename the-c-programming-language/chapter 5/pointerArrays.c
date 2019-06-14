#include <stdio.h>

/*
	This program prints the lines that are passed to the printlines method.

	In addition to this, it provides a method to print character by character.
*/

// Print the lines.
void printlines(char *lines[], int nlines);

// Print the characteres of the sentence seperated by white space.
void printcharacters(char *line);

int main() {
	char *lines[] = {"Life is wonderful", "Work hard", "Improve yourself everyday"};

	printf("---------PRINT LINES---------\n");
	printlines(lines, 3);

	printf("\n---------PRINT CHARACTERS---------\n");
	printcharacters(lines[0]);

}

void printlines(char *lines[], int nlines) {
	int i;
	for (i = 0; i < nlines; i++) {
		printf("%s\n", lines[i]);
	}
}

void printcharacters(char *line) {
	char c;
	while ((c = *line++) != '\0') {
		printf("%c ", c);
	}
	printf("\n");
}