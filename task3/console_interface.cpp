#include "console_interface.h"
#include "bank.h"
#include "client.h"
#include "exceptions.h"
#include <iostream>
#include <limits>

ConsoleInterface::ConsoleInterface() : centralBank(CentralBank::getInstance()) {}

void ConsoleInterface::run() {
    while (true) {
        displayMenu();
        processUserChoice();
    }
}

void ConsoleInterface::displayMenu() {
    std::cout << "\nBanking System Menu:\n";
    std::cout << "1. Create Bank\n";
    std::cout << "2. Create Client\n";
    std::cout << "3. Create Account\n";
    std::cout << "4. Make Transaction\n";
    std::cout << "5. View Account Balance\n";
    std::cout << "6. Revert Transaction\n";
    std::cout << "7. Simulate Time Pass (Day)\n";
    std::cout << "8. Simulate Time Pass (Month)\n";
    std::cout << "9. Exit\n";
    std::cout << "Enter your choice: ";
}

void ConsoleInterface::processUserChoice() {
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    try {
        switch (choice) {
        case 1: createBank(); break;
        case 2: createClient(); break;
        case 3: createAccount(); break;
        case 4: makeTransaction(); break;
        case 5: viewAccountBalance(); break;
        case 6: revertTransaction(); break;
        case 7: simulateDay(); break;
        case 8: simulateMonth(); break;
        case 9: exit(0);
        default: std::cout << "Invalid choice. Try again.\n";
        }
    }
    catch (const BankException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "Unknown error occurred\n";
    }
}

void ConsoleInterface::createBank() {
    std::string bankId, name;
    double debitRate, creditCommission, creditLimit, unverifiedLimit;

    std::cout << "Enter bank ID: ";
    std::getline(std::cin, bankId);
    std::cout << "Enter bank name: ";
    std::getline(std::cin, name);
    std::cout << "Enter debit interest rate (%): ";
    std::cin >> debitRate;
    std::cout << "Enter credit commission rate (%): ";
    std::cin >> creditCommission;
    std::cout << "Enter credit limit: ";
    std::cin >> creditLimit;
    std::cout << "Enter unverified client withdrawal limit: ";
    std::cin >> unverifiedLimit;

    std::unordered_map<double, double> depositRates;
    depositRates[1000] = 3.0;
    depositRates[10000] = 4.0;
    depositRates[50000] = 5.0;

    auto bank = std::make_shared<Bank>(bankId, name, debitRate, depositRates,
        creditCommission, creditLimit, unverifiedLimit);
    centralBank->registerBank(bank);
    banks[bankId] = bank;

    std::cout << "Bank created successfully.\n";
}

void ConsoleInterface::createClient() {
    if (banks.empty()) {
        std::cout << "No banks available. Create a bank first.\n";
        return;
    }

    std::string bankId, firstName, lastName, passport, address;
    std::cout << "Enter bank ID: ";
    std::getline(std::cin, bankId);

    if (banks.find(bankId) == banks.end()) {
        std::cout << "Bank not found.\n";
        return;
    }

    std::cout << "Enter first name: ";
    std::getline(std::cin, firstName);
    std::cout << "Enter last name: ";
    std::getline(std::cin, lastName);
    std::cout << "Enter passport number (optional): ";
    std::getline(std::cin, passport);
    std::cout << "Enter address (optional): ";
    std::getline(std::cin, address);

    ClientPersonalData personalData(firstName, lastName, passport, address);
    auto client = banks[bankId]->createClient(personalData);
    clients[firstName + " " + lastName] = client;

    std::cout << "Client created successfully.\n";
}

void ConsoleInterface::createAccount() {
    if (clients.empty()) {
        std::cout << "No clients available. Create a client first.\n";
        return;
    }

    std::string clientName, bankId;
    std::cout << "Enter client name (First Last): ";
    std::getline(std::cin, clientName);

    if (clients.find(clientName) == clients.end()) {
        std::cout << "Client not found.\n";
        return;
    }

    std::cout << "Enter bank ID: ";
    std::getline(std::cin, bankId);

    if (banks.find(bankId) == banks.end()) {
        std::cout << "Bank not found.\n";
        return;
    }

    int accountType;
    std::cout << "Select account type:\n";
    std::cout << "1. Debit\n";
    std::cout << "2. Deposit\n";
    std::cout << "3. Credit\n";
    std::cout << "Enter choice: ";
    std::cin >> accountType;

    std::shared_ptr<Account> account;
    switch (accountType) {
    case 1: {
        account = banks[bankId]->createDebitAccount(clients[clientName]);
        break;
    }
    case 2: {
        double initialAmount;
        int days;
        std::cout << "Enter initial amount: ";
        std::cin >> initialAmount;
        std::cout << "Enter deposit term in days: ";
        std::cin >> days;
        std::time_t endDate = std::time(nullptr) + days * 24 * 60 * 60;
        account = banks[bankId]->createDepositAccount(clients[clientName], initialAmount, endDate);
        break;
    }
    case 3: {
        account = banks[bankId]->createCreditAccount(clients[clientName]);
        break;
    }
    default: {
        std::cout << "Invalid account type.\n";
        return;
    }
    }

    std::cout << "Account created successfully. Account ID: " << account->getAccountId() << "\n";
}

void ConsoleInterface::makeTransaction() {
    std::string fromAccountId, toAccountId;
    double amount;

    std::cout << "Enter source account ID: ";
    std::getline(std::cin, fromAccountId);
    std::cout << "Enter destination account ID: ";
    std::getline(std::cin, toAccountId);
    std::cout << "Enter amount: ";
    std::cin >> amount;

    std::cout << "Transaction functionality not fully implemented in this example.\n";
}

void ConsoleInterface::viewAccountBalance() {
    std::string accountId;
    std::cout << "Enter account ID: ";
    std::getline(std::cin, accountId);

    std::cout << "Account balance functionality not fully implemented in this example.\n";
}

void ConsoleInterface::revertTransaction() {
    std::string transactionId;
    std::cout << "Enter transaction ID to revert: ";
    std::getline(std::cin, transactionId);

    std::cout << "Transaction revert functionality not fully implemented in this example.\n";
}

void ConsoleInterface::simulateDay() {
    centralBank->notifyBanksAboutNewDay();
    std::cout << "Day simulated. Daily interests applied.\n";
}

void ConsoleInterface::simulateMonth() {
    centralBank->notifyBanksAboutNewMonth();
    std::cout << "Month simulated. Monthly interests and commissions applied.\n";
}