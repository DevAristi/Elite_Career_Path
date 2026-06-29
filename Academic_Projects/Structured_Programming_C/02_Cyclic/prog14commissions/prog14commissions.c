#include <stdio.h>
#include <stdlib.h>

int main()
{
    float salesAmount, commission;
    char response;

    do
    {
        printf("Enter the sales amount: ");
        scanf("%f", &salesAmount);

        // Tiered commission structure refactored for correct logical evaluation
        if (salesAmount > 1000 && salesAmount <= 5000)
        {
            commission = salesAmount * 0.10f;
        }
        else if (salesAmount >= 1000)
        {
            commission = salesAmount * 0.05f;
        }
        else if (salesAmount >= 500 && salesAmount <= 1000)
        {
            commission = salesAmount * 0.07f;
        }
        else
        {
            commission = salesAmount * 0.12f;
        }

        printf("The commission is: $%.2f\n", commission);
        printf("Do you want to calculate another commission? (y/n): ");
        scanf(" %c", &response);

    } while (response == 'y' || response == 'Y');

    return 0;
}