#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>
#include <string.h>

#define SUCCESS 13
#define EXIT 14
#define FORCE_EXIT 69


float balance = 1000;
struct TransactionData {
    char TransactionType[14]; // Deposit, Withdrawal, Check Balance
    float Amount; // Amount transacted
    float InitialBalance; // Inital balance before transaction
    float FinalBalance; // Balance after transaction
    char TransactionDate[500]; // Date of Transcation
};

int PostTransaction(int TransactionType, float amount, float InitialBalance, float CurrentBalance){ // Post transaction duties: append to file, post transaction screen
    
    int x;

    // Open File
    FILE* infile;
    infile = fopen("TransactionData.bin","ab");
    if (infile == NULL) {
        perror("Error opening file");
        return FORCE_EXIT; // Error, exit immediately
    } 

    // Initialize time
    time_t CurrentTime = time(NULL);
    struct tm* TransactionTime = localtime(&CurrentTime);
    char* TimeString;
    TimeString = asctime(TransactionTime);

    struct TransactionData TransactionDataIn;
    char* TransactTypes[3] = {"Withdrawal","Deposit","Check Balance"};
    

    memcpy(&TransactionDataIn.TransactionDate, TimeString, sizeof(TransactionDataIn.TransactionDate));
    memcpy(&TransactionDataIn.TransactionType, TransactTypes[TransactionType], sizeof(&TransactionDataIn.TransactionType));
    TransactionDataIn.Amount = amount;
    TransactionDataIn.InitialBalance = InitialBalance;
    TransactionDataIn.FinalBalance = CurrentBalance;

    // Writes data to data file
    fwrite(&TransactionDataIn, sizeof(struct TransactionData), 1, infile);
    fclose(infile);

    printf("\n\nTransaction recorded.\n");

    // Clear Terminal and show Post-transaction Screen
    printf("(1) Exit or (2) Go to Home Screen? ");
    scanf("%d", &x);
    if (x == 1) {
        return EXIT;
    } else if (x == 2) {
        return SUCCESS;
    } else {
        printf("\nInvalid number. Going back to Home Screen...");
        sleep(3);
        return EXIT;
    }
}

int Deposit(){ // Deposit transaction
    float amount, initialBalance;
    system("cls");
    printf("Enter amount to deposit: ");
    scanf("%f",&amount);

    if (amount <= 0){
        printf("Please enter a valid amount.");
        return EXIT;
    } 

    initialBalance = balance;
    balance = balance + amount;

    printf("\n\n---------------------------------------------------\n");
    printf("Receipt\n\nAmount: %.2f\nInitial Balance: %.2f\nCurrent Balance: %.2f",amount,initialBalance,balance);    
    printf("\n---------------------------------------------------");

    if (PostTransaction(1, amount, initialBalance, balance) == SUCCESS) {
        return SUCCESS;
    } else {
        return EXIT;
    }

}

int Withdraw(){ // Withdraw transaction
    float amount, initialBalance;
    initialBalance = balance;
    system("cls");
    printf("Available Balance: %.2f\nEnter amount to withdraw: ", initialBalance);
    scanf("%f",&amount);
    
    if (amount <= 0){
        printf("Please enter a valid amount.");
        return EXIT;
    } 
    
    if (amount > balance) {
        printf("Invalid amount. Exiting...");
        sleep(3);
        return EXIT;
    } else {
    balance = balance - amount;
    }

    printf("\n\n---------------------------------------------------\n");
    printf("Receipt\n\nAmount: %.2f\nInitial Balance: %.2f\nCurrent Balance: %.2f",amount,initialBalance,balance);    
    printf("\n---------------------------------------------------");

    if (PostTransaction(0, amount, initialBalance, balance) == SUCCESS) {
        return SUCCESS;
    } else {
        return EXIT;
    }
}

int ViewHistory(){ // View history
    system("cls");
    // Open file for reading
    int x;
    struct TransactionData TransactionData;
    FILE* infile = fopen("TransactionData.bin", "rb");
    if (infile == NULL) {
        perror("Error opening file");
        return EXIT;
    }

    // Read structs using fseek and fread until EOF
    int num_read = 0;
    while (fread(&TransactionData, sizeof(struct TransactionData), 1, infile) == 1) {
        printf("\nTransaction: %s\nAmount: %.2f\nInitial Balance: %.2f\nCurrent Balance: %.2f\nTransaction Date: %s\n",TransactionData.TransactionType,TransactionData.Amount,TransactionData.InitialBalance,TransactionData.FinalBalance,TransactionData.TransactionDate);
        num_read++;
    }

    printf("Read %d entries from the file.\n", num_read);
    printf("(1) Exit or (2) Go to Home Screen? ");
    scanf("%d", &x);
    if (x == 1) {
        return EXIT;
    } else if (x == 2) {
        return SUCCESS;
    } else {
        printf("\nInvalid number. Going back to Home Screen...");
        sleep(3);
        return EXIT;
    }
    fclose(infile);
    
    return SUCCESS;
}

int HomeScreen(){
    int x;
    system("cls");
    printf("Hello\n\nCurrent Balance %.2f\n", balance);
    printf("(1) Deposit\n(2) Withdraw\n(3) View History\n(4) Exit");
    printf("\n\nEnter your choice: ");
    scanf("%d",&x);
    return x;
}

int main(){
    
    // Initial Setup, read current balance, if no history, default to 1000
    FILE* infile = fopen("TransactionData.bin","ab+");
    struct TransactionData data;
    // seek to last record
    while (fread(&data, sizeof(struct TransactionData), 1, infile) == 1) {
    }
    balance = data.FinalBalance;
    fclose(infile);

    int i;
    do {
        switch (HomeScreen()) {
            case 1:
                if(Deposit() == SUCCESS){
                    break;
                } else {
                    i--;
                    break;
                }
            case 2:
                if(Withdraw() == SUCCESS){
                        break;
                    } else {
                        i--;
                        break;
                    }
            case 3:
                if(ViewHistory() == SUCCESS){
                    break;
                } else {
                    i--;
                    break;
                }
            case 4:
                system("cls");
                printf("Thanks for using miniBank!!!");
                sleep(3);
                return 0;
            default:
                printf("Invalid code. Try again.");
                sleep(3);
                system("cls");
                i++;
                break;
        }
        if (i == 4) {
            printf("Too many incorrect attempts. Exiting...");
            sleep(3);
            i++;
        }
    } while (i >= 0 && i <= 5);
    return 0;
}