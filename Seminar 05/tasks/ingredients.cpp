#include "ingredients.h"
#include <cstring>
#include <iostream>
Ingredient::Ingredient()
{
}

Ingredient::~Ingredient()
{
    free();
}
void Ingredient::free()
{
    delete[] name;
    name = nullptr;
}
void Ingredient::copyFrom(const Ingredient &other)
{
    if (other.name != nullptr)
    {
        name = new char[std::strlen(other.name) + 1];
        std::strcpy(name, other.name);
    }
    else
    {
        name = nullptr;
    }
    amount = other.amount;
    unit = other.unit;
}
Ingredient &Ingredient::operator=(const Ingredient &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}
Ingredient::Ingredient(const Ingredient &other)
{
    copyFrom(other);
}

void Ingredient::printIngredient()
{
    if (name != nullptr)
    {
        std::cout << "\nName: " << name;
    }
    else
    {
        std::cout << "\nMissing name";
    }
    std::cout << "\nAmount: " << amount;
    std::cout << printmernaEdinica(unit);
}

const char *printmernaEdinica(mernaEdinica m)
{
    switch (m)
    {
    case mernaEdinica::g:
        return "grams";
    case mernaEdinica::L:
        return "Liters";
    case mernaEdinica::ml:
        return "mililiters";
    case mernaEdinica::kg:
        return "kilograms";
    }
    return "other";
}

char *Ingredient::getName() const
{
    return name;
}

void Ingredient::set(const char *newName, int newAmount, mernaEdinica newUnit)
{
    free();
    if (newName != nullptr)
    {
        name = new char[std::strlen(newName) + 1];
        std::strcpy(name, newName);
    }
    else
    {
        name = nullptr;
    }
    amount = newAmount;
    unit = newUnit;
}