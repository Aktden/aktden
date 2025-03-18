#ifndef BUYER_H
#define BUYER_H

#include <map>
#include <string>
#include "Shop.h"

class Buyer {
public:
    std::string name;
    double balance;
    std::map<int, int> shoppingList;

    Buyer(const std::string& name, double balance);

    void addFunds(double amount);
    void addToShoppingList(int productId, int quantity);
    bool buyProduct(Shop& shop, int productId, int quantity);
    void checkBalance() const;
};

#endif 
