#pragma once
#include "Recipe.h"
class RecipeBook
{
private:
    Recipe* recipes;
    int count;
    int capacity;

public:
    RecipeBook();
    RecipeBook(const RecipeBook& other);
    RecipeBook& operator=(const RecipeBook& other);
    ~RecipeBook();
    void copyFrom(const RecipeBook& other);
    void free();
    void resize();
    void addRecipe(const Recipe& r);
    bool removeRecipe(int id);
    Recipe* findById(int id);
    void printAll() const;
    void filterByIngredient(const char* name) const;
};

