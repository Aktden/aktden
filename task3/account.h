#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "observer.h"
#include <string>
#include <ctime>

class Account : public Observable {
protected:
    double balance;
    std::string accountId;
    std::time_t creationDate;
    bool isActive;
public:
    Account(const std::string& accountId, double initialBalance = 0.0);
    virtual ~Account() = default;

    virtual void withdraw(double amount);
    virtual void deposit(double amount);
    virtual bool canOverdraft() const = 0;
    virtual void applyDailyInterest() = 0;
    virtual void applyMonthlyInterest() = 0;
    virtual std::string getType() const = 0;

    double getBalance() const;
    std::string getAccountId() const;
    bool getIsActive() const;
    void deactivate();
};

class DebitAccount : public Account {
private:
    double interestRate;
public:
    DebitAccount(const std::string& accountId, double interestRate, double initialBalance = 0.0);
    bool canOverdraft() const override;
    void applyDailyInterest() override;
    void applyMonthlyInterest() override;
    std::string getType() const override;
};

class DepositAccount : public Account {
private:
    double interestRate;
    std::time_t endDate;
    double initialAmount;
public:
    DepositAccount(const std::string& accountId, double interestRate, std::time_t endDate, double initialBalance = 0.0);
    void withdraw(double amount) override;
    bool canOverdraft() const override;
    void applyDailyInterest() override;
    void applyMonthlyInterest() override;
    std::string getType() const override;
};

class CreditAccount : public Account {
private:
    double creditLimit;
    double commissionRate;
public:
    CreditAccount(const std::string& accountId, double creditLimit, double commissionRate, double initialBalance = 0.0);
    void withdraw(double amount) override;
    bool canOverdraft() const override;
    void applyDailyInterest() override;
    void applyMonthlyInterest() override;
    std::string getType() const override;
};

#endif // ACCOUNT_H
