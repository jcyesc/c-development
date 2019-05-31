
#include "hello-print.h"

/**
 *  This example shows how to use custom libraries and
 *  compile them using GCC.
 *
 *  Based on http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
 *
 *  gcc -o hello-make hello-make.c hello-print.c -I.
 *  ./hello-make
 *
 *  The -I. is included so that gcc will look in the current
 *  directory (.) for the include file hello-print.h.
 *
 *  In order to make the test/modify/debug cycle easier, we'll
 *  use make files.
 *
 *  To run the make files execute the following command:
 *
 *   make -f Makefile1
 *
 *  If there is only one makefile per directory and it is named
 *  "Makefile", we can just run:
 *
 *  make
 */
int main() {

	const char *myMessage = "My first message\n";
	hello_print(myMessage);

	return 0;
}


