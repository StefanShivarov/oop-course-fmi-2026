#define _CRT_SECURE_NO_WARNINGS
#include "RecipeBook.h"

void RecipeBook::copyFrom(const RecipeBook& other)
{
    count = other.count;
    capacity = other.capacity;
    recipes = new Recipe[capacity];
    for (int i = 0; i < count; i++) {


        recipes[i] = other.recipes[i];
    }
}

void RecipeBook::free()
{
    delete[] recipes;
}
void RecipeBook::resize()
{
    capacity *= 2;
    Recipe* newArr = new Recipe[capacity];
    for (int i = 0; i < count; i++) {


        newArr[i] = recipes[i];
    }
    delete[] recipes;
    recipes = newArr;
}

RecipeBook::RecipeBook()
{
    count = 0;
    capacity = 2;
    recipes = new Recipe[capacity];
}

RecipeBook::RecipeBook(const RecipeBook& other)
{
    copyFrom(other);
}

RecipeBook& RecipeBook::operator=(const RecipeBook& other)
{if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

RecipeBook::~RecipeBook()
{
    free();
}

void RecipeBook::addRecipe(const Recipe& r)
{
    if (count >= capacity) {
        resize();

    }
    recipes[count++] = r;
}

bool RecipeBook::removeRecipe(int id)
{
    for (int i = 0; i < count; i++)
    {
        if (recipes[i].getId() == id)
        {   for (int j = i; j < count - 1; j++) {
                recipes[j] = recipes[j + 1];
            }
            count--;
            return true;
        }
    }
    return false;
}

Recipe* RecipeBook::findById(int id)
{
    for (int i = 0; i < count; i++)
    {
        if (recipes[i].getId() == id) {
            return &recipes[i];
        }
    }
    return nullptr;
}

void RecipeBook::printAll() const
{
    for (int i = 0; i < count; i++) 
    {
        recipes[i].print();
    }
}
void RecipeBook::filterByIngredient(const char* name) const
{
    for (int i = 0; i < count; i++)
    {
        if (recipes[i].hasIngredient(name)) {


            recipes[i].print();
        }
    }
}
