#include <iostream>
#include <cstring>

#include "Ingredient.h"

#pragma warning(disable:4996)

void Ingredient::copyDynamicMemoryFrom(const Ingredient& other) {
    name = new char[std::strlen(other.name) + 1];
    std::strcpy(name, other.name);
    unit = new char[std::strlen(other.unit) + 1];
    std::strcpy(unit, other.unit);
}

void Ingredient::freeDynamicMemory() {
    delete[] name;
	delete[] unit;
}

Ingredient::Ingredient() : name(nullptr), unit(nullptr), quantity(0) {}

Ingredient::Ingredient(const char* name, const char* unit, double quantity) {
    this->name = new char[std::strlen(name) + 1];
    std::strcpy(this->name, name);
    this->unit = new char[std::strlen(unit) + 1];
    std::strcpy(this->unit, unit);
	this->quantity = quantity;
}

Ingredient::Ingredient(const Ingredient& other) : quantity(other.quantity) {
    copyDynamicMemoryFrom(other);
}

Ingredient& Ingredient::operator=(const Ingredient& other) {
    if (this != &other) {
        freeDynamicMemory();
        copyDynamicMemoryFrom(other);
        quantity = other.quantity;
    }

	return *this;
}

Ingredient::~Ingredient() {
	freeDynamicMemory();
}

const char* Ingredient::getName() const {
    return name;
}

double Ingredient::getQuantity() const {
    return quantity;
}

const char* Ingredient::getUnit() const {
    return unit;
}

void Ingredient::print(std::ostream& os) const {
    os << name << ": " << quantity << unit;
}
