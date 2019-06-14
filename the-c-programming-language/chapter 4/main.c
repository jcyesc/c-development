#include "stdio.h"


/*
   External variables

   This example shows how to declare and use external variables.

   How to compile

   gcc main.c functions.c
*/

// This is an external variable and is declared in functions.c
int counter = 0;

int main() {

	printf("Invoking external functions\n");
	increase();
	printCounter();
}