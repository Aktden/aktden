#include <iostream>
#include "Product.h"
#include "Shop.h"
#include "Buyer.h"
#include "ShopManager.h"

int main() {
    Product apple(1, "Apple");
    Product banana(2, "Banana");

    Shop shop1("Shop 1");
    shop1.addProduct(apple, 10, 1.5);
    shop1.addProduct(banana, 5, 2.0);

    Shop shop2("Shop 2");
    shop2.addProduct(apple, 8, 1.2);
    shop2.addProduct(banana, 7, 2.5);

    ShopManager manager;
    manager.addShop(shop1);
    manager.addShop(shop2);

    Buyer buyer("John", 20.0);
    buyer.addToShoppingList(1, 3); 

    Shop* cheapestShop = manager.findCheapestShop(1);
    if (cheapestShop) {
        std::cout << "Cheapest shop for apples: " << cheapestShop->name << std::endl;
        if (buyer.buyProduct(*cheapestShop, 1, 3)) {
            std::cout << "Purchase successful!" << std::endl;
        }
        else {
            std::cout << "Purchase failed!" << std::endl;
        }
    }
    else {
        std::cout << "No shop found with apples in stock." << std::endl;
    }

    buyer.checkBalance();

    return 0;
}