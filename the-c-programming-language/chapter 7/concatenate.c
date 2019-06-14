#include <stdio.h>

/* cat: concatenate files
 * 
 * This program is in charge of concatenating the files to the standard output.
 *
 * The file pointers stdin and stdout are objects of type FILE *. They are constants, however,
 * not variables, so it is not possible to assign to them.
 */

int main(int argc, char *argv[]) {
  FILE *fp;
  void filecopy(FILE *, FILE *);

  if (argc == 1) { /* no args: copy standard input */
    filecopy(stdin,  stdout);      
  } else {
  	while (--argc > 0) {
      if ((fp = fopen(*++argv, "r")) == NULL) {
        printf("cat: can't open %s\n", *argv);
        return 1;
      } else {
        filecopy(fp, stdout);
        fclose(fp);
      }
  	}

    return 0;
  }
}

/* filecopy: copy file inputFile to file outputFile */
void filecopy(FILE *inputFile, FILE *outputFile) {
  int c;

  while ((c = getc(inputFile)) != EOF)
    putc(c, outputFile);
}
