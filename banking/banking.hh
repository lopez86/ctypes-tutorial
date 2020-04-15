/** 
 * \file banking.hh
 * \brief Defines C++ API for our toy ctypes tutorial
 * 
 * This header defines the main data structures used internally in the tutorial.
 * The code that we are running requires these classes but we don't need to
 * expose the APIs to the outside world if we only want to force users to use
 * the C API.
 */ 
#ifndef BANKING_HH
#define BANKING_HH

#include <map>
#include <memory>
#include <string>

#include "banking.h"

/* C++ API */

/**
 * Class to represent a bank account.
 * 
 * A bank account here has a username, a balance, and an internal unique id. 
 * The username is used for user-facing operations and must also be unique.
 * The balance is determined by an integer value to prevent rounding errors.
 * Note that this might not be ideal for operations like interest payments unless
 * care is taken to deal with rounding properly.
 */
class BankAccount {
    public:
        /** Constructor for a new bank account. */
        BankAccount(const std::string username, int balance);
        /** Destructor. */
        virtual ~BankAccount() {}

        /** Check the balance of the account. */
        const Receipt checkBalance() const;
        /** Deposit funds into the account. */
        const Receipt deposit(int value);
        /** Withdraw funds into the account. */
        const Receipt withdraw(int value);

        /** Get the user id. */
        int getUserid() const {return userid;}
        /** Get the user name. */
        std::string getUsername() const {return username;}

    private:
        std::string username; ///< The unique username
        int userid; ///< The internal user id
        int balance; ///< The balance in the account

        static int totalAccounts; ///< The total number of accounts that have been made
};


/**
 * Class to represent a bank.
 * 
 * This bank simply holds accounts and can also add new accounts.
 * Account removal is not allowed right now.
 * In real code, the account and bank abstractions would probably
 * really be abstractions around some sort of database system but here
 * we just use a map from username to an account object.
 */
class Bank {
    public:
        /** Constructor. */
        Bank() {}
        /** Destructor. */
        virtual ~Bank(){}

        /** Add a new account. */
        const Receipt addAccount(const std::string username, int balance);
        /** Get an account. */
        std::shared_ptr<BankAccount> getAccount(const std::string username);
        /** Get an account, const version. */
        const std::shared_ptr<BankAccount> getAccount(const std::string username) const;

    private:
        std::map<std::string, std::shared_ptr<BankAccount> > accounts; ///< The accounts.

};

#endif // #ifdef BANKING_HH
