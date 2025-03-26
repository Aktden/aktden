#include "client.h"
#include "account.h"

Client::Client(const ClientPersonalData& personalData)
    : personalData(personalData) {}

void Client::addAccount(const std::shared_ptr<Account>& account) {
    accounts.push_back(account);
    account->addObserver(this);
}

const std::vector<std::shared_ptr<Account>>& Client::getAccounts() const {
    return accounts;
}

const ClientPersonalData& Client::getPersonalData() const {
    return personalData;
}

void Client::update(const std::string& message) {
    std::cout << "Notification for client " << personalData.getFirstName()
        << " " << personalData.getLastName() << ": " << message << std::endl;
}

bool Client::isVerified() const {
    return personalData.isVerified();
}

ClientPersonalData::ClientPersonalData(const std::string& firstName, const std::string& lastName,
    const std::string& passportNumber, const std::string& address)
    : firstName(firstName), lastName(lastName), passportNumber(passportNumber), address(address) {
    if (firstName.empty() || lastName.empty()) {
        throw BankException("First and last name are required");
    }
}

bool ClientPersonalData::isVerified() const {
    return !passportNumber.empty() && !address.empty();
}

std::string ClientPersonalData::getFirstName() const { return firstName; }
std::string ClientPersonalData::getLastName() const { return lastName; }
std::string ClientPersonalData::getPassportNumber() const { return passportNumber; }
std::string ClientPersonalData::getAddress() const { return address; }