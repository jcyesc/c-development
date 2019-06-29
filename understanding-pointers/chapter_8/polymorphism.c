#include <stdio.h>
#include <stdlib.h>

/**
 * Polymorphism and Virtual Functions
 *
 * This example shows how to implement polymorphism in C using
 * virtual functions.
 *
 * To execute the program run:
 *
 * make polymorphism
 * ./polymorphism
 *
 */

typedef void (*fptrSet)(void *, int);
typedef int (*fptrGet)(void *);
typedef void (*fptrDisplay)(void *);

typedef struct {
	// Functions
	fptrSet setX;
	fptrGet getX;
	fptrSet setY;
	fptrGet getY;
	fptrDisplay display;
} VirtualFunctions;

typedef struct {
	VirtualFunctions functions;
	// Base variables
	int x;
	int y;
} Shape;

void shapeDisplay(Shape* shape) {
	printf("Shape x = %d, y = %d\n", shape->x, shape->y);
}
void shapeSetX(Shape* shape, int x) {
	shape->x = x;
}
void shapeSetY(Shape *shape, int y) {
	shape->y = y;
}
int shapeGetX(Shape *shape) {
	return shape->x;
}
int shapeGetY(Shape *shape) {
	return shape->y;
}

Shape* getShapeInstance() {
	Shape* shape = (Shape *) malloc(sizeof(Shape));
	shape->functions.display = (void (*)(void *)) shapeDisplay;
	shape->functions.setX = (void (*)(void *, int)) shapeSetX;
	shape->functions.getX = (int (*)(void *)) shapeGetX;
	shape->functions.setY = (void (*)(void *, int)) shapeSetY;
	shape->functions.getY = (int (*)(void *)) shapeGetY;
	shape->x = 100;
	shape->y = 50;

	return shape;
}

typedef struct {
	Shape base;
	int width;
	int height;
} Rectangle;

void rectangleSetX(Rectangle *rectangle, int x) {
	rectangle->base.x = x;
}

void rectangleSetY(Rectangle *rectangle, int y) {
	rectangle->base.y = y;
}

int rectangleGetX(Rectangle *rectangle) {
	return rectangle->base.x;
}

int rectangleGetY(Rectangle *rectangle) {
	return rectangle->base.y;
}

void rectangleDisplay(Rectangle *rectangle) {
	printf("Rectangle x = %d, y = %d, height = %d, width = %d\n",
			rectangle->base.x, rectangle->base.y, rectangle->height,
			rectangle->width);
}

Rectangle* getRectangleInstance() {
	Rectangle *rectangle = (Rectangle*) malloc(sizeof(Rectangle));
	rectangle->base.functions.display = (void (*)(void *)) rectangleDisplay;
	rectangle->base.functions.setX = (void (*)(void *, int)) rectangleSetX;
	rectangle->base.functions.getX = (int (*)(void *)) rectangleGetX;
	rectangle->base.functions.setY = (void (*)(void *, int)) rectangleSetY;
	rectangle->base.functions.getY = (int (*)(void *)) rectangleGetY;
	rectangle->base.x = 250;
	rectangle->base.y = 45;
	rectangle->height = 340;
	rectangle->width = 236;

	return rectangle;
}

int main() {
	Shape *sptr = getShapeInstance();
	sptr->functions.setX(sptr, 35);
	sptr->functions.display(sptr);
	printf("%d\n", sptr->functions.getY(sptr));

	Rectangle *rptr = getRectangleInstance();
	rptr->base.functions.setX(rptr, 695);
	rptr->base.functions.setY(rptr, 123);
	rptr->base.functions.display(rptr);

	// Iterating an array Polymorphically
	int size = 3;
	Shape *shapes[size];
	shapes[0] = sptr;
	shapes[1] = (Shape *) rptr;
	shapes[2] = (Shape *) getRectangleInstance();
	shapes[2]->functions.setX(shapes[2], 1111);
	shapes[2]->functions.setY(shapes[2], 2222);

	printf("\nIterating Polymorphically\n");
	for (int i = 0; i < 3; i++) {
		shapes[i]->functions.display(shapes[i]);
	}

	for (int i = 0; i < 3; i++) {
		free(shapes[i]);
	}

	return 0;
}

