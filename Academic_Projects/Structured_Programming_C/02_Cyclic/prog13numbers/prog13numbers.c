#include <stdio.h>

int main() {
    float number;
    char response;

    do {
        printf("Enter a number: ");
        scanf("%f", &number);

        if (number > 0) {
            printf("The number is POSITIVE\n");
        } else if (number < 0) {
            printf("The number is NEGATIVO\n");
        } else {
            printf("The number is ZERO\n");
        }

        printf("\nDo you want to run the operation again? (y/n): ");
        scanf(" %c", &response); 

    } while (response == 'y' || response == 'Y');

    printf("Program execution finished.\n");
    return 0;
}