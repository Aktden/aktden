#include "Shop.h"

Shop::Shop(const std::string& name) : name(name) {}

void Shop::addProduct(const Product& product, int quantity, double price) {
    products[product.id] = ProductInfo(product, quantity, price);
}

void Shop::removeProduct(int productId) {
    products.erase(productId);
}

void Shop::updateProductQuantity(int productId, int quantity) {
    if (products.find(productId) != products.end()) {
        products[productId].quantity = quantity;
    }
    else {
        throw std::runtime_error("Product not found");
    }
}

void Shop::updateProductPrice(int productId, double price) {
    if (products.find(productId) != products.end()) {
        products[productId].price = price;
    }
    else {
        throw std::runtime_error("Product not found");
    }
}

double Shop::getProductPrice(int productId) {
    if (products.find(productId) != products.end()) {
        return products[productId].price;
    }
    else {
        throw std::runtime_error("Product not found");
    }
}

int Shop::getProductQuantity(int productId) {
    if (products.find(productId) != products.end()) {
        return products[productId].quantity;
    }
    else {
        throw std::runtime_error("Product not found");
    }
}

bool Shop::sellProduct(int productId, int quantity) {
    if (products.find(productId) != products.end() && products[productId].quantity >= quantity) {
        products[productId].quantity -= quantity;
        return true;
    }
    else {
        return false;
    }
}