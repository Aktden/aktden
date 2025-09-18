#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>
#include <memory>

class Account;

class Transaction {
protected:
    std::string transactionId;
    double amount;
    std::time_t timestamp;
    bool isExecuted;
    bool isReverted;
public:
    Transaction(const std::string& transactionId, double amount);
    virtual ~Transaction() = default;

    virtual void execute() = 0;
    virtual void revert() = 0;

    std::string getTransactionId() const;
    double getAmount() const;
    std::time_t getTimestamp() const;
    bool getIsExecuted() const;
    bool getIsReverted() const;
};

class TransferTransaction : public Transaction {
private:
    std::shared_ptr<Account> fromAccount;
    std::shared_ptr<Account> toAccount;
public:
    TransferTransaction(const std::string& transactionId, double amount,
        const std::shared_ptr<Account>& fromAccount,
        const std::shared_ptr<Account>& toAccount);
    void execute() override;
    void revert() override;
};

#endif // TRANSACTION_H
