//
// Created by Boris Bozhilov on 3/24/2026.
//
#include <iostream>

#include "RecipeCollection.h"

RecipeCollection::RecipeCollection() : recipes(nullptr) {

    recipes = new Recipe[bufferSizeMultiplier * RECIPES_BUFFER_COUNT];
}

RecipeCollection::RecipeCollection(const RecipeCollection &other) : countOfRecipes(other.countOfRecipes) {

    recipes = new Recipe[other.countOfRecipes];

    for (int i = 0; i < countOfRecipes; i++) {

        recipes[i] = other.recipes[i];
    }
}

RecipeCollection::~RecipeCollection() {

    delete[] recipes;
    recipes = nullptr;
}

void RecipeCollection::addRecipe(const Recipe &recipe) {

    if (countOfRecipes >= bufferSizeMultiplier * RECIPES_BUFFER_COUNT) {

        bufferSizeMultiplier++;

        Recipe *moreRecipes = new Recipe[bufferSizeMultiplier * RECIPES_BUFFER_COUNT];

        for (int i = 0; i < countOfRecipes; i++) {

            moreRecipes[i] = recipes[i];
        }

        delete[] recipes;

        recipes = moreRecipes;

        moreRecipes = nullptr;
    }

    recipes[countOfRecipes] = recipe;

    countOfRecipes++;
}


int RecipeCollection::findRecipe(const unsigned int id) const {

    int recipeIndex = -1;

    for (int i = 0; i < countOfRecipes; i++) {

        if (recipes[i].getID() == id) {
            recipeIndex = i;
            break;
        }
    }

   return recipeIndex;
}

bool RecipeCollection::removeRecipe(const unsigned int id) {

    int recipeIndex = findRecipe(id);

    if (recipeIndex == -1) return false;

    for (int i = recipeIndex + 1; i < countOfRecipes; i++) {

        recipes[i - 1] = recipes[i];
    }

    return true;
}

int RecipeCollection::findRecipe(const MyString name) const {

    int recipeIndex = -1;

    for (int i = 0; i < countOfRecipes; i++) {

        if (recipes[i].getName() == MyString(name)) {
            recipeIndex = i;
            break;
        }
    }

    return recipeIndex;
}

void RecipeCollection::printRecipes() const {

    for (int i = 0; i < countOfRecipes; i++) {

        recipes[i].printInfo();
        std::cout << std::endl;
    }
}

RecipeCollection RecipeCollection::createFilteredRecipesCollection(const MyString &ingredientName) const {

    RecipeCollection filteredRecipes = RecipeCollection();

    for (int i = 0; i < countOfRecipes; i++) {

        if (recipes[i].checkIfIngredientIsInRecipe(ingredientName.getString()))
            filteredRecipes.addRecipe(recipes[i]);
    }

    return filteredRecipes;
}


unsigned int RecipeCollection::getCountOfRecipes() const {
    return countOfRecipes;
}

