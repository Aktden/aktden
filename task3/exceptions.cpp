#include "exceptions.h"

BankException::BankException(const std::string& message)
    : std::runtime_error(message) {}

InsufficientFundsException::InsufficientFundsException(const std::string& message)
    : BankException(message) {}

InvalidTransactionException::InvalidTransactionException(const std::string& message)
    : BankException(message) {}