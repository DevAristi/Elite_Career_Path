#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PARTS 100

struct SparePart {
    int id;
    char description[50];
    char brand[50];
    float price;
    int quantity;
};

void addSparePart(struct SparePart catalog[], int *total);
void removeSparePart(struct SparePart catalog[], int total);
void modifySparePart(struct SparePart catalog[], int total);
void searchSparePart(struct SparePart catalog[], int total);
int findIndexById(struct SparePart catalog[], int total, int idToFind);

int main() {
    struct SparePart catalog[MAX_PARTS];
    int totalRegistered = 0;
    int option;

    do {
        printf("\n-------------------------------------------\n");
        printf("INVENTORY SYSTEM: AUTO PARTS STORE\n");
        printf("-------------------------------------------\n");
        printf("1. Add Spare Part - Register Intake\n");
        printf("2. Remove Spare Part - Register Sale\n");
        printf("3. Modify Spare Part - Update Info\n");
        printf("4. Search Spare Part - Check Stock\n");
        printf("5. Exit System\n");
        printf("-------------------------------------------\n");
        printf("Select the operation you wish to perform: ");
        scanf("%d", &option);

        switch(option) {
            case 1:
                addSparePart(catalog, &totalRegistered);
                break;
            case 2:
                removeSparePart(catalog, totalRegistered);
                break;
            case 3:
                modifySparePart(catalog, totalRegistered);
                break;
            case 4:
                searchSparePart(catalog, totalRegistered);
                break;
            case 5:
                printf("\nExiting system...\n");
                break;
            default:
                printf("\nOption not found. Please try again.\n");
        }
    } while(option != 5);

    return 0;
}

int findIndexById(struct SparePart catalog[], int total, int idToFind) {
    for (int i = 0; i < total; i++) {
        if (catalog[i].id == idToFind) {
            return i;
        }
    }
    return -1;
}

void addSparePart(struct SparePart catalog[], int *total) {
    char response;
    do {
        if (*total >= MAX_PARTS) {
            printf("\n>> Error: Catalog is full. Cannot register more parts.\n");
            return;
        }

        printf("\n--- ADD SPARE PART ---\n");
        printf("Enter Part ID: ");
        scanf("%d", &catalog[*total].id);

        if (findIndexById(catalog, *total, catalog[*total].id) != -1) {
            printf(">> Error: ID already exists in the catalog.\n");
        } else {
            printf("Enter Description: ");
            scanf(" %[^\n]", catalog[*total].description);

            printf("Enter Brand: ");
            scanf(" %[^\n]", catalog[*total].brand);

            printf("Enter Price: $");
            scanf("%f", &catalog[*total].price);

            printf("Enter Quantity to add: ");
            scanf("%d", &catalog[*total].quantity);

            (*total)++;

            printf("\n>> Spare part successfully registered.\n");
        }

        printf("Do you want to register another part? (y/n): ");
        scanf(" %c", &response);

    } while(response == 'y' || response == 'Y');
}

void removeSparePart(struct SparePart catalog[], int total) {
    if (total == 0) {
        printf("\n>> You must register a spare part first.\n");
        return;
    }

    int idToFind, saleQuantity, index;
    char response;
    do {
        printf("\n--- REMOVE SPARE PART (SALE) ---\n");
        printf("Enter the ID of the part to remove: ");
        scanf("%d", &idToFind);

        index = findIndexById(catalog, total, idToFind);

        if (index != -1) {
            printf("Current stock: %d units\n", catalog[index].quantity);
            printf("Enter the quantity of parts sold: ");
            scanf("%d", &saleQuantity);

            if (saleQuantity <= catalog[index].quantity) {
                catalog[index].quantity -= saleQuantity;
                printf("\n>> Sale registered. New stock: %d units\n", catalog[index].quantity);
            } else {
                printf("\n>> Error: Insufficient stock available.\n");
            }
        } else {
            printf("\n>> Error: Spare part not found.\n");
        }

        printf("Do you want to register another sale? (y/n): ");
        scanf(" %c", &response);
    } while(response == 'y' || response == 'Y');
}

void modifySparePart(struct SparePart catalog[], int total) {
    if (total == 0) {
        printf("\n>> You must register a spare part first.\n");
        return;
    }

    int idToFind, subOption, index;

    printf("\n--- MODIFY SPARE PART ---\n");
    printf("Enter the ID of the part to modify: ");
    scanf("%d", &idToFind);

    index = findIndexById(catalog, total, idToFind);

    if (index != -1) {
        printf("\nWhat data do you want to update?\n");
        printf("1. Price\n2. Quantity in Stock\n3. Brand\n");
        printf("Select an option: ");
        scanf("%d", &subOption);

        switch(subOption) {
            case 1:
                printf("Enter the new price: $");
                scanf("%f", &catalog[index].price);
                printf(">> Price updated.\n");
                break;
            case 2:
                printf("Enter the quantity of parts added to stock: ");
                int addedParts;
                scanf("%d", &addedParts);
                catalog[index].quantity += addedParts;
                printf(">> Stock updated. New total: %d\n", catalog[index].quantity);
                break;
            case 3:
                printf("Enter the new brand: ");
                scanf(" %[^\n]", catalog[index].brand);
                printf(">> Brand updated.\n");
                break;
            default:
                printf(">> Invalid option.\n");
        }
    } else {
        printf("\n>> Error: Spare part not found.\n");
    }
}

void searchSparePart(struct SparePart catalog[], int total) {
    if (total == 0) {
        printf("\n>> No spare parts registered.\n");
        return;
    }

    int idToFind, index;
    char response;

    do {
        printf("\n--- SPARE PART SEARCH ---\n");
        printf("Enter Part ID: ");
        scanf("%d", &idToFind);

        index = findIndexById(catalog, total, idToFind);

        if (index != -1) {
            printf("\nRESULT:\n");
            printf("ID: %d\n", catalog[index].id);
            printf("Description: %s\n", catalog[index].description);
            printf("Brand: %s\n", catalog[index].brand);
            printf("Price: $%.2f\n", catalog[index].price);
            printf("Available Stock: %d units\n", catalog[index].quantity);
        } else {
            printf("\n>> Error: Spare part not found.\n");
        }

        printf("\nDo you want to search for another spare part? (y/n): ");
        scanf(" %c", &response);
    } while(response == 'y' || response == 'Y');
}