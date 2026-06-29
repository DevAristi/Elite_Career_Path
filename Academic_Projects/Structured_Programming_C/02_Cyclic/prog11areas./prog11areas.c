#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int option;
    float base, baseLarge, height, area;
    
    do {
        printf("\n--- GEOMETRIC AREA CALCULATOR ---\n1. Parallelogram\n2. Trapezoid\n3. Exit\n");
        printf("Select an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Enter base (b) and height (h): ");
                scanf("%f %f", &base, &height);
                area = base * height;
                printf("The resulting area is: %.2f\n", area);
                break;

            case 2:
                printf("Enter major base (B), minor base (b) and height (h): ");
                scanf("%f %f %f", &baseLarge, &base, &height);
                area = ((baseLarge + base) * height) / 2.0f;
                printf("The resulting area is: %.2f\n", area);
                break;

            case 3:
                printf("Thank you for using the system.\n");
                break;

            default:
                printf("Invalid selection.\n");
                break;
        }

    } while (option != 3);
    return 0;
}