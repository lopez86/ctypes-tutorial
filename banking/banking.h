/**
 * \file banking.h
 * \brief C/C++ API for the tutorial
 * 
 * This file provides the main C API that we will expose to python.
 * It also allows us to at least somewhat obscure the details of what 
 * we are doing if we only provide this to 3rd parties.
 */
#ifndef BANKING_H
#define BANKING_H

#ifdef __cplusplus
extern "C" {
#endif
    /** Transaction Receipt */
    struct Receipt {
        int status; ///< Status code
        int cash_returned; ///< Amount of cash returned to the user
        int balance; ///< Current balance in the account
    };

    /** Opaque handler for a bank object */
    struct BankHandler {
        void* bank; ///< The bank, must be of type Bank
    };

    extern const int SUCCESS; ///< Successful operation
    extern const int AUTH_FAILED; ///< Authorization failed somehow
    extern const int INSUFFICIENT_FUNDS; ///< Not enough funds for the transaction
    extern const int OTHER_ERROR; ///< Another error

    /** Create a Bank and return a handler to it. */
    struct BankHandler* createBank();
    /** Clear out associated memory with the bank. */
    void destroyBank(struct BankHandler* bankHandler);
    /** Create a new account and deposit funds into it. */
    const struct Receipt createAccount(
        struct BankHandler* handler, const char* username, int balance
    );
    /** Check the balance of an account. */
    const struct Receipt checkBalance(struct BankHandler* handler, const char* username);
    /** Deposit some cash into an account. */
    const struct Receipt deposit(struct BankHandler* handler, const char* username, int value);
    /** Withdraw some cash from an account. */
    const struct Receipt withdraw(struct BankHandler* handler, const char* username, int value);
#ifdef __cplusplus
}
#endif

#endif  /* #ifdef BANKING_H */