#include <stdio.h>
#define MAXLINE 1000 // Maximum input line size

/*

 This program prints the longest input line that it finds.
 
 How to execute the program
 
 ./a.out
 String one
 This line is longer
 This is the longest line
 This is other line
 This is the longest line

 Press Ctrl-D
 
 */
int getLine(char line[], int maxline);
void copy(char to[], char from[]);

// print longest input line
int main() {
    int len;                // current line length
    int max;                // maximum length seen so far.
    char line[MAXLINE];     // current input line
    char longest[MAXLINE];  // longest line saved here
    
    max = 0;
    while ((len = getLine(line, MAXLINE)) > 0 ) {
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    }

    if (max > 0)  // there was a line
        printf("%s", longest);

    return 0;
}

// getline: read a line into s, return length.
int getLine(char s[], int lim) {
    int c, i;
    
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }
    
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

// copy: copy 'from' into 'to'; assume to is big engough
void copy(char to[], char from[]) {
    int i = 0;
    
    while ((to[i] = from[i]) != '\0')
        ++i;
}













