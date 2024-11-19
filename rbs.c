#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 50
#define MAX_LENGTH 100

typedef struct {
    int id;
    char name[MAX_LENGTH];
    int price;
} MenuItem;

void loadMenu(const char *filename, MenuItem menu[], int *menuSize) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }

    char line[256];
    *menuSize = 0;

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%[^,],%d", &menu[*menuSize].id, menu[*menuSize].name, &menu[*menuSize].price);
        (*menuSize)++;
    }

    fclose(file);
}

void displayMenu(MenuItem menu[], int menuSize) {
    printf("\tChoose your order:\n\n");
    for (int i = 0; i < menuSize; i++) {
        printf("\t%d. %s\t\t%d/-\n", menu[i].id, menu[i].name, menu[i].price);
    }
    printf("\n");
}

int main() {
    MenuItem menu[MAX_ITEMS];
    int menuSize;
    int orderID, quantity;
    char addMore = 'y';
    int totalBill = 0, cgst = 0, sgst = 0;

    int mealChoice;
    const char *menuFile;

    printf("\t\tWelcome to Al-Baik Restaurant\n\n");
    printf("Choose your meal plan:\n");
    printf("1. Breakfast\n2. Lunch\n3. Dinner\n");
    printf("Enter your choice: ");
    scanf("%d", &mealChoice);

    switch (mealChoice) {
        case 1:
            menuFile = "breakfast.txt";
            break;
        case 2:
            menuFile = "lunch.txt";
            break;
        case 3:
            menuFile = "dinner.txt";
            break;
        default:
            printf("Invalid choice. Exiting program.\n");
            return 1;
    }

    
    loadMenu(menuFile, menu, &menuSize);

    int orderQuantities[MAX_ITEMS] = {0};

    while (addMore == 'y' || addMore == 'Y') {
        displayMenu(menu, menuSize);
        printf("Enter the item number you want to order: ");
        scanf("%d", &orderID);

        if (orderID >= 1 && orderID <= menuSize) {
            printf("Enter the quantity: ");
            scanf("%d", &quantity);
            orderQuantities[orderID - 1] += quantity;
        } else {
            printf("Invalid item number. Please try again.\n");
            continue;
        }

        printf("\nDo you want to add more items? (Y/N): ");
        fflush(stdin);
        scanf(" %c", &addMore);
    }

    
    printf("\n\t\tGenerating your BILL...\n");
    printf("\t\t\t\t\tAl-Baik\n");
    printf("\n\tItem\t\tQuantity\tPrice\tTotal\n");
    printf("\t-------------------------------------------------\n");

    for (int i = 0; i < menuSize; i++) {
        if (orderQuantities[i] > 0) {
            int itemTotal = orderQuantities[i] * menu[i].price;
            totalBill += itemTotal;
            printf("\t%s\t\t%d\t\t%d\t%d/-\n", menu[i].name, orderQuantities[i], menu[i].price, itemTotal);
        }
    }

    
    sgst = totalBill * 0.05;
    cgst = sgst;
    totalBill += sgst + cgst;

    printf("\n\t-------------------------------------------------\n");
    printf("\tSubtotal:\t\t\t\t%d/-\n", totalBill - sgst - cgst);
    printf("\tSGST (5%%):\t\t\t\t%d/-\n", sgst);
    printf("\tCGST (5%%):\t\t\t\t%d/-\n", cgst);
    printf("\tTotal Bill:\t\t\t\t%d/-\n", totalBill);

    printf("\n\tThank you for dining with us!\n");
    return 0;
}
