#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "accounts.dat"

typedef struct {
    int accountNumber;
    char name[50];
    float balance;
} Account;

void createAccount();
void depositMoney();
void withdrawMoney();
void checkBalance();
void viewAllAccounts();

int main() {
    int choice;
    while (1) {
        printf("\nBank Account Management System\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. View All Accounts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5: viewAllAccounts(); break;
            case 6: exit(0);
            default: printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

void createAccount() {
    FILE *file = fopen(FILENAME, "ab");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    Account acc;
    printf("Enter Account Number: ");
    scanf("%d", &acc.accountNumber);
    printf("Enter Name: ");
    scanf("%s", acc.name);
    acc.balance = 0.0;
    
    fwrite(&acc, sizeof(Account), 1, file);
    fclose(file);
    printf("Account created successfully!\n");
}

void depositMoney() {
    FILE *file = fopen(FILENAME, "r+b");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    int accNo;
    float amount;
    printf("Enter Account Number: ");
    scanf("%d", &accNo);
    
    Account acc;
    while (fread(&acc, sizeof(Account), 1, file)) {
        if (acc.accountNumber == accNo) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            acc.balance += amount;
            fseek(file, -sizeof(Account), SEEK_CUR);
            fwrite(&acc, sizeof(Account), 1, file);
            fclose(file);
            printf("Amount deposited successfully!\n");
            return;
        }
    }
    printf("Account not found!\n");
    fclose(file);
}

void withdrawMoney() {
    FILE *file = fopen(FILENAME, "r+b");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    int accNo;
    float amount;
    printf("Enter Account Number: ");
    scanf("%d", &accNo);
    
    Account acc;
    while (fread(&acc, sizeof(Account), 1, file)) {
        if (acc.accountNumber == accNo) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            if (amount > acc.balance) {
                printf("Insufficient balance!\n");
            } else {
                acc.balance -= amount;
                fseek(file, -sizeof(Account), SEEK_CUR);
                fwrite(&acc, sizeof(Account), 1, file);
                printf("Amount withdrawn successfully!\n");
            }
            fclose(file);
            return;
        }
    }
    printf("Account not found!\n");
    fclose(file);
}

void checkBalance() {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    int accNo;
    printf("Enter Account Number: ");
    scanf("%d", &accNo);
    
    Account acc;
    while (fread(&acc, sizeof(Account), 1, file)) {
        if (acc.accountNumber == accNo) {
            printf("Account Number: %d\nName: %s\nBalance: %.2f\n", acc.accountNumber, acc.name, acc.balance);
            fclose(file);
            return;
        }
    }
    printf("Account not found!\n");
    fclose(file);
}

void viewAllAccounts() {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    
    Account acc;
    printf("\nAccount List:\n");
    printf("---------------------------\n");
    while (fread(&acc, sizeof(Account), 1, file)) {
        printf("Account Number: %d\nName: %s\nBalance: %.2f\n", acc.accountNumber, acc.name, acc.balance);
        printf("---------------------------\n");
    }
    fclose(file);
}
