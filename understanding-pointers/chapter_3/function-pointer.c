#include <stdio.h>
#include <stdlib.h>

/**
 * Function pointer
 */
int square(int num) {
	return num * num;
}

int add(int num1, int num2) {
	return num1 + num2;
}

int subtract(int num1, int num2) {
	return num1 - num2;
}

void using_function_pointer() {
	printf("using_function_pointer() \n");
	int (*fptr1)(int);

	int n = 5;
	fptr1 = square; // fptr1 = &square; it is the same.

	printf("%d squared is %d\n", n, fptr1(n));
}

typedef int (*fptrOperation)(int, int);

/** Uses the typedef fptrOperation for the function pointer. */
int compute1(fptrOperation operation, int num1, int num2) {
	return operation(num1, num2);
}

/** Don't use the typedef fptrOperation for the function pointer. */
int compute2(int (*fptr)(int, int), int num1, int num2) {
	return fptr(num1, num2);
}

void passing_function_pointers() {
	printf("passing_function_pointers()\n");

	int result = compute1(add, 5, 6);
	printf("compute1() = %d\n", result);
	result = compute2(subtract, 5, 6);
	printf("compute2() = %d\n", result);
}

fptrOperation select(char opcode) {
	switch (opcode) {
	case '+':
		return add;
	case '-':
		return subtract;
	default:
		return add;
	}
}

int evaluate(char opcode, int num1, int num2) {
	fptrOperation operation = select(opcode);
	return operation(num1, num2);
}

void returning_function_pointers() {
	printf("returning_function_pointers()\n");

	int result = evaluate('+', 5, 6);
	printf("evaluate() = %d\n", result);
	result = evaluate('-', 5, 6);
	printf("evaluate1() = %d\n", result);
}

void using_array_function_pointers() {
	printf("using_array_function_pointers()\n");

	fptrOperation operations1[128] = { NULL };
	operations1['+'] = add;
	operations1['-'] = subtract;
	printf("%d\n", operations1['+'](45, 60));

	// Another way of declaring arrays without using a typedef.
	int (*operations2[128])(int, int) = {NULL };
	operations2['+'] = add;
	operations2['-'] = subtract;
	printf("%d\n", operations2['+'](45, 60));


	int (*(*ptr_to_array_of_ptr_to_func_returning_int)[])(int, int);
	ptr_to_array_of_ptr_to_func_returning_int = &operations2;
	printf("Same address %p, +1 = %p \n", operations2, (operations2 + 1));
	printf("Same address %p, +1 = %p \n", ptr_to_array_of_ptr_to_func_returning_int, (*ptr_to_array_of_ptr_to_func_returning_int + 1));
	printf("Same address %p, +1 = %p \n", *ptr_to_array_of_ptr_to_func_returning_int, (*ptr_to_array_of_ptr_to_func_returning_int + 1));
	printf("%d\n", (*ptr_to_array_of_ptr_to_func_returning_int)['+'](1237, 5));

	// The line below generates the following error:
	// error: arithmetic on a pointer to an incomplete type 'int (*[])(int, int)'
	// printf("Same address %p, +1 = %p \n", ptr_to_array_of_ptr_to_func_returning_int, (ptr_to_array_of_ptr_to_func_returning_int + 1));
	// This error is fixed by assigning size to the pointer to array of pointers.
	// int (*(*ptr_to_array_of_ptr_to_func_returning_int)[5])(int, int);
}

int main() {
	using_function_pointer();

	passing_function_pointers();

	returning_function_pointers();

	using_array_function_pointers();

	return 0;
}


