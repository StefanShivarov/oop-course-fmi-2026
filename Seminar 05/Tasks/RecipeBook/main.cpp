// Recipe Book.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "RecipeBook.h"

int main()
{
    Ingredient salt("Salt", 5.0, Unit::grams);
    Ingredient eggs("Eggs", 3.0, Unit::pieces);
    Ingredient flour("Flour", 200.0, Unit::grams);
    Ingredient milk("Milk", 0.5, Unit::litres);

    Recipe scrambledEggs;
    scrambledEggs.setName("Scrambled Eggs");
    scrambledEggs.setDescription("Whisk eggs and fry them in a pan with salt.");
    scrambledEggs.addIngredient(eggs);
    scrambledEggs.addIngredient(salt);

    Recipe pancakes;
    pancakes.setName("Pancakes");
    pancakes.setDescription("Mix flour, milk, and eggs. Fry in a pan.");
    pancakes.addIngredient(flour);
    pancakes.addIngredient(milk);
    pancakes.addIngredient(eggs);

    RecipeBook myCookBook;

    std::cout << "--- Adding recipes to the book ---" << std::endl;
    myCookBook.addRecipe(scrambledEggs);
    myCookBook.addRecipe(pancakes);

    myCookBook.printEveryRecipe();

    std::cout << "\n--- Searching for recipes with 'Milk' ---" << std::endl;
    if (myCookBook.searchRecipe("Milk")) {
        std::cout << "Found a recipe containing Milk!" << std::endl;
    }
    else {
        std::cout << "No recipe with Milk found." << std::endl;
    }

    int idToRemove = 1; 
    std::cout << "\n--- Removing recipe with ID " << idToRemove << " ---" << std::endl;
    myCookBook.removeRecipe(idToRemove);

    std::cout << "\n--- Updated Recipe Book ---" << std::endl;
    myCookBook.printEveryRecipe();

	
}
