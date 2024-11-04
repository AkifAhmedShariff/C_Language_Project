#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct items {
    char item[30];
    float price;
    int qty;
};

struct orders {
    char customer[50];
    char date[50];
    struct items itm[10];
};

struct items menu[10] = {
    {"Chicken Burger", 150.0, 0},
    {"Grilled Chicken", 300.0, 0},
    {"Shawarma", 120.0, 0},
    {"French Fries", 80.0, 0},
    {"Coke", 50.0, 0},
    {"Pizza", 200.0, 0},
    {"Pasta", 180.0, 0},
    {"Salad", 70.0, 0},
    {"Ice Cream", 60.0, 0},
    {"Juice", 40.0, 0}
};

void generateBillHeader(char name[50], char date[30]) {
    printf("\n\n");
    printf("\t    ADV. Restaurant");
    printf("\n\t   -----------------");
    printf("\nDate: %s", date);
    printf("\nInvoice To: %s", name);
    printf("\n");
    printf("---------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n---------------------------------------");
    printf("\n\n");
}

void generateBillBody(char item[30], int qty, float price) {
    printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f\t\t", qty * price);
    printf("\n");
}

void generateBillFooter(float total) {
    printf("\n");
    float dis = 0.1 * total;
    float netTotal = total - dis;
    float cgst = 0.09 * netTotal, grandTotal = netTotal + 2 * cgst;
    printf("---------------------------------------\n");
    printf("Sub Total\t\t\t%.2f", total);
    printf("\nDiscount @10%%\t\t\t%.2f", dis);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f", netTotal);
    printf("\nCGST @9%%\t\t\t%.2f", cgst);
    printf("\nSGST @9%%\t\t\t%.2f", cgst);
    printf("\n---------------------------------------");
    printf("\nGrand Total\t\t\t%.2f", grandTotal);
    printf("\n---------------------------------------\n");
}

int main() {
    int opt, itemNumber, qty;
    struct orders ord;
    char saveBill = 'y', contFlag = 'y';
    FILE *fp;

    while (contFlag == 'y') {
        system("clear");
        float total = 0;
        int invoiceFound = 0;

        printf("\t============AHMED RESTAURANT============");
        printf("\n\nPlease select your preferred operation:");
        printf("\n1. Generate Invoice");
        printf("\n2. Show all Invoices");
        printf("\n3. Search Invoice");
        printf("\n4. Exit");
        printf("\n\nYour choice:\t");
        scanf("%d", &opt);
        fgetc(stdin);

        switch (opt) {
            case 1:
                system("clear");
                printf("\nPlease enter the name of the customer:\t");
                fgets(ord.customer, 50, stdin);
                ord.customer[strlen(ord.customer) - 1] = 0;
                strcpy(ord.date, __DATE__);

                printf("\nAvailable Menu:\n");
                for (int i = 0; i < 10; i++) {
                    printf("%d. %s - %.2f\n", i + 1, menu[i].item, menu[i].price);
                }

                for (int i = 0; i < 10; i++) {
                    ord.itm[i].qty = 0;  
                }
                while (1) {
                    printf("\nEnter item number (0 to finish): ");
                    scanf("%d", &itemNumber);

                    if (itemNumber == 0) {
                        break;
                    } else if (itemNumber < 1 || itemNumber > 10) {
                        printf("Invalid item number. Please try again.\n");
                        continue;
                    }

                    printf("Enter quantity for %s: ", menu[itemNumber - 1].item);
                    scanf("%d", &qty);

                    ord.itm[itemNumber - 1].qty += qty;
                    ord.itm[itemNumber - 1].price = menu[itemNumber - 1].price;
                    strcpy(ord.itm[itemNumber - 1].item, menu[itemNumber - 1].item);

                    total += qty * menu[itemNumber - 1].price;
                }

                generateBillHeader(ord.customer, ord.date);
                for (int i = 0; i < 10; i++) {
                    if (ord.itm[i].qty > 0) {
                        generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
                    }
                }
                generateBillFooter(total);

                printf("\nDo you want to save the invoice [y/n]:\t");
                scanf(" %c", &saveBill);

                if (saveBill == 'y') {
                    fp = fopen("RestaurantBill.dat", "a+");
                    fwrite(&ord, sizeof(struct orders), 1, fp);
                    if (fwrite != 0)
                        printf("\nSuccessfully saved");
                    else
                        printf("\nError saving");
                    fclose(fp);
                }
                break;

            case 2:
                system("clear");
                fp = fopen("RestaurantBill.dat", "r");
                printf("\n  *****Your Previous Invoices*****\n");
                while (fread(&ord, sizeof(struct orders), 1, fp)) {
                    float tot = 0;
                    generateBillHeader(ord.customer, ord.date);
                    for (int i = 0; i < 10; i++) {
                        if (ord.itm[i].qty > 0) {
                            generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
                            tot += ord.itm[i].qty * ord.itm[i].price;
                        }
                    }
                    generateBillFooter(tot);
                }
                fclose(fp);
                break;

            case 3:
                printf("Enter the name of the customer:\t");
                fgets(ord.customer, 50, stdin);
                ord.customer[strlen(ord.customer) - 1] = 0;
                system("clear");
                fp = fopen("RestaurantBill.dat", "r");
                printf("\t*****Invoice of %s*****", ord.customer);
                while (fread(&ord, sizeof(struct orders), 1, fp)) {
                    float tot = 0;
                    if (!strcmp(ord.customer, ord.customer)) {
                        generateBillHeader(ord.customer, ord.date);
                        for (int i = 0; i < 10; i++) {
                            if (ord.itm[i].qty > 0) {
                                generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
                                tot += ord.itm[i].qty * ord.itm[i].price;
                            }
                        }
                        generateBillFooter(tot);
                        invoiceFound = 1;
                    }
                }
                if (!invoiceFound) {
                    printf("Sorry, the invoice for %s does not exist.", ord.customer);
                }
                fclose(fp);
                break;

            case 4:
                printf("\n\t\t Bye Bye :)\n\n");
                exit(0);
                break;

            default:
                printf("Sorry, invalid option");
                break;
        }

        printf("\nDo you want to perform another operation? [y/n]:\t");
        scanf(" %c", &contFlag);
    }

    printf("\n\t\t Bye Bye :)\n\n");
    return 0;
}
