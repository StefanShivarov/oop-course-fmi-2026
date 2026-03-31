#pragma once
#include "Ingredient.h"
#include <iostream>

class Recipe {
private:
    static unsigned totalRecipes;
    unsigned id;
    char* title = nullptr;
    char* description = nullptr;
    Ingredient* ingredients = nullptr;
    size_t size;
    size_t capacity;

    void copyDynamicMemory(const Recipe& other);
    void copyFrom(const Recipe& other);
    void free();
    void resize(size_t newCap);

public:
    Recipe();
    Recipe(const char* title, const char* instructions);
    Recipe(const Recipe& other);
    Recipe& operator=(const Recipe& other);
    ~Recipe();

    void addIngredient(const Ingredient& ingredient);
    void removeIngredient(const char* name);
    bool contains(const char* name) const;

    unsigned getId() const;
    const char* getTitle() const;
    const char* getDescription() const;
    const Ingredient* getIngredients() const;
    size_t getSize() const;
};

void printRecipe(const Recipe& recipe, std::ostream& os = std::cout);
