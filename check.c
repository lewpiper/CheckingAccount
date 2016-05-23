//Checking Account Lab
//Lew Piper III | Palomar ID 011263249

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void outputHeaders(void);
void initialBalance(double amount, double* balance, double* service, double* openBalance);
void deposit(double amount, double* balance, double* service, int* numDeposit, double* amtDeposit);
void check(double amount, double* balance, double* service, int* numCheck, double* amtCheck);
void outputSummary(int numDeposit, double amtDeposit, int numCheck, double amtCheck, double openBalance, double service, double closeBalance);

FILE *fpIn;
FILE *fpOut;

//Provided main function from the Stegman Textbook for this course from page 232
int main (void) {
    char code;
    double amount, service, balance;
    double amtCheck, amtDeposit, openBalance, closeBalance;
    int numCheck, numDeposit;
    
    if (!(fpIn = fopen("account.txt", "r"))) {
        printf("account.txt could not be opened for input.");
        exit(1);
    }
    if (!(fpOut = fopen("csis.txt", "w"))) {
        printf("csis.text could not be opened for output");
        exit(1);
    }
    
    amount        = 0.0;
    service       = 0.0;
    balance       = 0.0;
    amtCheck      = 0.0;
    amtDeposit    = 0.0;
    openBalance   = 0.0;
    closeBalance  = 0.0;
    numCheck      = 0;
    numDeposit    = 0;
    
    outputHeaders();
    
    while (!feof(fpIn)) {
        fscanf(fpIn, "%c %lf\n", &code, &amount);
        if (code == 'I') {
            initialBalance(amount, &balance, &service, &openBalance);
        } else if (code == 'D') {
            deposit(amount, &balance, &service, &numDeposit, &amtDeposit);
        } else {
            check(amount, &balance, &service, &numCheck, &amtCheck);
        }
    }
    
    
    closeBalance = balance - service;
    outputSummary(numDeposit, amtDeposit, numCheck, amtCheck, openBalance, service, closeBalance);
    fclose(fpIn);
    fclose(fpOut);
    return 0;
}

void outputHeaders(void) {
    int i;
    
    //Prints the headers for each of the columns in the output files
    printf("%s%16s%12s%14s\n", "Transaction", "Deposit", "Check", "Balance");
    fprintf(fpOut,"%s%16s%12s%14s\n", "Transaction", "Deposit", "Check", "Balance");
    
    //Formats the dashed lines under each of the headers established above for the output file
    for (i = 1; i <= 11; i++) {
        printf("%c", '-');
        fprintf(fpOut,"%c", '-');
    }
    for (i = 12; i <= 20; i++) {
        printf(" ");
        fprintf(fpOut," ");
    }
    for (i = 21; i <= 27; i++) {
        printf("%c", '-');
        fprintf(fpOut,"%c", '-');
    }
    for (i = 29; i <= 35; i++) {
        printf(" ");
        fprintf(fpOut," ");
    }
    for (i = 36; i <= 40; i++) {
        printf("%c", '-');
        fprintf(fpOut,"%c", '-');
    }
    for (i = 42; i <= 48; i++) {
        printf(" ");
        fprintf(fpOut," ");
    }
    for (i = 49; i <= 55; i++) {
        printf("%c", '-');
        fprintf(fpOut,"%c", '-');
    }
    printf("\n");
    fprintf(fpOut,"\n");
}

void initialBalance(double amount, double* balance, double* service, double* openBalance) {
    //Set the balance of the account to the amount that is read in from the account text file when the inital balance function is called
    *balance = amount;
    //Open balance or the balance at the beginning of the month is also the amount on the first indial call to the inital balance fucntion
    *openBalance = amount;
    //Service fee for the month is charged on the first inital balance as a regular account maintence fee
    service += 3;
    //Print Initial Balance to console and fpOut file
    printf("Initial Balance                                %.2lf\n", *balance);
    fprintf(fpOut,"Initial Balance                                %.2lf\n", *balance);
}

void deposit(double amount, double* balance, double* service, int* numDeposit, double* amtDeposit) {
    //Takes the balance before this function was invoked and adds the last amount to it forming a new balance
    *balance = *balance + amount;
    //Charges the banks service fee per deposit which is 3 cents for every depost
    *service += 0.03;
    //Keeps a running total of just the deposits made by adding the amount to a total of the amount of deposits
    *amtDeposit += amount;
    //Keeps a running total of the number of deposits by incrementing the running total
    *numDeposit = *numDeposit + 1;
    //Print Deposit and remaining Balance to console and fpOut file
    printf("%s%20.2lf%26.2lf\n", "Deposit", amount, *balance);
    fprintf(fpOut,"%s%20.2lf%26.2lf\n", "Deposit", amount, *balance);
}

void check(double amount, double* balance, double* service, int* numCheck, double* amtCheck) {
    //Checks if check written will cause overdraft, if it does it charges a service fee otherwise it just deducts the amount from the account
    if ((*balance - amount) > 0) {
        *balance = *balance - amount;
    } else if ((*balance - amount) < 0) {
        *balance = *balance - amount;
        //Overdraft fee charged to the account if there is insufficent funds
        *service += 5.00;
    }
    //Charges the banks service fee per check which is 6 cents
    *service += 0.06;
    //Keeps a running total of the amount of money paid out of the account in the form of checks
    *amtCheck += amount;
    //Keeps a running total of the number of checks written by incrementing the running total
    *numCheck = *numCheck + 1;
    //Print Check and remaining Balance to console and fpOut file
    printf("%s%34.2lf%14.2lf\n", "Check", amount, *balance);
    fprintf(fpOut,"%s%34.2lf%14.2lf\n", "Check", amount, *balance);
}

void outputSummary(int numDeposit, double amtDeposit, int numCheck, double amtCheck, double openBalance, double service, double closeBalance) {
    //Prints additional details as a summary for the montly statement for the account holder
    printf("\n");
    printf("\n");
    printf("Total number of deposits: %d\n", numDeposit);
    printf("Total amount deposits: %.2lf\n", amtDeposit);
    printf("\n");
    printf("Total number of checks: %d\n", numCheck);
    printf("Total amount checks: %.2lf\n", amtCheck);
    printf("\n");
    printf("Total service charge: %.2lf\n", service);
    printf("\n");
    printf("Opening balance: %.2lf\n", openBalance);
    printf("Closing balance: %.2lf\n", closeBalance);
    
    //Prints same things to the output file
    fprintf(fpOut,"\n");
    fprintf(fpOut,"\n");
    fprintf(fpOut,"Total number of deposits: %d\n", numDeposit);
    fprintf(fpOut,"Total amount deposits: %.2lf\n", amtDeposit);
    fprintf(fpOut,"\n");
    fprintf(fpOut,"Total number of checks: %d\n", numCheck);
    fprintf(fpOut,"Total amount checks: %.2lf\n", amtCheck);
    fprintf(fpOut,"\n");
    fprintf(fpOut,"Total service charge: %.2lf\n", service);
    fprintf(fpOut,"\n");
    fprintf(fpOut,"Opening balance: %.2lf\n", openBalance);
    fprintf(fpOut,"Closing balance: %.2lf\n", closeBalance);
}