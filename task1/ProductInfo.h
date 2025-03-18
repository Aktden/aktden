#ifndef PRODUCTINFO_H
#define PRODUCTINFO_H

#include "Product.h"

class ProductInfo {
public:
    Product product;
    int quantity;
    double price;

    ProductInfo(const Product& product, int quantity, double price);
};

#endif 

