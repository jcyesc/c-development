
CC=gcc
CFLAGS=-I.

main: main.o wifi_scan.o
	$(CC) -o $@ $^ $(CFLAGS)

wifi_scan: wifi_scan.o
	$(CC) -o $@ $^ $(CFLAGS)
	
clean:
	rm *.o main
 