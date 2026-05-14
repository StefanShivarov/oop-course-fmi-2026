#pragma once
#include "ingredients.h"
#include "recipe.h"

class CookBook
{
private:
    recipe *recipes = nullptr;
    int numberOfrecipes = 0;
    void copyFrom(const CookBook &other);
    void free();

public:
    CookBook();
    ~CookBook();
    void removeRecipe(const int id);
    CookBook(const CookBook &other);
    CookBook &operator=(const CookBook &other);
    void addNewRecipe(const recipe &newRecipe);
    int searchRecipeById(const int id);
    void printAllRecipes() const;
    CookBook *filterRecipesByIngredient(const Ingredient &ingredient) const;
};