#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// Global vars
float balance = 1000;
float amt;
int ch;

// Main Screen
int HomeScreen(){
    system("cls");
    printf("Hello!\n\nCurrent Balance %.2f\n\n(1) Deposit\n(2) Withdraw\n(3) Exit\n\nEnter your choice:",balance);
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
    
    system("cls");
    printf("Enter amount to withdraw: ");
    scanf("%f", &amt);
    
    balance = balance - amt;
    printf("Withdraw successful.\n\nCash on Hand: %.2f\nCurrent Balance: %.2f\n\n",amt,balance);

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
    
    ch = afterAction();
    return ch;
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
            case 3:
                system("cls");
                printf("THANK YOU FOR USING MIBANK, PLEASE COME AGAIN!");
                getch();
                i--;
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