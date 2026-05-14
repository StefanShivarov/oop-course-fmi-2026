#include <iostream>
#include <cstring>
#include "recipe.h"
int recipe::count = 0;
recipe::recipe()
{
    id = ++count;
};
int recipe::getId() const
{
    return id;
}
recipe::recipe(const recipe &other)
{
    id = ++count;
    copyFrom(other);
};

void copy(char *&first, const char *other)
{
    if (other != nullptr)
    {
        first = new char[std::strlen(other) + 1];
        std::strcpy(first, other);
    }
    else
    {
        first = nullptr;
    }
}
void copy(Ingredient *&first, const Ingredient *other, const int otherNumberOfIngredients)
{
    first = new Ingredient[otherNumberOfIngredients];
    for (int i = 0; i < otherNumberOfIngredients; i++)
    {
        first[i] = other[i];
    }
}

void recipe::copyFrom(const recipe &other)
{
    copy(name, other.name);
    copy(description, other.description);
    numberOfIngredients = other.numberOfIngredients;
    copy(ingredients, other.ingredients, other.numberOfIngredients);
}
void recipe::free()
{
    delete[] ingredients;
    delete[] name;
    delete[] description;

    ingredients = nullptr;
    name = nullptr;
    description = nullptr;
    numberOfIngredients = 0;
}
recipe::~recipe()
{
    free();
};

recipe &recipe::operator=(const recipe &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

void recipe::addIngredient(const Ingredient ingredient)
{
    Ingredient *temp = new Ingredient[numberOfIngredients + 1];
    for (int i = 0; i < numberOfIngredients; i++)
    {
        temp[i] = ingredients[i];
    }
    temp[numberOfIngredients] = ingredient;
    numberOfIngredients++;
    delete[] ingredients;
    ingredients = temp;
}
void recipe::removeIngredient(const int index)
{
    if (index >= numberOfIngredients)
    {
        return;
    }
    Ingredient *temp = new Ingredient[numberOfIngredients - 1];
    for (int i = 0; i < index; i++)
    {
        temp[i] = ingredients[i];
    }
    for (int i = index + 1; i < numberOfIngredients; i++)
    {
        temp[i - 1] = ingredients[i];
    }
    numberOfIngredients--;
    delete[] ingredients;
    ingredients = temp;
}

bool recipe::containsIngredient(const char *name)
{
    if (name == nullptr)
    {
        return false;
    }
    for (int i = 0; i < numberOfIngredients; i++)
    {
        if (ingredients[i].getName() != nullptr && !(std::strcmp(name, ingredients[i].getName())))
            return true;
    }
    return false;
}

void recipe::printRecipe() const
{
    if (name != nullptr)
    {
        std::cout << "\nName: " << name;
    }
    else
    {
        std::cout << "\nMissing name";
    }
    if (description != nullptr)
    {
        std::cout << "\nDescription: " << description;
    }
    else
    {
        std::cout << "\nMissing description";
    }

    std::cout << "\nIngredients: ";
    for (int i = 0; i < numberOfIngredients; i++)
    {
        ingredients[i].printIngredient();
    }
}

void recipe::set(const char *name, const char *description, Ingredient *ingredients, int numberOfingredients)
{
    free();
    copy(this->name,name);
    copy(this->description,description);

    for (int i = 0; i < numberOfIngredients; i++)
    {
        this->addIngredient(ingredients[i]);
    }
}