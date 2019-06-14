/* This program exemplifies the use of functions.
 *
 */

#include <stdio.h>

int power(int m, int n);

// Test power function
int main() {
    int i = 0;

    for (i = 0; i < 10; i++)
        printf("%d %d %d\n", i, power(2,i), power(-3, i));

    return 0;
}

/*
 A note of history
 
 The biggest change between ANSI C and earlier versions is how functions
 are declared and defined. In the original definition of C, the power function
 would have been written like this:
 */
power(base, n)
int base, n;
{
    int i, p;
    p = 1;
    for (i = 1; i <= n; ++i) {
        
        p = p * base;
    }
    return p;
}