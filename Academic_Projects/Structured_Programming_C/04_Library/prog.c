#include <stdio.h>
#include <stdlib.h>
#include "libaristi.h"

void waitForUser() {
    printf("\nPress Enter to continue...");
    getchar(); // Catch residual newline
    getchar(); // Wait for actual keystroke
}

int main() {
    int option;
    verifyPassword();
    
    do
    {
        #ifdef _WIN32
            system("CLS");
        #else
            system("clear");
        #endif

        printf("--- SYSTEM MENU ---\n");
        printf("1.- ADD TWO INTEGERS\n");
        printf("2.- SUBTRACT TWO DECIMALS\n");
        printf("3.- MULTIPLY TWO DECIMALS\n");
        printf("4.- SHOW THE GREATER OF TWO INTEGERS\n");
        printf("5.- EXIT\n");
        printf("Select an option: ");
        scanf("%d", &option);
        
        switch(option)
        {
            case 1:
                requestIntegerInputs();
                printf("Result of addition: %d\n", add(intA, intB));
                waitForUser();
                break;
                   
            case 2:
                requestFloatInputs();
                printf("Result of subtraction: %f\n", subtract(floatP, floatQ));
                waitForUser();
                break;
                   
            case 3:
                requestFloatInputs();
                printf("Result of multiplication: %f\n", multiply(floatP, floatQ));
                waitForUser();
                break;
                   
            case 4:
                requestIntegerInputs();
                printf("The maximum number is: %d\n", getMaximum(intA, intB));
                waitForUser();
                break;
                   
            case 5:
                printf("Exiting system...\n");
                break;
                   
            default:
                printf("Invalid selection.\n");
                waitForUser();
                break;
        }
        
    } while(option != 5);
    
    return 0;
}