/**
 * \file bank_example.c
 * \brief Quick example using the library in C
 * 
 * To run:
 * >>> make
 * >>> LD_LIBRARY_PATH=$PWD/banking:$LD_LIBRARY_PATH ./bank_example.exe
 */ 
#include <stdio.h>

#include "banking/banking.h"


/** Print the result of a transaction. */
void print_result(const struct Receipt receipt) {
    printf(
        "Receipt, Status: %d, Cash returned: %d, Current balance: %d\n",
        receipt.status,
        receipt.cash_returned,
        receipt.balance
    );
};


/**
 * The example code.
 * 
 * Creates a bank and runs some commands, printing out results.
 */ 
int main() {
    printf("Creating bank\n");
    struct BankHandler* handler = createBank();
    printf("Creating account\n");
    createAccount(handler, "bill gates", "msft", 100);
    printf("Checking balance, wrong account\n");
    print_result(checkBalance(handler, "jeff bezos", "amzn"));
    printf("Checking balance, wrong password\n");
    print_result(checkBalance(handler, "bill gates", "amzn"));
    printf("Checking balance\n");
    print_result(checkBalance(handler, "bill gates", "msft"));
    printf("Deposit money\n");
    print_result(deposit(handler, "bill gates", "msft", 10));
    printf("Withdraw money\n");
    print_result(withdraw(handler, "bill gates", "msft", 15));
    printf("Trying to withdraw too much\n");
    print_result(withdraw(handler, "bill gates", "msft", 1000));

    destroyBank(handler);
    return 0;
}
