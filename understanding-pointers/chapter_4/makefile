
CC=gcc
CFLAGS=-I.

intro-arrays: intro-arrays.o
	$(CC) -o $@ $^ $(CFLAGS)
	
realloc-arrays: realloc-arrays.o
	$(CC) -o $@ $^ $(CFLAGS)
	
one-dimensional-array: one-dimensional-array.o
	$(CC) -o $@ $^ $(CFLAGS)

multidimensional-arrays: multidimensional-arrays.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o intro-arrays realloc-arrays one-dimensional-array multidimensional-arrays
