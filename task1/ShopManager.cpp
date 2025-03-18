#include "ShopManager.h"
#include <limits>

void ShopManager::addShop(const Shop& shop) {
    shops.push_back(shop);
}

Shop* ShopManager::findCheapestShop(int productId) {
    Shop* cheapestShop = nullptr;
    double minPrice = std::numeric_limits<double>::max();

    for (auto& shop : shops) {
        try {
            double price = shop.getProductPrice(productId);
            if (price < minPrice) {
                minPrice = price;
                cheapestShop = &shop;
            }
        }
        catch (const std::runtime_error&) {
            continue;
        }
    }

    return cheapestShop;
}

Shop* ShopManager::getShopByName(const std::string& name) {
    for (auto& shop : shops) {
        if (shop.name == name) {
            return &shop;
        }
    }
    return nullptr;
}