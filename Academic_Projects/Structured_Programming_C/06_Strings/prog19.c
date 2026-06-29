#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Standard C manual implementation for string uppercase conversion
void toUpperCase(char *str) {
    while (*str) {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

// Standard C manual implementation for string reversal
void reverseString(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

int main()
{
    char stringA[50], stringB[50];
    int comparisonResult;
    
    printf("Enter a phrase (max 50 characters):\n");
    fgets(stringA, sizeof(stringA), stdin);
    stringA[strcspn(stringA, "\n")] = 0; // Strip newline
    
    printf("The phrase entered is:\n%s\n", stringA);
    
    toUpperCase(stringA);
    printf("The phrase in UPPERCASE becomes:\n%s\n", stringA);
    
    strcpy(stringB, stringA);
    printf("String A content: \n%s\nString B content: \n%s\n", stringA, stringB);
    
    comparisonResult = strcmp(stringA, stringB);
    if(comparisonResult == 0) {
        printf("THE STRINGS ARE EQUAL :)\n");
    } else {
        printf("THE STRINGS ARE DIFFERENT :(\n");
    }
    
    reverseString(stringB);
    printf("\nString A remains: %s\nString B inverted becomes: \n%s\n", stringA, stringB);
    
    comparisonResult = strcmp(stringA, stringB);
    if (comparisonResult == 0) {
        printf("THE STRINGS ARE EQUAL :)\n");
    } else {
        printf("THE STRINGS ARE DIFFERENT :(\n");
    }
    
    printf("\nPress Enter to close program...");
    getchar(); 
    return 0;
}