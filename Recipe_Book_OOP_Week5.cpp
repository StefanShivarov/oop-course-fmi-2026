#include <iostream>
#include<print>
#include"RecipeBook.h"

int main()
{
    RecipeBook book;

    Ingredient i1("Flour", 500, "gr");
    Ingredient i2("Milk", 200, "ml");
    Ingredient i3("Eggs", 3, "other");
    Ingredient i4("Sugar", 100, "gr");

    Recipe r1;
    r1.setName("Pancakes");
    r1.setDescription("Mix ingredients and fry.");

    r1.addIngredient(i1);
    r1.addIngredient(i2);
    r1.addIngredient(i3);

    book.addRecipe(r1);

    Recipe r2;
    r2.setName("Cake");
    r2.setDescription("Bake everything.");

    r2.addIngredient(i1);
    r2.addIngredient(i4);

    book.addRecipe(r2);

    std::println("\nAll Recipes:");
    book.printRecipeBook();

    std::println("\nSearch recipe by Name:");
    Recipe& found = book.getRecipeByName("Pancakes");
    found.printRecipe();

    Ingredient butter("Butter", 50, "gr");
    book.addIngredient(butter, found.getId());

    std::println("\nAfter adding butter:");
    found.printRecipe();

    book.removeIngredient(i2, found.getId());

    std::println("\nAfter removing milk:");
    found.printRecipe();

    std::println("\nRecipes with flour:");
    book.filterRecipesByIngredient("Flour");

    book.removeRecipe(found.getId());

    std::println("\nAfter removing pancakes:");
    book.printRecipeBook();

    return 0;
}
