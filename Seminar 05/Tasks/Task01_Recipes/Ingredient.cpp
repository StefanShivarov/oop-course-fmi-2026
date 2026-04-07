#include "Ingredient.h"
#include <cstring>

const char* Utils::convertUnitToString(Unit u) {
    switch (u) {
        case G: return "g";
        case MG: return "mg";
        case L: return "l";
        case ML: return "ml";
        case DROPS: return "drops";
        case PIECES: return "pieces";
        default: return "";
    }
}

void Ingredient::copyDynamicMemory(const Ingredient& other) {
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
}

void Ingredient::copyFrom(const Ingredient& other) {
    copyDynamicMemory(other);
    quantity = other.quantity;
    unit = other.unit;
}

void Ingredient::free() {
    delete[] name;
    name = nullptr;
}

Ingredient::Ingredient() : quantity(0), unit(Unit::G) {}

Ingredient::Ingredient(const char* name, unsigned quantity, Unit unit) : quantity(quantity), unit(unit) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

Ingredient::Ingredient(const Ingredient& other) : quantity(other.quantity), unit(other.unit) {
    copyDynamicMemory(other);
}

Ingredient& Ingredient::operator=(const Ingredient& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Ingredient::~Ingredient() {
    free();
}

const char* Ingredient::getName() const {
    return name;
}

unsigned Ingredient::getQuantity() const {
    return quantity;
}

Unit Ingredient::getUnit() const {
    return unit;
}

void printIngredient(const Ingredient& ingredient, std::ostream& os) {
    os << ingredient.getName();
    os << " " << ingredient.getQuantity() << " " << Utils::convertUnitToString(ingredient.getUnit()) << '\n';
}
