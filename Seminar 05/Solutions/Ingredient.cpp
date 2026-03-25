//
// Created by Boris Bozhilov on 3/23/2026.
//

#include "Ingredient.h"
#include <cstring>
#include <iostream>

Ingredient::Ingredient() : name(MyString("")), quantity(0), metricUnit(MyString("")) {
};

Ingredient::Ingredient(const MyString &name, const unsigned int quantity, const MyString &metricUnit)
    : name(name), quantity(quantity), metricUnit(metricUnit) {
}

Ingredient::Ingredient(const Ingredient &other)
: name(other.name), quantity(other.quantity), metricUnit(other.metricUnit){
}

Ingredient &Ingredient::operator=(const Ingredient &other) {

    if (this == &other) return *this;

    name = other.name;
    quantity = other.quantity;
    metricUnit = other.metricUnit;

    return *this;
}

Ingredient::~Ingredient() = default;

const MyString &Ingredient::getName() const {
    return name;
}

void Ingredient::printInfo() const {

    name.print();
    std::cout << ", " << quantity << " ";
    metricUnit.print();
    std::cout << std::endl;
}





