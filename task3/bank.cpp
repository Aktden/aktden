#include "bank.h"
#include "exceptions.h"
#include <ctime>

Bank::Bank(const std::string& bankId, const std::string& name,
    double debitInterestRate, const std::unordered_map<double, double>& depositInterestRates,
    double creditCommissionRate, double creditLimit, double unverifiedWithdrawalLimit)
    : bankId(bankId), name(name), debitInterestRate(debitInterestRate),
    depositInterestRates(depositInterestRates), creditCommissionRate(creditCommissionRate),
    creditLimit(creditLimit), unverifiedWithdrawalLimit(unverifiedWithdrawalLimit) {}

std::shared_ptr<Client> Bank::createClient(const ClientPersonalData& personalData) {
    auto client = std::make_shared<Client>(personalData);
    clients.push_back(client);
    return client;
}

std::shared_ptr<Account> Bank::createDebitAccount(const std::shared_ptr<Client>& client) {
    std::string accountId = generateAccountId();
    auto account = std::make_shared<DebitAccount>(accountId, debitInterestRate);
    client->addAccount(account);
    accounts[accountId] = account;
    return account;
}

std::shared_ptr<Account> Bank::createDepositAccount(const std::shared_ptr<Client>& client,
    double initialAmount, std::time_t endDate) {
    std::string accountId = generateAccountId();
    double interestRate = getDepositInterestRate(initialAmount);
    auto account = std::make_shared<DepositAccount>(accountId, interestRate, endDate, initialAmount);
    client->addAccount(account);
    accounts[accountId] = account;
    return account;
}

std::shared_ptr<Account> Bank::createCreditAccount(const std::shared_ptr<Client>& client) {
    std::string accountId = generateAccountId();
    auto account = std::make_shared<CreditAccount>(accountId, creditLimit, creditCommissionRate);
    client->addAccount(account);
    accounts[accountId] = account;
    return account;
}

std::shared_ptr<Transaction> Bank::createTransfer(const std::string& transactionId, double amount,
    const std::shared_ptr<Account>& fromAccount,
    const std::shared_ptr<Account>& toAccount) {
    if (!fromAccount || !toAccount) throw InvalidTransactionException("Invalid accounts");

    auto fromClient = findClientByAccount(fromAccount);
    if (!fromClient->isVerified() && amount > unverifiedWithdrawalLimit) {
        throw InvalidTransactionException("Unverified client cannot transfer more than the limit");
    }

    auto transaction = std::make_shared<TransferTransaction>(transactionId, amount, fromAccount, toAccount);
    transactions[transactionId] = transaction;
    return transaction;
}

void Bank::executeTransaction(const std::string& transactionId) {
    if (transactions.find(transactionId) == transactions.end()) {
        throw InvalidTransactionException("Transaction not found");
    }
    transactions[transactionId]->execute();
}

void Bank::revertTransaction(const std::string& transactionId) {
    if (transactions.find(transactionId) == transactions.end()) {
        throw InvalidTransactionException("Transaction not found");
    }
    transactions[transactionId]->revert();
}

void Bank::applyDailyInterest() {
    for (auto& accountPair : accounts) {
        accountPair.second->applyDailyInterest();
    }
}

void Bank::applyMonthlyInterest() {
    for (auto& accountPair : accounts) {
        accountPair.second->applyMonthlyInterest();
    }
}

std::shared_ptr<Client> Bank::findClientByAccount(const std::shared_ptr<Account>& account) {
    for (auto& client : clients) {
        for (auto& clientAccount : client->getAccounts()) {
            if (clientAccount->getAccountId() == account->getAccountId()) {
                return client;
            }
        }
    }
    return nullptr;
}

std::string Bank::getBankId() const {
    return bankId;
}

// Вспомогательные методы
std::string Bank::generateAccountId() {
    return bankId + "-" + std::to_string(accounts.size() + 1);
}

double Bank::getDepositInterestRate(double amount) {
    double bestRate = 0.0;
    for (auto& [minAmount, rate] : depositInterestRates) {
        if (amount >= minAmount && rate > bestRate) {
            bestRate = rate;
        }
    }
    return bestRate;
}