#include "central_bank.h"

CentralBank* CentralBank::instance = nullptr;

CentralBank* CentralBank::getInstance() {
    if (!instance) {
        instance = new CentralBank();
    }
    return instance;
}

void CentralBank::registerBank(const std::shared_ptr<Bank>& bank) {
    banks[bank->getBankId()] = bank;
}

std::shared_ptr<Transaction> CentralBank::createInterbankTransfer(const std::string& transactionId, double amount,
    const std::shared_ptr<Account>& fromAccount,
    const std::shared_ptr<Account>& toAccount) {
    auto transaction = std::make_shared<TransferTransaction>(transactionId, amount, fromAccount, toAccount);
    interbankTransactions[transactionId] = transaction;
    return transaction;
}

void CentralBank::executeInterbankTransfer(const std::string& transactionId) {
    if (interbankTransactions.find(transactionId) == interbankTransactions.end()) {
        throw InvalidTransactionException("Interbank transaction not found");
    }
    interbankTransactions[transactionId]->execute();
}

void CentralBank::notifyBanksAboutNewDay() {
    for (auto& bankPair : banks) {
        bankPair.second->applyDailyInterest();
    }
}

void CentralBank::notifyBanksAboutNewMonth() {
    for (auto& bankPair : banks) {
        bankPair.second->applyMonthlyInterest();
    }
}