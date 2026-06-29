#include <stdio.h>
#include <stdlib.h>

int main() {
    int shirtCount;
    float subtotal, tax, totalPrice;
    char response;

    do {
        printf("\n--- Shirt Store Management ---\n");
        printf("Enter the number of shirts purchased by the customer: ");
        scanf("%d", &shirtCount);

        if (shirtCount < 5) {
            subtotal = shirtCount * 250;
        } 
        else if (shirtCount >= 5 && shirtCount <= 10) {
            subtotal = shirtCount * 220;
        } 
        else {
            subtotal = shirtCount * 180;
        }

        tax = subtotal * 0.16f; // 16% standard VAT
        totalPrice = subtotal + tax;

        printf("\nSubtotal: $%.2f", subtotal);
        printf("\nVAT (16%%): $%.2f", tax);
        printf("\nTotal due: $%.2f", totalPrice);

        printf("\n\nDo you want to calculate for another customer? (y/n): ");
        scanf(" %c", &response);

    } while (response == 'y' || response == 'Y');

    printf("\nProgram terminated successfully.\n");
    return 0;
}