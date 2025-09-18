#include "transaction.h"
#include "account.h"
#include "exceptions.h"

Transaction::Transaction(const std::string& transactionId, double amount)
    : transactionId(transactionId), amount(amount), timestamp(std::time(nullptr)),
    isExecuted(false), isReverted(false) {}

std::string Transaction::getTransactionId() const { return transactionId; }
double Transaction::getAmount() const { return amount; }
std::time_t Transaction::getTimestamp() const { return timestamp; }
bool Transaction::getIsExecuted() const { return isExecuted; }
bool Transaction::getIsReverted() const { return isReverted; }

TransferTransaction::TransferTransaction(const std::string& transactionId, double amount,
    const std::shared_ptr<Account>& fromAccount,
    const std::shared_ptr<Account>& toAccount)
    : Transaction(transactionId, amount), fromAccount(fromAccount), toAccount(toAccount) {}

void TransferTransaction::execute() {
    if (isExecuted) throw InvalidTransactionException("Transaction already executed");
    if (isReverted) throw InvalidTransactionException("Transaction was reverted");

    fromAccount->withdraw(amount);
    toAccount->deposit(amount);

    isExecuted = true;
}

void TransferTransaction::revert() {
    if (!isExecuted) throw InvalidTransactionException("Transaction not executed yet");
    if (isReverted) throw InvalidTransactionException("Transaction already reverted");

    toAccount->withdraw(amount);
    fromAccount->deposit(amount);

    isReverted = true;
}