
CC=gcc
CFLAGS=-I.

endianness: endianness.o
	$(CC) -o $@ $^ $(CFLAGS)

restrict-keyword: restrict-keyword.o
	$(CC) -o $@ $^ $(CFLAGS)

opaque-main: opaque-pointer.o opaque-main.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o endianness restrict-keyword opaque-main
