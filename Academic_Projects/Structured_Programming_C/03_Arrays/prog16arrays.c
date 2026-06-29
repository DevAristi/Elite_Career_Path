#include <stdio.h>
#include <stdlib.h>

int main() 
{
    int i, array[7];
    
    for (i = 0; i < 7; i++) 
    {
        printf("Enter the value for element array[%d]: ", i);
        scanf("%d", &array[i]);
    }
    
    printf("\nThe entered array is:\n");
    for (i = 0; i < 7; i++) 
    {
        printf("%d\n", array[i]);
    }
    return 0;
}