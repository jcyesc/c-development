
CC=gcc
CFLAGS=-I.

intro-arrays: intro-arrays.o
	$(CC) -o $@ $^ $(CFLAGS)
	
realloc-arrays: realloc-arrays.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o intro-arrays realloc-arrays
