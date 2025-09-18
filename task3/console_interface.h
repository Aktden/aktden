#ifndef CONSOLE_INTERFACE_H
#define CONSOLE_INTERFACE_H

#include "central_bank.h"
#include <unordered_map>
#include <memory>

class ConsoleInterface {
private:
    CentralBank* centralBank;
    std::unordered_map<std::string, std::shared_ptr<Bank>> banks;
    std::unordered_map<std::string, std::shared_ptr<Client>> clients;

public:
    ConsoleInterface();
    void run();

private:
    void displayMenu();
    void processUserChoice();
    void createBank();
    void createClient();
    void createAccount();
    void makeTransaction();
    void viewAccountBalance();
    void revertTransaction();
    void simulateDay();
    void simulateMonth();
};

#endif // CONSOLE_INTERFACE_H
