# Make file for the list example.
#
# The commands to be executed by main are:
#
# gcc -I.   -c -o list_main.o list_main.c
# gcc -o list-main list_main.o -I.
#
CC=gcc
CFLAGS=-I.

list-main: list_main.o
	$(CC) -o $@ $^ $(CFLAGS)
	
clean:
	rm *.o list-main
 
