#pragma once

#include <iostream>
#include <cstring>

enum class mernaEdinica
{
    g,
    L,
    ml,
    kg
};

const char *printmernaEdinica(mernaEdinica m);

class Ingredient
{
private:
    char *name = nullptr;
    int amount = 0;
    mernaEdinica unit;
    void copyFrom(const Ingredient &other);
    void free();

public:
    Ingredient();
    ~Ingredient();
    Ingredient(const Ingredient &other);
    Ingredient &operator=(const Ingredient &other);
    void printIngredient();
    char *getName() const;
    void set(const char* newName, int newAmount, mernaEdinica newUnit);
};