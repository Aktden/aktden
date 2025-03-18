#ifndef SHOP_H
#define SHOP_H

#include <map>
#include <string>
#include <stdexcept>
#include "ProductInfo.h"

class Shop {
public:
    std::string name;
    std::map<int, ProductInfo> products;

    Shop(const std::string& name);

    void addProduct(const Product& product, int quantity, double price);
    void removeProduct(int productId);
    void updateProductQuantity(int productId, int quantity);
    void updateProductPrice(int productId, double price);
    double getProductPrice(int productId);
    int getProductQuantity(int productId);
    bool sellProduct(int productId, int quantity);
};

#endif 