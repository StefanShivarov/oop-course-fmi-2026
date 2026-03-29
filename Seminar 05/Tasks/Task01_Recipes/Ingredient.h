#pragma once
#include <iosfwd>
#include <iostream>

enum class Unit {
    MG, G, L, ML, DROPS, PIECES
};

namespace Utils {
    using enum Unit;
    const char* convertUnitToString(Unit u);
}

class Ingredient {

private:
    char* name = nullptr;
    unsigned quantity;


    Unit unit;
    void copyDynamicMemory(const Ingredient& other);
    void copyFrom(const Ingredient& other);
    void free();

public:
    Ingredient();
    Ingredient(const char* name, unsigned quantity, Unit unit);
    Ingredient(const Ingredient& other);
    Ingredient& operator=(const Ingredient& other);
    ~Ingredient();

    const char* getName() const;
    unsigned getQuantity() const;
    Unit getUnit() const;
};



void printIngredient(const Ingredient& ingredient, std::ostream& os = std::cout);
