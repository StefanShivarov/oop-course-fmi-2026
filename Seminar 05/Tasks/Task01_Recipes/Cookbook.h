#pragma once
#include "Recipe.h"

class Cookbook {
private:
    char* name = nullptr;
    Recipe* recipes = nullptr;
    size_t size;
    size_t capacity;

    void copyDynamicMemory(const Cookbook& other);
    void copyFrom(const Cookbook& other);
    void free();
    void resize();

public:
    Cookbook(const char* name);
    Cookbook(const Cookbook& other);
    Cookbook& operator=(const Cookbook& other);
    ~Cookbook();

    const char* getName() const;

    const Recipe* getRecipes() const;
    size_t getRecipesCount() const;

    void addRecipe(const Recipe& recipe);
    void removeRecipe(const char* title);
    bool containsRecipe(const char* title) const;
};

void printCookbook(const Cookbook& cookbook, std::ostream& os = std::cout);
void filterRecipes(const Cookbook& cookbook, bool (*shouldFilter) (const Recipe&), std::ostream& os = std::cout);
