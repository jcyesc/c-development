/**
	Pointers and Arrays

	This program examplifies the use of pointers to calculate the length of a string. In
	order to achieve this, it uses address arithmetic.
*/

#include <stdio.h>

int strlen(char *p);

int main() {
	char *string = "Learning C";
	int length = strlen(string);
	printf("\nThe length of '%s' is %d\n", string, length);
}

/**
	This method calculates the lenght of the string. It receives a pointer
	to the first element of the string.
*/
int strlen(char *p) {
	char *pointer = p;

	while (*pointer != '\0') {
		printf("%c ", *pointer);
		pointer++;
	}

	printf("\nAddresses [Start, Last] : [%d, %d] : Distance: %d", p, pointer, pointer - p);
	return pointer - p;
}