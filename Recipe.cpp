#define _CRT_SECURE_NO_WARNINGS
#include "Recipe.h"
#include <iostream>

int Recipe::nextId = 1;

void Recipe::copyFrom(const Recipe& other)
{
    id = other.id;
    int n = strlen(other.name) + 1;
    name = new char[n];
    strcpy(name, other.name);
    int d = strlen(other.description) + 1;
    description = new char[d];
    strcpy(description, other.description);
    count = other.count;
    capacity = other.capacity;
    ingredients = new Ingredient[capacity];
    for (int i = 0; i < count; i++)
    {
        ingredients[i] = other.ingredients[i];
    }
}

void Recipe::free()
{
    delete[] name;
    delete[] description;
    delete[] ingredients;
}

void Recipe::resize()
{
    capacity *= 2;
    Ingredient* newArr = new Ingredient[capacity];
    for (int i = 0; i < count; i++) 
    {
        newArr[i] = ingredients[i];
    }
    delete[] ingredients;
    ingredients = newArr;
}

Recipe::Recipe()
{
    id = nextId++;
    name = new char[1];
    name[0] = '\0';
    description = new char[1];
    description[0] = '\0';
    count = 0;
    capacity = 2;
    ingredients = new Ingredient[capacity];
}

Recipe::Recipe(const char* name, const char* description)
{
    id = nextId++;
    int n = strlen(name) + 1;
    this->name = new char[n];
    strcpy(this->name, name);
    int d = strlen(description) + 1;
    this->description = new char[d];
    strcpy(this->description, description);
    count = 0;
    capacity = 2;
    ingredients = new Ingredient[capacity];
}

Recipe::Recipe(const Recipe& other)
{
    copyFrom(other);
}

Recipe& Recipe::operator=(const Recipe& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

Recipe::~Recipe()
{
    free();
}

int Recipe::getId() const
{
    return id;
}

const char* Recipe::getName() const
{
    return name;
}

void Recipe::addIngredient(const Ingredient& i)
{
    if (count >= capacity)
        resize();
    ingredients[count++] = i;
}

bool Recipe::removeIngredient(const char* name)
{
    for (int i = 0; i < count; i++)
    {
      if (strcmp(ingredients[i].getName(), name) == 0)
        {
            for (int j = i; j < count - 1; j++) 
            {
                ingredients[j] = ingredients[j + 1];
            }
            count--;
            return true;
        }
    }
    return false;
}

bool Recipe::hasIngredient(const char* name) const
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(ingredients[i].getName(), name) == 0) 
        {
            return true;
        }
    }
    return false;
}

void Recipe::print() const
{
    std::cout << "ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Description: " << description << std::endl;
    for (int i = 0; i < count; i++) 
    {


        ingredients[i].print();
    }

    std::cout << std::endl;
}
