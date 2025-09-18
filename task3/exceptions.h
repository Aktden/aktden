#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class BankException : public std::runtime_error {
public:
    explicit BankException(const std::string& message);
};

class InsufficientFundsException : public BankException {
public:
    explicit InsufficientFundsException(const std::string& message);
};

class InvalidTransactionException : public BankException {
public:
    explicit InvalidTransactionException(const std::string& message);
};

#endif 
