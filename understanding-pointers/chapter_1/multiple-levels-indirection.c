
#include <stdio.h>

/**
 * Multiple levels of indirection
 *
 * It is not uncommon to see a variable declared as a pointer to
 * a pointer, sometimes called a double pointer.
 *
 * Execute
 *
 * make multiple-levels-indirection
 * ./multiple-levels-indirection
 *
 */

int main() {

	char *titles[] = {
			"A Tale of Tow Cities",
			"Wuthering Heights",
			"Don Quixote",
			"Odyssey",
			"Mobby-Dick",
			"Hamlet",
			"Gulliver's Travels" };

	// Each array element contains a pointer
	// that points to a second pointer to char.
	char **bestBooks[3];
	bestBooks[0] = &titles[0];
	bestBooks[1] = &titles[3];
	bestBooks[2] = &titles[5];

	printf("Best book 1:            `%s`\n", *bestBooks[0]);
	printf("First letter of book 1: `%c`\n", **bestBooks[0]);
	printf("Best book 2:            `%s`\n", *bestBooks[1]);
	printf("First letter of book 2: `%c`\n", **bestBooks[1]);
	printf("Best book 3:            `%s`\n", *bestBooks[2]);
	printf("First letter of book 3: `%c`\n", **bestBooks[2]);

	return 0;
}
