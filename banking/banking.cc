#include "banking.hh"


int BankAccount::totalAccounts = 0;

const int SUCCESS = 0;
const int AUTH_FAILED = 1;
const int INSUFFICIENT_FUNDS = 2;
const int OTHER_ERROR = 3;

BankAccount::BankAccount(std::string uname, int bal) : username(uname), userid(totalAccounts), balance(bal) {
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

const Receipt createAccount(BankHandler* handler, const char* username, int balance) {
    Bank* bank = static_cast<Bank*> (handler->bank);
    std::string name(username);
    const Receipt receipt = bank->addAccount(name, balance);
    return receipt;
}

 const Receipt checkBalance(BankHandler* handler, const char* username) {
    Bank* bank = static_cast<Bank*> (handler->bank);
    std::string name(username);
    auto account = bank->getAccount(name);
    Receipt receipt;
    if (!account) {
        receipt = {AUTH_FAILED, 0, 0};
    }
    else receipt = account->checkBalance();
    return receipt;
}

const Receipt deposit(BankHandler* handler, const char* username, int value) {
    Bank* bank = static_cast<Bank*> (handler->bank);
    auto account = bank->getAccount(username);
    if (!account) return {AUTH_FAILED, 0, 0};
    return account->deposit(value);
}

const Receipt withdraw(BankHandler* handler, const char* username, int value) {
    Bank* bank = static_cast<Bank*> (handler->bank);
    auto account = bank->getAccount(username);
    if (!account) return {AUTH_FAILED, 0, 0};
    return account->withdraw(value);
}


const Receipt 
Bank::addAccount(const std::string username, int balance) {
    auto existing_account = getAccount(username);
    if (existing_account != nullptr) {
        return {AUTH_FAILED, balance, 0};
    }
    accounts[username] = std::make_shared<BankAccount>(BankAccount{username, balance});
    return {SUCCESS, 0, balance};
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
