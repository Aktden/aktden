#ifndef CENTRAL_BANK_H
#define CENTRAL_BANK_H

#include "bank.h"
#include "transaction.h"
#include <unordered_map>
#include <memory>

class CentralBank {
private:
    static CentralBank* instance;
    std::unordered_map<std::string, std::shared_ptr<Bank>> banks;
    std::unordered_map<std::string, std::shared_ptr<Transaction>> interbankTransactions;

    CentralBank() = default;

public:
    static CentralBank* getInstance();
    void registerBank(const std::shared_ptr<Bank>& bank);
    std::shared_ptr<Transaction> createInterbankTransfer(const std::string& transactionId, double amount,
        const std::shared_ptr<Account>& fromAccount,
        const std::shared_ptr<Account>& toAccount);
    void executeInterbankTransfer(const std::string& transactionId);
    void notifyBanksAboutNewDay();
    void notifyBanksAboutNewMonth();
};

#endif 
