
#include <stdio.h>

/**
 * Endianness of a Machine
 *
 * Endian refers to the order of bytes in memory. There are two types
 * of endianness: little endian and big endian. Little endian is when the least
 * signicant byte of a data type is stored in the lowest address.
 *
 * For example, the number 0x12345678 will be stored in the following address in
 * a little endian machine:
 *
 * Address        | value
 * -----------------------
 * 0x7ffee13d2a38 |  78
 * 0x7ffee13d2a39 |  56
 * 0x7ffee13d2a3a |  34
 * 0x7ffee13d2a3b |  12
 *
 * In order to execute the program run:
 *
 * make endianness
 * ./endianness
 *
 */

int main() {
	int num = 0x12345678;
	char *ptr = (char *) &num;
	for (int i = 0; i < sizeof(int); i++) {
		printf("%p: %02x \n", ptr, *ptr++);
	}

	return 0;
}
