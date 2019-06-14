#include "stdio.h"

// This is an external variable and needs to be declared later.
extern int counter;

void increase() {
	counter++;
}

void printCounter() {
	printf("Counter %d\n", counter);
}