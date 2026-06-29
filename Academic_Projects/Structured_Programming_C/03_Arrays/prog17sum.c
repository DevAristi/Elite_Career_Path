#include <stdio.h>
#include <stdlib.h>

int main() 
{
    float arrayA[5], arrayB[5], arrayC[5];
    int i;
    
    for (i = 0; i < 5; i++) 
    {
        printf("Enter the value for element arrayA[%d]: ", i);
        scanf("%f", &arrayA[i]);
        printf("Enter the value for element arrayB[%d]: ", i);
        scanf("%f", &arrayB[i]);
        
        arrayC[i] = arrayA[i] + arrayB[i];
    }
    
    printf("\nThe resulting arrays are:\n");
    for (i = 0; i < 5; i++) 
    {
        printf("%.1f + %.1f = %.1f\n", arrayA[i], arrayB[i], arrayC[i]);
    }
    return 0;
}