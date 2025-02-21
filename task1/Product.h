#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
public:
    std::string title;  
    int id;             

    Product(const std::string& title, int id);  
};

#endif 

