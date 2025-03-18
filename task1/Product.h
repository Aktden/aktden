#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
public:
    int id;
    std::string name;

    Product(int id, const std::string& name);
};

#endif 
