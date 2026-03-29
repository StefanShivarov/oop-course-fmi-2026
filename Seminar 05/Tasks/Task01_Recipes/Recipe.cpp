#include "Recipe.h"
#include <cstring>

unsigned Recipe::totalRecipes = 0;

void Recipe::copyDynamicMemory(const Recipe& other) {
    title = new char[strlen(other.title) + 1];
    strcpy(title, other.title);

    description = new char[strlen(other.description) + 1];
    strcpy(description, other.description);

    ingredients = new Ingredient[other.capacity];
    for (size_t i = 0; i < other.size; i++) {
        ingredients[i] = other.ingredients[i];
    }
}

void Recipe::copyFrom(const Recipe& other) {
    id = other.id;
    size = other.size;
    capacity = other.capacity;
    copyDynamicMemory(other);
}

void Recipe::free() {
    delete[] title;
    delete[] description;
    delete[] ingredients;
}

void Recipe::resize(size_t newCap) {
    capacity = newCap;
    Ingredient* newArr = new Ingredient[capacity];

    for (size_t i = 0; i < size; i++) {
        newArr[i] = ingredients[i];
    }

    delete[] ingredients;
    ingredients = newArr;
}

Recipe::Recipe(): Recipe("", "") {
}

Recipe::Recipe(const char* title, const char* instructions): id(++totalRecipes), size(0), capacity(4) {
    this->title = new char[strlen(title) + 1];
    strcpy(this->title, title);

    this->description = new char[strlen(instructions) + 1];
    strcpy(this->description, instructions);

    ingredients = new Ingredient[capacity];
}

Recipe::Recipe(const Recipe& other) : id(++totalRecipes), size(other.size), capacity(other.capacity) {
    copyDynamicMemory(other);
}

Recipe& Recipe::operator=(const Recipe& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Recipe::~Recipe() {
    free();
}

void Recipe::addIngredient(const Ingredient& ingredient) {
    if (size >= capacity) {
        resize(capacity + 4);
    }
    ingredients[size++] = ingredient;
}

void Recipe::removeIngredient(const char* name) {
    for (size_t i = 0; i < size; i++) {
        if (strcmp(ingredients[i].getName(), name) == 0) {
            for (size_t j = i; j < size - 1; j++) {
                ingredients[j] = ingredients[j + 1];
            }
            size--;
            return;
        }
    }
}

bool Recipe::contains(const char* name) const {
    for (size_t i = 0; i < size; i++) {
        if (strcmp(ingredients[i].getName(), name) == 0) {
            return true;
        }
    }
    return false;
}

unsigned Recipe::getId() const {
    return id;
}

const char* Recipe::getTitle() const {
    return title;
}

const char* Recipe::getDescription() const {
    return description;
}

const Ingredient* Recipe::getIngredients() const {
    return ingredients;
}

size_t Recipe::getSize() const {
    return size;
}

void printRecipe(const Recipe& recipe, std::ostream& os) {
    os << "Id: " << recipe.getId() << std::endl;
    os << "Title: " << recipe.getTitle() << '\n';
    os << "Description: " << recipe.getDescription() << '\n';
    const Ingredient* ingredients = recipe.getIngredients();
    os << "Ingredients: " << '\n';
    for (size_t i = 0; i < recipe.getSize(); i++) {
        printIngredient(ingredients[i], os);
    }
}
