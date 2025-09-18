#ifndef BANK_H
#define BANK_H

#include "account.h"
#include "client.h"
#include "transaction.h"
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class Bank : public Observable {
private:
    std::string bankId;
    std::string name;
    std::vector<std::shared_ptr<Client>> clients;
    std::unordered_map<std::string, std::shared_ptr<Account>> accounts;
    std::unordered_map<std::string, std::shared_ptr<Transaction>> transactions;

    double debitInterestRate;
    std::unordered_map<double, double> depositInterestRates;
    double creditCommissionRate;
    double creditLimit;
    double unverifiedWithdrawalLimit;

public:
    Bank(const std::string& bankId, const std::string& name,
        double debitInterestRate, const std::unordered_map<double, double>& depositInterestRates,
        double creditCommissionRate, double creditLimit, double unverifiedWithdrawalLimit);

    std::shared_ptr<Client> createClient(const ClientPersonalData& personalData);
    std::shared_ptr<Account> createDebitAccount(const std::shared_ptr<Client>& client);
    std::shared_ptr<Account> createDepositAccount(const std::shared_ptr<Client>& client,
        double initialAmount, std::time_t endDate);
    std::shared_ptr<Account> createCreditAccount(const std::shared_ptr<Client>& client);
    std::shared_ptr<Transaction> createTransfer(const std::string& transactionId, double amount,
        const std::shared_ptr<Account>& fromAccount,
        const std::shared_ptr<Account>& toAccount);
    void executeTransaction(const std::string& transactionId);
    void revertTransaction(const std::string& transactionId);
    void applyDailyInterest();
    void applyMonthlyInterest();
    std::shared_ptr<Client> findClientByAccount(const std::shared_ptr<Account>& account);
    std::string getBankId() const;
};

#endif // BANK_H
