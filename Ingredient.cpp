#define _CRT_SECURE_NO_WARNINGS
#include "Ingredient.h"
#include <iostream>

void Ingredient::copyFrom(const Ingredient& other)
{
    int n = strlen(other.name) + 1;
    name = new char[n];
    strcpy(name, other.name);
    int u = strlen(other.unit) + 1;
    unit = new char[u];
    strcpy(unit, other.unit);
    quantity = other.quantity;
}


void Ingredient::free()
{
    delete[] name;
    delete[] unit;
}

Ingredient::Ingredient()
{
    name = new char[1];
    name[0] = '\0';
    unit = new char[1];
    unit[0] = '\0';
    quantity = 0;
}

Ingredient::Ingredient(const char* name, double quantity, const char* unit)
{
    int n = strlen(name) + 1;
    this->name = new char[n];
    strcpy(this->name, name);
    int u = strlen(unit) + 1;
    this->unit = new char[u];
    strcpy(this->unit, unit);
    this->quantity = quantity;
}

Ingredient::Ingredient(const Ingredient& other)
{
    copyFrom(other);
}

Ingredient& Ingredient::operator=(const Ingredient& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

Ingredient::~Ingredient()
{
    free();
}

const char* Ingredient::getName() const
{
    return name;
}

double Ingredient::getQuantity() const
{
    return quantity;
}

const char* Ingredient::getUnit() const
{
    return unit;
}

void Ingredient::print() const
{
    std::cout<< name << " : " << quantity << " " << unit << std::endl;
}
