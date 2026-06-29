#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CompactDisc
{
    char title[50];
    char artist[30];
    int trackCount;
    float price;
};

int main()
{
    // Fixed compile-time syntax error '5px' to integer literal '5'
    struct CompactDisc collection[5]; 
    int i;
    
    for(i = 0; i < 5; i++)
    {
        printf("\nEnter the Title of Disc %d: ", i + 1);
        // Clear input buffer safely before fetching lines
        if (i > 0) getchar(); 
        
        fgets(collection[i].title, sizeof(collection[i].title), stdin);
        collection[i].title[strcspn(collection[i].title, "\n")] = 0;

        printf("Enter the Artist of Disc %d: ", i + 1);
        fgets(collection[i].artist, sizeof(collection[i].artist), stdin);
        collection[i].artist[strcspn(collection[i].artist, "\n")] = 0;

        printf("Enter the number of tracks for Disc %d: ", i + 1);
        scanf("%d", &collection[i].trackCount);

        printf("Enter the price for Disc %d: ", i + 1);
        scanf("%f", &collection[i].price);
    }

    printf("\n====================================");
    printf("\n      FULL MUSIC COLLECTION");
    printf("\n====================================\n");
    
    for(i = 0; i < 5; i++)
    {
        printf("Disc Number: %d\n", i + 1);
        printf("  Title: %s\n", collection[i].title);
        printf("  Artist: %s\n", collection[i].artist);
        printf("  Tracks: %d\n", collection[i].trackCount);
        printf("  Price: $%.2f\n", collection[i].price);
        printf("------------------------------------\n");
    }

    return 0;
}