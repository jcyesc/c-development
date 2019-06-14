/*
	This program implements different ways of the strcmp function. It uses
	pointers to implement it.

	NOTE:
		
		There is an important difference between these definitions:

			char amessage[] = "now is the time";	// an array
			char *pmessage = "now is the time";		// a pointer

		amessage is an array, just big enough to hold the sequence of characteres
		and '\0' that initializes it. Individual characters within the array may be
		change but amessage will always refer to the same storage. On the other hand,
		pmessage is a pointer, initialized to point o a string constant; the pointer
		may subsequently be modified to point elsewhere, but the result is undefined if
		you try to modify the string contents.
*/

#include <stdio.h>

/*
	This method compares the character  strings s and t, and returns negative, zero
	or positive if s is lexicographically less than, equal to, or greater than t. The
	value is obtained by substracting the characters at the first position where s and t
	disagree.
*/
int strcmp_1(char *s, char *t);

int strcmp_2(char *s, char *t);

void printResult(char *s1, char *s2, int result);

int main() {

	char *str1 = "First string";
	char *str2 = "First element";
	char *str3 = "First string";

	// Array version
	printf("Array version\n");
	printResult(str1, str2, strcmp_1(str1, str2));
	printResult(str1, str3, strcmp_1(str1, str3));

	// Pointer version
	printf("\nPointer version\n");
	printResult(str1, str2, strcmp_2(str1, str2));
	printResult(str1, str3, strcmp_2(str1, str3));

	// If there is not return statement, the default value is zero.
}

void printResult(char *s1, char *s2, int result) {
	printf("Are they equals ['%s', '%s']: %s\n", s1, s2, (result ? "NO" : "YES"));
}

// Array version
int strcmp_1(char *s, char *t) {
	int i;

	for (i = 0; s[i] == t[i]; i++) {
		if (s[i] == '\0') {
			return 0;
		}
	}

	return s[i] - t[i];
}

// Pointer version
int strcmp_2(char *s, char *t) {
	for (; *s == *t ; s++, t++) {
		if (*s == '\0') {
			return 0;
		}
	}

	return *s - *t;
}

