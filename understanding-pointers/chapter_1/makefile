
CC=gcc
CFLAGS=-I.

pointer-related-types: pointer-related-types.o
	$(CC) -o $@ $^ $(CFLAGS)

multiple-levels-indirection: multiple-levels-indirection.o
	$(CC) -o $@ $^ $(CFLAGS)

constants-and-pointers: constants-and-pointers.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o pointer-related-types multiple-levels-indirection constants-and-pointers 