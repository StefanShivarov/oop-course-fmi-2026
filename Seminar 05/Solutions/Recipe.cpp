//
// Created by Boris Bozhilov on 3/23/2026.
//

#include "Recipe.h"
#include <iostream>

#include "RecipeCollection.h"

unsigned int Recipe::countOfRecipes = 0;

Recipe::Recipe() : id(++countOfRecipes), name(MyString()), description(MyString()), ingredients(IngredientsList()){
}

Recipe::Recipe(const MyString &name, const MyString &description)
    : id(++countOfRecipes), name(name), description(description), ingredients(IngredientsList()){
}

Recipe::Recipe(const Recipe &other)
    : id(++countOfRecipes), name(other.name), description(other.description), ingredients(other.ingredients){
}

Recipe &Recipe::operator=(const Recipe &other) {

    if (this == &other) return *this;

    id = other.id;
    name = other.name;
    description = other.description;
    ingredients = other.ingredients;

    return *this;
}

Recipe::~Recipe() = default;

void Recipe::addIngredientToRecipe(const Ingredient &ingredient) {

    ingredients.addIngredient(ingredient);
}

bool Recipe::removeIngredientFromRecipe(const Ingredient &ingredient) {

    return ingredients.removeIngredient(ingredient.getName());
}

bool Recipe::checkIfIngredientIsInRecipe(const char *name) const {

    MyString ingredientName = MyString(name);

    return ingredients.findIngredient(ingredientName) != -1;
}

void Recipe::printInfo() const {

    std::cout << id << ". " << name.getString() << std::endl;
    std::cout << description.getString() << std::endl;
    std::cout << "Ingredients: " << std::endl;
    ingredients.printIngredients();
}

unsigned int Recipe::getID() const {
    return id;
}

const MyString &Recipe::getName() const {
    return name;
}






