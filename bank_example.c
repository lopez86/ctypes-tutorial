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
    struct BankHandler* handler = createBank();
    struct Receipt result;

    createAccount(handler, "bill gates", 100);
    result = checkBalance(handler, "jeff bezos");
    print_result(result);
    result = checkBalance(handler, "bill gates");
    print_result(result);
    result = deposit(handler, "bill gates", 10);
    print_result(result);
    result = withdraw(handler, "bill gates", 15);
    print_result(result);
    result = withdraw(handler, "bill gates", 1000);
    print_result(result);

    destroyBank(handler);
    return 0;
}
