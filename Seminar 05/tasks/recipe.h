#pragma once
#include "ingredients.h"
class recipe
{
private:
    int id = 0;
    static int count;
    char *name = nullptr;
    char *description = nullptr;
    Ingredient *ingredients = nullptr;
    int numberOfIngredients = 0;
    void free();
    void copyFrom(const recipe &other);

public:
    recipe();
    ~recipe();
    recipe(const recipe &other);
    recipe &operator=(const recipe &other);
    int getId() const;
    void addIngredient(const Ingredient ingredient);
    void removeIngredient(const int index);
    bool containsIngredient(const char *name);
    void printRecipe() const;
    void set(const char* name, const char* description, Ingredient* ingredients ,int numberOfingredients);
};
