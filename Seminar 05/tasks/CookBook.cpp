#include "ingredients.h"
#include "recipe.h"
#include "CookBook.h"

CookBook::CookBook()
{
}

void CookBook::copyFrom(const CookBook &other)
{
    numberOfrecipes = other.numberOfrecipes;
    recipes = new recipe[numberOfrecipes];
    for (int i = 0; i < numberOfrecipes; i++)
    {
        recipes[i] = other.recipes[i];
    }
}
void CookBook::free()
{
    delete[] recipes;
    recipes = nullptr;
}
CookBook::CookBook(const CookBook &other)
{
    copyFrom(other);
}

CookBook &CookBook::operator=(const CookBook &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

void CookBook::addNewRecipe(const recipe &newRecipe)
{
    recipe *temp = new recipe[numberOfrecipes + 1];
    for (int i = 0; i < numberOfrecipes; i++)
    {
        temp[i] = recipes[i];
    }
    temp[numberOfrecipes] = newRecipe;
    delete[] recipes;
    recipes = temp;
    numberOfrecipes++;
}
CookBook::~CookBook()
{
    free();
}

void CookBook::removeRecipe(const int id)
{
    int index = searchRecipeById(id);
    if (index == -1)
    {
        return;
    }
    recipe *temp = new recipe[numberOfrecipes - 1];
    for (int i = 0; i < index; i++)
    {
        temp[i] = recipes[i];
    }
    for (int i = index + 1; i < numberOfrecipes; i++)
    {
        temp[i - 1] = recipes[i];
    }
    numberOfrecipes--;
    delete[] recipes;
    recipes = temp;
}

int CookBook::searchRecipeById(const int id)
{
    int index = -1;
    for (int i = 0; i < numberOfrecipes; i++)
    {
        if (recipes[i].getId() == id)
        {
            index = i;
        }
    }
    return index;
}

void CookBook::printAllRecipes() const
{
    for (int i = 0; i < numberOfrecipes; i++)
    {
        std::cout << "\nRecipe " << i << ": ";
        recipes[i].printRecipe();
    }
}

CookBook *CookBook::filterRecipesByIngredient(const Ingredient &ingredient) const
{
    CookBook *result = new CookBook();
    for (int i = 0; i < numberOfrecipes; i++)
    {
        if (recipes[i].containsIngredient(ingredient.getName()))
        {
            result->addNewRecipe(recipes[i]);
        }
    }
    return result;
}