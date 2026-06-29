#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i;
    float grade;

    for (i = 1; i <= 3; i++)
    {
        printf("Enter the grade for student %d: ", i);
        scanf("%f", &grade);

        if (grade >= 7.0f && grade <= 10.0f)
        {
            printf("---YOU PASSED!---\n");
        }
        else
        {
            printf("---SEE YOU NEXT TERM! >:( ---\n");
        }
    }
    return 0;
}
