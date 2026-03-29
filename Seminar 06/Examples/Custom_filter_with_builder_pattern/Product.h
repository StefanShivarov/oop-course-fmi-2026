#pragma once
#include <iostream>

class Product {
private:
    char* name;
    double price;
    int quantity;

    void copyFrom(const Product& other);
    void free();

public:
    Product(const char* name, double price, int quantity);
    Product(const Product& other);
    Product& operator=(const Product& other);
    ~Product();

    const char* getName() const;
    double getPrice() const;
    int getQuantity() const;
};

std::ostream& operator<<(std::ostream& os, const Product& product);
