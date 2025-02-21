#ifndef SHOPMANAGER_H
#define SHOPMANAGER_H

#include <vector>
#include "Shop.h"

class ShopManager {
public:
    std::vector<Shop> shops;  

    void addShop(const Shop& shop);  
    Shop* findShopWithLowestPrice(int productId);  
};

#endif 

