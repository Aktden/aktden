#ifndef SHOP_H
#define SHOP_H

#include <vector>
#include <utility>
#include "Product.h"
#include "ProductInfo.h"

class Shop {
public:
    std::string title;  
    std::vector<std::pair<Product, ProductInfo>> products;  

    Shop(const std::string title);  

    void addProduct(const Product product, double price, int quantity);  
    bool buyProduct(int productId, int quantity);  
    double getPrice(int productId);  
    int getQuantity(int productId);  
};

#endif 

