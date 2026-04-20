#include "Product.h"
#include <cstring>
#pragma warning(disable:4996)

void Product::copyFrom(const Product& other) {
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    price = other.price;
    quantity = other.quantity;
}

void Product::free() {
    delete[] name;
    name = nullptr;
}

Product::Product(const char* name, double price, int quantity) : price(price), quantity(quantity) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

Product::Product(const Product& other) {
    copyFrom(other);
}

Product& Product::operator=(const Product& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Product::~Product() {
    free();
}

const char* Product::getName() const {
    return name;
}

double Product::getPrice() const {
    return price;
}

int Product::getQuantity() const {
    return quantity;
}

std::ostream& operator<<(std::ostream& os, const Product& product) {
    os << product.getName() << " " << product.getPrice() << " " << product.getQuantity();
    return os;
}
