
CC=gcc
CFLAGS=-I.

pointer-to-pointer: pointer-to-pointer.o
	$(CC) -o $@ $^ $(CFLAGS)

function-pointer: function-pointer.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o pointer-to-pointer function-pointer
 