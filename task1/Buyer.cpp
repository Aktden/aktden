#include "Buyer.h"
#include <iostream>

Buyer::Buyer(const std::string& name, double balance) : name(name), balance(balance) {}

void Buyer::addFunds(double amount) {
    balance += amount;
}

void Buyer::addToShoppingList(int productId, int quantity) {
    shoppingList[productId] = quantity;
}

bool Buyer::buyProduct(Shop& shop, int productId, int quantity) {
    double totalCost = shop.getProductPrice(productId) * quantity;
    if (balance >= totalCost && shop.sellProduct(productId, quantity)) {
        balance -= totalCost;
        return true;
    }
    else {
        return false;
    }
}

void Buyer::checkBalance() const {
    std::cout << "Balance: " << balance << std::endl;
}