#ifndef LIBARISTI_H
#define LIBARISTI_H

#include <stdio.h>

#define PASSWORD_KEY 99

// Global utility variables
int intA, intB;
float floatP, floatQ;

float square(float x) {
    return x * x;
}

int add(int c, int d) {
    return (c + d);
}

float multiply(float e, float f) {
    return (e * f);
}

int getMaximum(int g, int h) {
    return (g > h) ? g : h; // Cleaner ternary operator approach
}

float subtract(float i, float j) {
    return (i - j);
}

void verifyPassword() {
    int inputKey;
    do {
        printf("Enter the system password (integer): ");
        scanf("%d", &inputKey);
    } while (inputKey != PASSWORD_KEY);  
    
    printf("Access granted! Welcome.\n");
}

void requestFloatInputs() {
    printf("Enter a decimal value: ");
    scanf("%f", &floatP);
    printf("Enter another decimal value: ");
    scanf("%f", &floatQ);
}

void requestIntegerInputs() {
    printf("Enter an integer value: ");
    scanf("%d", &intA);
    printf("Enter another integer value: ");
    scanf("%d", &intB);
}

#endif