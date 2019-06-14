#include <stdio.h>

/*
 * array_structs.c
 *
 *  Created on: Sep 22, 2013
 *      Author: jcyescas
 */

#define SIZE_ACCOUNTS 3

struct Account {
	int id;
	double amount;
	char *description;
};

struct Account accounts[SIZE_ACCOUNTS];

int main() {
	printf("Array of Structs\n");

	// Initializing structs
	int i;
	for (i = 0; i < SIZE_ACCOUNTS; i++) {
		accounts[i].id = i + 1;
		accounts[i].amount = 3.1416 * i;
		accounts[i].description = "description";
	}

	for (i = 0; i < SIZE_ACCOUNTS; i++) {
		printf("Account [%d]: Id [%d], Amount [%f], Description: %s\n",
			i, accounts[i].id, accounts[i].amount, accounts[i].description);
	}

	return 0;
}
