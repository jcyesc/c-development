/*
 This program prints the size in bites of the different
 data types.
 */

#include <stdio.h>

int getIntSize();
int getCharSize();
int getShortIntSize();
int getLongSize();
int getFloatSize();
int getDoubleSize();
int getLongDoubleSize();

int main() {
    
    printf("Int size %d \n", getIntSize());
    printf("Char size %d \n", getCharSize());
    printf("Short Int size %d \n", getShortIntSize());
    printf("Long size %d \n", getLongSize());
    //printf("Double size %d \n", getIntSize());
    //printf("Long Double size %d \n", getIntSize());
    
    return 0;
}

int getIntSize() {
    int type = 1;
    
    int bytes = 0;
    
    while (type != 0) {
        bytes++;
        type = type << 1;
    }
    
    return bytes;
}

int getCharSize() {
    char type = 1;
    
    int bytes = 0;
    
    while (type != 0) {
        bytes++;
        type = type << 1;
    }
    
    return bytes;
}


int getShortIntSize() {
    short int type = 1;
    
    int bytes = 0;
    
    while (type != 0) {
        bytes++;
        type = type << 1;
    }
    
    return bytes;
}


int getLongSize() {
    long type = 1;
    
    int bytes = 0;
    
    while (type != 0) {
        bytes++;
        type = type << 1;
    }
    
    return bytes;
}
/*
int getFloatSize() {
    float type = 1;
    
    int bytes = 0;
    
    while (type != 0) {
        bytes++;
        type = type << 1;
    }
    
    return bytes;
}

int getDoubleSize() {
    double type = 1;
    
    int bytes = 0;
    
    while (type != 0) {
        bytes++;
        type = type << 1;
    }
    
    return bytes;
}

int getLongDoubleSize() {
    long double type = 1;
    
    int bytes = 0;
    
    while (type != 0) {
        bytes++;
        type = type << 1;
    }
    
    return bytes;
}*/