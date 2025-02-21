#ifndef BUYER_H
#define BUYER_H

#include "Shop.h"

class Buyer {
public:
    int id;         
    double balance; 

    Buyer(int id, double balance);  

    bool buyProduct(Shop& shop, int productId, int quantity);  
};

#endif 

