#include <stdio.h>

/*
 This program shows that if we are not careful with the array indexes and pointers we might override illegally the memory.
 */
int main() {
  
  
  
  char a[10];
  char *p = "This is the end my little friend";

  // accessing the memory illegally.
  int i;
  for(i = 0; i < 100; i++)
     printf("%d, ", a[i]);
    
  strcat(a, p);

    
  printf("Second: %s\n", p);
  printf("First: %s\n", a);

  
    
  
  return 0;
}

/* strcat: concatenate t to end of s; must be big enough. */
void strcat(char s[], char t[]) {
  int i, j;

  i = j = 0;
  while (s[i] != '\0') // fin end of s
    i++;
    while((s[i++] = t[j++]) != '\0') { // copy t
        printf("%d, \n", i);
        
        if (i == 11) {
           
            printf("breaking\n");
            ////s[i] = '\0';
            break;
            
        }
    }
}
