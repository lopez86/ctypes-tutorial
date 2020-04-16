#include "banking.hh"
#include "security.hh"


int BankAccount::totalAccounts = 0;

const int SUCCESS = 0;
const int AUTH_FAILED = 1;
const int INSUFFICIENT_FUNDS = 2;
const int OTHER_ERROR = 3;


/**
 * Function to handle getting an account and verifying its credentials.
 */
std::shared_ptr<BankAccount> getValidatedAccount(
    BankHandler* handler, std::string username, std::string password    
) {
    Bank* bank = static_cast<Bank*> (handler->bank);
    auto account = bank->getAccount(username);
    if (
        !account ||
        !security::superSecretCheckHashFunction(password, account->getPasswordHash())

    ) {
        return nullptr;
    }
    return account;
}


BankAccount::BankAccount(std::string uname, std::string pwd, int bal) : 
    username(uname),
    passwordHash(pwd),
    userid(totalAccounts),
    balance(bal) {
    ++totalAccounts;
}

const Receipt
BankAccount::checkBalance() const {
    return {SUCCESS, 0, balance};
}

const Receipt
BankAccount::deposit(int value) {
    balance = balance + value;
    return {SUCCESS, 0, balance};
}

const Receipt
BankAccount::withdraw(int value) {
    int proposed_balance = balance - value;
    int status;
    int cash_returned;
    if (proposed_balance < 0) {
        status = INSUFFICIENT_FUNDS;
        cash_returned = value;
    } else{
        balance = proposed_balance;
        status = SUCCESS;
        cash_returned = 0;
    }
    return {status, cash_returned, balance};
}

BankHandler* createBank() {
    return new BankHandler{new Bank};
}

void destroyBank(BankHandler* bankHandler) {
    if (!bankHandler) return;
    Bank* bank = static_cast<Bank*> (bankHandler->bank);
    if (bank) delete bank;
    delete bankHandler;
}

const Receipt createAccount(
    BankHandler* handler, const char* username, const char* password, int balance
) {
    Bank* bank = static_cast<Bank*> (handler->bank);
    std::string pwdHash = security::superSecretHashFunction(password);
    auto newAccount = std::make_shared<BankAccount>(BankAccount{username, pwdHash, balance});
    const Receipt receipt = bank->addAccount(newAccount);
    return receipt;
}

 const Receipt checkBalance(BankHandler* handler, const char* username, const char* password) {
    auto account = getValidatedAccount(handler, username, password);
    if (!account) {
        return {AUTH_FAILED, 0, 0};
    }
    return account->checkBalance();
}

const Receipt deposit(BankHandler* handler, const char* username, const char* password, int value) {
    auto account = getValidatedAccount(handler, username, password);
    if (!account) {
        return {AUTH_FAILED, value, 0};
    }
    return account->deposit(value);
}

const Receipt withdraw(BankHandler* handler, const char* username, const char* password, int value) {
    auto account = getValidatedAccount(handler, username, password);
    if (!account) {
        return {AUTH_FAILED, 0, 0};
    }
    return account->withdraw(value);
}


const Receipt 
Bank::addAccount(std::shared_ptr<BankAccount> newAccount) {
    auto existing_account = getAccount(newAccount->getUsername());
    if (existing_account != nullptr) {
        return {AUTH_FAILED, newAccount->getBalance(), 0};
    }
    accounts[newAccount->getUsername()] = newAccount;
    return {SUCCESS, 0, newAccount->getBalance()};
}

std::shared_ptr<BankAccount> 
Bank::getAccount(const std::string username) {
    std::shared_ptr<BankAccount> result = nullptr;
    auto entry = accounts.find(username);
    if (entry != accounts.end()) result = entry->second;
    return result;
}

const std::shared_ptr<BankAccount> 
Bank::getAccount(const std::string username) const {
    std::shared_ptr<BankAccount> result = nullptr;
    auto entry = accounts.find(username);
    if (entry != accounts.end()) result = entry->second;
    return result;
}
