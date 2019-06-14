/* printf.c - program to demonstrate printf output */

#include<stdio.h>

int main(int argc, char **argv)
{
        char name[] = "Some string";
        int i,j;
        float fi;
        double di;
        int *ptr;

        /* use %s to print a string, \n is a "newline" */
        printf("Here is: %s\n", name);

        /* usr %d to print integers */
        /* just use multiple specifiers to print multiple variables */
        i = 16;
        j = 32768;
        printf("i is %d  and j is %d\n", i, j);

        /* use %f to print a float */
        fi = 22.0/7.0;
        printf("fi is %f\n", fi);

        /* use %lf to print a double */
        /* also can specify the "format" */
        di = 22.0/7.0;
        printf("di is %2.20lf\n", di);
        printf("fi is %2.20lf\n", fi);

        /* use %X and %x to print in hexidecimal (good for pointers) */
        ptr = &i;
        printf("ptr is %X\n", ptr);
        printf("ptr is %x\n", ptr);

        /* use %c to print a single character */
        printf("%c%c%c\n", 'a', 'b', 99);

        /* stdout and stderr */
        printf("Hello there printf\n");
        fprintf(stdout, "Hello there fprintf\n");
        fprintf(stderr, "Hello there stderr\n");
        printf("sizeof(int) = %d\n", sizeof (int));
        printf("sizeof(int *) = %d\n", sizeof (int *));

        return 0;
}