#include <stdio.h>

#define IN  1     // Inside a word
#define OUT 0     // Outside a word

/*
 * This program counts lines, words, and characters, with the
 * loose definition that a word is any sequence of characters that
 * does not contain a blank, tab or newline. This is a bare-bones version
 * of the UNIX program wc.
 *
 * How to execute the program:
 * 
 *  more file.txt | ./a.out 
 *
 *         or
 *
 *  ./a.out 
 *  ENTER SOMETHING AND WHEN YOU ARE DONE TYPE Ctrl-D.
 *
 */

// Count lines, words, and characters in input
int main() {
    int c;
    int nl;
    int nw;
    int nc;
    int state;
    
    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n')
            nl++;
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            nw++;
        }
            
    }
    
    printf("%d %d %d\n", nl, nw, nc);
           
           return 0;
}
