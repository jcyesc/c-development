
/*
 * In Linux, the file include/linux/err.h defines the following macros
 * to return an error instead of just NULL:
 *
 *     void *ERR_PTR (long error);
 *     long IS_ERR (const void *ptr);
 *     long PTR_ERR (const void *ptr);
 *     long IS_ERR_OR_NULL(const void *ptr)
 *
 * https://elixir.bootlin.com/linux/v5.16.5/source/include/linux/err.h#L24
 *
 * To compile and execute:
 *
 *     $ gcc -o error error.c
 *     $ ./error
 *     MAX NUMBER [18446744073709551615]
 *     The value is [23] >= [18446744073709547521] = [0]
 *     The value is [18446744073709551593] >= [18446744073709547521] = [1]
 */
#include <stdio.h>

#define MAX_NUMBER ~0

#define MAX_ERRNO	4095

#define IS_ERR_VALUE(x) (unsigned long)(void *)(x) >= (unsigned long)-MAX_ERRNO

void print_result(unsigned long error) {
	unsigned long value = (unsigned long)-MAX_ERRNO;
	unsigned long result = IS_ERR_VALUE((void *) error);

	printf("The value is [%lu] >= [%lu] = [%lu] \n", error, value, result);
}

int main() {

	unsigned long error;
	unsigned long max = MAX_NUMBER;

	printf("MAX NUMBER [%lu]\n", max);

	error = 23;
	print_result(error);

	error = -23;
	print_result(error);

	return 0;
}


