#include <stdio.h>

/* Copy input to output; 1st version */

int main() {
    int c;

    c = getchar();
    while (c != EOF) {
        putchar(c);
        c = getchar();
    }

    // Ctrl-d to represent End of File.
    if (c == EOF) {
    	printf("End of file\n");
    }
}
