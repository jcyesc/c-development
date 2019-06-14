#include <stdio.h>
#include <stdlib.h>

/**
	This program shows how to declare and use structs.
*/

struct fraction {
	int numerator;
	int denominator;
};

/*
	It returns a pointer to a new fraction. The caller is responsible
	for deleting this fraction with free when it's no longer required.
*/
struct fraction * createFraction() {
	return (struct fraction *) malloc(sizeof(struct fraction));
}

/* This method receives two fractions and add them. It returns
   a pointer to the new fraction. The caller is responsible for
   deleting this fraction with free when it's no longer required.

   a/b + c/d = (ad + bc)/bd
*/
struct fraction * add(struct fraction *f1, struct fraction *f2) {
	struct fraction *result = createFraction();
	result->numerator = (f1->numerator * f2->denominator + f1->denominator * f2->numerator);
	result->denominator = f1->denominator * f2->denominator;

	return result;
}

/* This method receives two fractions and multiply them. It returns
   a pointer to the new fraction. The caller is responsible for
   deleting this fraction with free when it's no longer required.

   a/b * c/d = ac/bd	
*/
struct fraction * multiply(struct fraction *f1, struct fraction *f2) {
	struct fraction *result = createFraction();
	(*result).numerator = (*f1).numerator * (*f2).numerator;
	(*result).denominator = (*f1).denominator * (*f2).denominator;

	return result;
}

void print(struct fraction *f) {
	printf("(%d / %d)", f->numerator, f->denominator);
}

int main() {
	struct fraction f1, f2;
	f1.numerator = 3;
	f1.denominator = 4;

	f2.numerator = 1;
	f2.denominator = 2;

	struct fraction *result;

	result = add(&f1, &f2);
	print(&f1);
	printf(" + ");
	print(&f2);
	printf(" = ");
	print(result);
	printf("\n");

	free(result);
}

