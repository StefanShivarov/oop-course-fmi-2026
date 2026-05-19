#pragma once
#include "Ingredient.h"
class Recipe
{
private:
    int id;
    char* name;
    char* description;
    Ingredient* ingredients;
    int count;
    int capacity;
    static int nextId;


public:
    Recipe();
    Recipe(const char* name, const char* description);
    Recipe(const Recipe& other);
    Recipe& operator=(const Recipe& other);
    ~Recipe();
    void copyFrom(const Recipe& other);
    void free();
    void resize();
    int getId() const;
    const char* getName() const;
    void addIngredient(const Ingredient& ing);
    bool removeIngredient(const char* name);
    bool hasIngredient(const char* name) const;

    void print() const;
};

