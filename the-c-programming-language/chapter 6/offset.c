#include <stdio.h>
#include <stdlib.h>

/*
   Offset

   We are getting the offset of the members of the struct.
*/

//#define offsetof(TYPE, MEMBER) (size_t) & (((TYPE *) 0)->MEMBER)
#define offsetof(TYPE, MEMBER) (unsigned) & (((TYPE *) 0)->MEMBER)
/*
	This is equal to:

		struct *p = (struct *) 0;
*/



struct point {
  int x;
  int y;
  int z;
  char c;
  float o;
};

int main() {
  printf("Offset of y = %d\n", offsetof(struct point, y));
  printf("Offset of z = %d\n", offsetof(struct point, z));
  printf("Offset of o = %d\n", offsetof(struct point, o));

  // This is saying, suppose that there is something in address zero and
  // use arithmetic of pointers to get the address of the elements.
  struct point *pr = (struct point *) 0;
  int offs = (int) & (pr->z);

  printf("Offset of z = %d\n", offs);


}