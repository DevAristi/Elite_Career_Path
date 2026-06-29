#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char lastNameP[30], lastNameM[30], firstName[30];
    
    printf("ENTER YOUR FIRST NAME: \n");
    // Safe replacement for gets() to avoid buffer overflows
    fgets(firstName, sizeof(firstName), stdin);
    firstName[strcspn(firstName, "\n")] = 0; // Strips trailing newline character

    printf("ENTER YOUR PATERNA LAST NAME: \n");
    fgets(lastNameP, sizeof(lastNameP), stdin);
    lastNameP[strcspn(lastNameP, "\n")] = 0;

    printf("ENTER YOUR MATERNAL LAST NAME: \n");
    fgets(lastNameM, sizeof(lastNameM), stdin);
    lastNameM[strcspn(lastNameM, "\n")] = 0;

    printf("\nYOU ARE %s %s %s, NICE TO MEET YOU! :)\n", firstName, lastNameP, lastNameM);
    
    printf("\nPress Enter to exit...");
    getchar(); 
    return 0;
}