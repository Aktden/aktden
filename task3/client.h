#ifndef CLIENT_H
#define CLIENT_H

#include "observer.h"
#include <string>
#include <memory>
#include <vector>

class Account;
class ClientPersonalData;

class Client : public Observer {
private:
    ClientPersonalData personalData;
    std::vector<std::shared_ptr<Account>> accounts;
public:
    Client(const ClientPersonalData& personalData);
    void addAccount(const std::shared_ptr<Account>& account);
    const std::vector<std::shared_ptr<Account>>& getAccounts() const;
    const ClientPersonalData& getPersonalData() const;
    void update(const std::string& message) override;
    bool isVerified() const;
};

class ClientPersonalData {
private:
    std::string firstName;
    std::string lastName;
    std::string passportNumber;
    std::string address;
public:
    ClientPersonalData(const std::string& firstName, const std::string& lastName,
        const std::string& passportNumber = "", const std::string& address = "");
    bool isVerified() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getPassportNumber() const;
    std::string getAddress() const;
};

#endif 
