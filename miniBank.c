#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

// Global vars
float balance = 1000;
float amt;
int ch;
char* t_types[3] = {"Deposit", "Check Balance", "Withdrawal"};

// Transaction history database
struct history {
    char *Transact_type; // Deposit, CheckBalance, Withdraw
    float amount; // Amount withdrew/deposited, 0/NULL if CheckBalance
    float initBalance;
    float currentBalance;
    char *dateCreated; // mm/dd/yyyy hh:mm:ss 24 hr format
} logs[99];

// Record history after transaction
void readHistory(int type, float amt, float initbal, float bal){ // Record History after transaction
    
    int i = 0;
    int maxElement = 99;
    time_t t = time(NULL);
    struct tm* timeFull = localtime(&t);

    while (i <= maxElement) {
        if (logs[i].Transact_type != NULL) {
            i++;
        } else {
            break;
        }
    }

    logs[i].Transact_type = t_types[type-1];
    logs[i].amount = amt;
    logs[i].initBalance = initbal;
    logs[i].currentBalance = bal;
    logs[i].dateCreated = asctime(timeFull);
}

// Password Protection
// File Handle

// Main Screen
int HomeScreen(){
    system("cls");
    printf("Hello!\n\nCurrent Balance %.2f\n\n(1) Deposit\n(2) Withdraw\n(3) View History\n(4) Exit\n\nEnter your choice:",balance);
    scanf("%d", &ch);
    return ch;
}

// After action Screen
int afterAction(){
    printf("(1) Exit or (2) Go back to Main Screen? ");
    scanf("%d",&ch);
        if (ch == 1) 
        {
            printf("THANK YOU FOR USING MIBANK, PLEASE COME AGAIN!");
            getch();
            return 1;
        } else if (ch == 2)
        {
            return 2;    
        }
}

int withDraw(){
    float initBal = balance;
    system("cls");
    printf("Enter amount to withdraw: ");
    scanf("%f", &amt);
    balance = balance - amt;
    printf("Withdraw successful.\n\nCash on Hand: %.2f\nCurrent Balance: %.2f\n\n",amt,balance);

    readHistory(3, amt, initBal, balance);

    ch = afterAction();
    return ch;
}

int depoSit(){
    float initBal;
    system("cls");
    printf("Enter amount to deposit: ");
    scanf("%f", &amt);
    
    initBal = balance;
    balance = balance + amt;
    printf("Deposit successful.\n\nInitial Balance: %.2f\nCurrent Balance: %.2f\n\n",initBal,balance);

    readHistory(1, amt, initBal, balance);
    
    ch = afterAction();
    return ch;
}

void viewHistory(){
    int i;
    for (i = 0; i <= 99; i++) {
        if (logs[i].Transact_type != NULL) {
        printf("\nType: %s\nAmount: %.2f\nInitial Balance: %.2f\nCurrent Balance: %.2f\nDate: %s\n",logs[i].Transact_type, logs[i].amount, logs[i].initBalance, logs[i].currentBalance, logs[i].dateCreated);
        } else {
            break;
        }
    }
}

int main(){
    int i = 1;   
    while (i < 6 && i > 0) { // while loop to loop back to HomeScreen every after action
        int i2 = HomeScreen();
        switch (i2) {
            case 1:
                if (depoSit() == 1){
                    i--;
                } 
                break;
            case 2:
               if (withDraw() == 1){
                    i--;
               }
               break;
            case 4:
                system("cls");
                printf("THANK YOU FOR USING MIBANK, PLEASE COME AGAIN!");
                getch();
                i--;
                break;
            case 3:
                system("cls");
                viewHistory();
                if (afterAction() == 1){
                    i--;
                }
                break;
            default:
                system("cls");
                printf("Invalid code.");
                getch();
                system("cls");
                i++;
                break;
        }
        if (i == 5) { // Exits after more than 5 incorrect attempts.
            printf("Too many incorrect attempts. Exiting...");
            getch();
            i++;
        }
    }
    return 0;
}