#include "Cookbook.h"
#include <cstring>

void Cookbook::copyDynamicMemory(const Cookbook& other) {
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);

    recipes = new Recipe[other.capacity];
    for (size_t i = 0; i < other.size; i++) {
        recipes[i] = other.recipes[i];
    }
}

void Cookbook::copyFrom(const Cookbook& other) {
    size = other.size;
    capacity = other.capacity;
    copyDynamicMemory(other);
}

void Cookbook::free() {
    delete[] name;
    delete[] recipes;
}

void Cookbook::resize() {
    capacity *= 2;
    Recipe* newArr = new Recipe[capacity];

    for (size_t i = 0; i < size; i++) {
        newArr[i] = recipes[i];
    }

    delete[] recipes;
    recipes = newArr;
}

Cookbook::Cookbook(const char* name) : size(0), capacity(4) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);

    recipes = new Recipe[capacity];
}

Cookbook::Cookbook(const Cookbook& other) : size(other.size), capacity(other.capacity) {
    copyDynamicMemory(other);
}

Cookbook& Cookbook::operator=(const Cookbook& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Cookbook::~Cookbook() {
    free();
}

const char* Cookbook::getName() const {
    return name;
}

const Recipe* Cookbook::getRecipes() const {
    return recipes;
}

size_t Cookbook::getRecipesCount() const {
    return size;
}

void Cookbook::addRecipe(const Recipe& recipe) {
    if (size >= capacity) {
        resize();
    }
    if (containsRecipe(recipe.getTitle())) {
        return;
    }
    recipes[size++] = recipe;
}

void Cookbook::removeRecipe(const char* title) {
    for (size_t i = 0; i < size; i++) {
        if (strcmp(recipes[i].getTitle(), title) == 0) {
            for (size_t j = i; j < size - 1; j++) {
                recipes[j] = recipes[j + 1];
            }
            size--;
            return;
        }
    }
}

bool Cookbook::containsRecipe(const char* title) const {
    for (size_t i = 0; i < size; i++) {
        if (strcmp(recipes[i].getTitle(), title) == 0) {
            return true;
        }
    }
    return false;
}

void printCookbook(const Cookbook& cookbook, std::ostream& os) {
    os << "Cookbook " << cookbook.getName() << '\n';
    const Recipe* recipesArr = cookbook.getRecipes();
    for (size_t i = 0; i < cookbook.getRecipesCount(); i++) {
        printRecipe(recipesArr[i], os);
    }
}

void filterRecipes(const Cookbook& cookbook, bool (*shouldFilter)(const Recipe&), std::ostream& os) {
    const Recipe* recipesArr = cookbook.getRecipes();
    for (size_t i = 0; i < cookbook.getRecipesCount(); i++) {
        if (shouldFilter(recipesArr[i])) {
            printRecipe(recipesArr[i], os);
        }
    }
}
