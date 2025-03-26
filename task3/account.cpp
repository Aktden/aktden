#include "account.h"
#include <stdexcept>

Account::Account(const std::string& accountId, double initialBalance)
    : accountId(accountId), balance(initialBalance),
    creationDate(std::time(nullptr)), isActive(true) {}

void Account::withdraw(double amount) {
    if (!isActive) throw BankException("Account is not active");
    if (amount <= 0) throw InvalidTransactionException("Invalid amount");
    if (amount > balance && !canOverdraft()) {
        throw InsufficientFundsException("Insufficient funds");
    }

    balance -= amount;
    notifyObservers("Withdrawal of " + std::to_string(amount) + " from account " + accountId);
}

void Account::deposit(double amount) {
    if (!isActive) throw BankException("Account is not active");
    if (amount <= 0) throw InvalidTransactionException("Invalid amount");

    balance += amount;
    notifyObservers("Deposit of " + std::to_string(amount) + " to account " + accountId);
}

double Account::getBalance() const { return balance; }
std::string Account::getAccountId() const { return accountId; }
bool Account::getIsActive() const { return isActive; }
void Account::deactivate() { isActive = false; }

DebitAccount::DebitAccount(const std::string& accountId, double interestRate, double initialBalance)
    : Account(accountId, initialBalance), interestRate(interestRate) {}

bool DebitAccount::canOverdraft() const { return false; }

void DebitAccount::applyDailyInterest() {
    balance += balance * (interestRate / 36500);
}

void DebitAccount::applyMonthlyInterest() {
    balance += balance * (interestRate / 1200);
}

std::string DebitAccount::getType() const { return "Debit"; }

DepositAccount::DepositAccount(const std::string& accountId, double interestRate,
    std::time_t endDate, double initialBalance)
    : Account(accountId, initialBalance), interestRate(interestRate),
    endDate(endDate), initialAmount(initialBalance) {}

void DepositAccount::withdraw(double amount) {
    if (std::time(nullptr) < endDate) {
        throw BankException("Cannot withdraw from deposit account before end date");
    }
    Account::withdraw(amount);
}

bool DepositAccount::canOverdraft() const { return false; }

void DepositAccount::applyDailyInterest() {
}

void DepositAccount::applyMonthlyInterest() {
    balance += balance * (interestRate / 1200);
}

std::string DepositAccount::getType() const { return "Deposit"; }

CreditAccount::CreditAccount(const std::string& accountId, double creditLimit,
    double commissionRate, double initialBalance)
    : Account(accountId, initialBalance), creditLimit(creditLimit),
    commissionRate(commissionRate) {}

void CreditAccount::withdraw(double amount) {
    if (amount > balance + creditLimit) {
        throw InsufficientFundsException("Exceeds credit limit");
    }
    Account::withdraw(amount);
}

bool CreditAccount::canOverdraft() const { return true; }

void CreditAccount::applyDailyInterest() {
    
}

void CreditAccount::applyMonthlyInterest() {
    if (balance < 0) {
        balance -= (-balance) * (commissionRate / 100);
    }
}

std::string CreditAccount::getType() const { return "Credit"; }