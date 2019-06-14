#include <stdio.h>
#include <stdlib.h>

/*
	Table lookup

	This program implements a table lookup and shows the internal
	details of the table lookup, in this case the hash table.

	The hash function that is implemented here is not very efficient
	but it works for our example.
*/

#define HASHSIZE 101

typedef struct node {
	struct node *next;
	char *name;
	char *value;
} Node;

/* Hash table */
static Node *hashtable[HASHSIZE];

/* 
	Hash Function

	The hashing function, which is used by lookup and install, adds
	each character value in the string to a scrambled combination of the
	previous ones and returns the remainder modulo the array size. This is
	not the best posible hash function, but it is short and effective.
*/
unsigned hash(char *s) {
	/* Unsigned arithmetic ensures that the hash value is non-negative. */
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++) {
		hashval = *s + 31 * hashval;
	}

	return hashval % HASHSIZE;
}

Node *lookup(char *s) {
	Node *np;

	for (np = hashtable[hash(s)]; np != NULL; np = np->next) {
		if (strcmp(s, np->name) == 0)
			return np;	// Found
	}

	return NULL;
}

void install(char *name, char *value) {
	Node *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) { // Not  found
		np = (Node *) malloc (sizeof(Node));
		np->next = NULL;
		np->name = name;
		np->value = value;
		hashval = hash(name);
		np->next = hashtable[hashval];
		hashtable[hashval] = np;
	} else { // Found
		np->value = value;
	}
}

int main() {
	char *keys[] = {"one", "two", "three"};
	char *values[] = {"1", "2", "3"};
	int length = 3;
	Node *np;

	printf("Installing keys\n");
	int i;
	for (i = 0; i < length; i++) {
		install(keys[i], values[i]);
	}

	printf("\nPrinting key value pairs\n");
	for (i = 0; i < length; i++) {
		np = lookup(keys[i]);
		printf("Key[%s] - Value[%s]\n", keys[i], (np != NULL ? np->value : "NULL"));
	}

	char *key = "NO EXIST";
	np = lookup(key);
	printf("Key[%s] - Value[%s]\n", key, (np != NULL ? np->value : "NULL"));
}

