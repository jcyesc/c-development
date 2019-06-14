/*
 *  Created by Juan Carlos Yescas on 1/24/13.
 * 
 * Arrays
 *
 * This program counts the number of occurrences of each digit, of
 * white space characters (blank, tab, newline), and of all other characters.
 *
 * There are twelve categories of input, so it is convenient to use an array
 * to hold the number of occurrences of each digit, rather than ten individual
 * variables.
 *
 * How to execute this program
 *
 * ./a.out
 * Enter 1 2 3 4 5 6
 * and then press Crtl-d
 *
 */

#include <stdio.h>

/* Count digits, white space, others */

int main() {
    int c, i, nwhite, nother;
    int ndigit[10];

    nwhite = nother = 0;
    for (i = 0; i < 10; ++i)
        ndigit[i] = 0;

    while ((c = getchar()) != EOF) {
        if (c >= '0' && c <= '9')
            ++ndigit[c - '0'];
        else if (c == ' ' || c == '\n' || c == '\t')
            ++nwhite;
        else
            ++nother;
    }

    printf("digits = ");
    for (i = 0; i < 10; ++i)
        printf(" %d", ndigit[i]);
    printf(", white space = %d, other %d\n", nwhite, nother);
    return 0;
}
