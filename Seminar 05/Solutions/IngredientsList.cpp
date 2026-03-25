//
// Created by Boris Bozhilov on 3/24/2026.
//

#include "IngredientsList.h"

IngredientsList::IngredientsList() : size(0), ingredients(nullptr){

    ingredients = new Ingredient[bufferSizeMultiplier * INGREDIENTS_BUFFER_COUNT];
}

IngredientsList::IngredientsList(const unsigned int size) : size(size), ingredients(nullptr) {

    int bufferSize = size + (INGREDIENTS_BUFFER_COUNT - (size % INGREDIENTS_BUFFER_COUNT));
    bufferSizeMultiplier = bufferSize / INGREDIENTS_BUFFER_COUNT;

    this->ingredients = new Ingredient[bufferSize];
}

IngredientsList::IngredientsList(const unsigned int size, const Ingredient *ingredients)
: size(size), ingredients(nullptr) {

    int bufferSize = size + (size % INGREDIENTS_BUFFER_COUNT);
    bufferSizeMultiplier = bufferSize / INGREDIENTS_BUFFER_COUNT;

    this->ingredients = new Ingredient[bufferSize];

    for (int i = 0; i < size; i++) {

        this->ingredients[i] = ingredients[i];
    }
}

IngredientsList::IngredientsList(const IngredientsList &other) {

    size = other.size;

    ingredients = new Ingredient[size];

    for (int i = 0; i < size; i++) {
        ingredients[i] = other.ingredients[i];
    }
}

IngredientsList &IngredientsList::operator=(const IngredientsList &other) {

    if (this == &other) return *this;

    size = other.size;
    delete[] ingredients;
    ingredients = new Ingredient[size];

    for (int i = 0; i < size; i++) {

        ingredients[i] = other.ingredients[i];
    }

    return *this;
}

IngredientsList::~IngredientsList() {

    size = 0;

    delete[] ingredients;
    ingredients = nullptr;
}

void IngredientsList::addIngredient(const Ingredient &ingredient) {

    if (size >= bufferSizeMultiplier * INGREDIENTS_BUFFER_COUNT) {

        bufferSizeMultiplier++;

        Ingredient* moreIngredients = new Ingredient[bufferSizeMultiplier * INGREDIENTS_BUFFER_COUNT];

        for (int i = 0; i < size; i++) {

            moreIngredients[i] = ingredients[i];
        }

        delete[] ingredients;

        ingredients = moreIngredients;

        // just in case
        moreIngredients = nullptr;
    }

    ingredients[size] = ingredient;
    size++;
}

int IngredientsList::findIngredient(const MyString &name) const{

    for (int i = 0; i < size; i++) {

        if(ingredients[i].getName() == name) return i;
    }

    return -1;
}

bool IngredientsList::removeIngredient(const MyString &name) {

    int ingredientIndex = findIngredient(name);

    if (ingredientIndex == -1) return false;

    for (int i = ingredientIndex + 1; i < size; i++) {
        ingredients[i - 1] = ingredients[i];
    }

    size--;

    // here I'm going to leave the array as it is for now
    // in order to improve the class, the array's buffer size should be reduced if it can fit in a lower threshold
    // this way it's going to take up less space given that a lot of objects have been removed
    // however, given the context of the problem it's probably going to be a rare case and will add unnecessary complexity

    return true;
}

void IngredientsList::printIngredients() const {

    for (int i = 0; i < size; i++) {

        ingredients[i].printInfo();
    }
}



