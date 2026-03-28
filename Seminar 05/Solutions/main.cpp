#include <iostream>

#include "IngredientsList.h"
#include "MyString.h"
#include "Recipe.h"
#include "RecipeCollection.h"

int main(){

    MyString a = MyString("Hello");
    MyString b = MyString("He1llo");

    IngredientsList list = IngredientsList();

    list.addIngredient(Ingredient("egg", 3, "count"));
    list.addIngredient(Ingredient("milk", 500, "milliliters"));
    list.addIngredient(Ingredient("flour", 250, "grams"));
    list.addIngredient(Ingredient("sugar", 300, "grams"));

    std::cout << "Sample ingredients: " << std::endl;
    list.printIngredients();
    std::cout << std::endl;

    Recipe recipe1 = Recipe("Cake1", "a simple sweet delight");

    recipe1.addIngredientToRecipe(Ingredient("egg", 3, "count"));
    recipe1.addIngredientToRecipe(Ingredient("milk", 500, "milliliters"));
    recipe1.addIngredientToRecipe(Ingredient("flour", 250, "grams"));
    recipe1.addIngredientToRecipe(Ingredient("sugar", 300, "grams"));

    Recipe recipe2 = Recipe("Cake2", "a simple sweet delight");

    recipe2.addIngredientToRecipe(Ingredient("egg", 3, "count"));
    recipe2.addIngredientToRecipe(Ingredient("milk", 500, "milliliters"));
    recipe2.addIngredientToRecipe(Ingredient("flour", 250, "grams"));
    recipe2.addIngredientToRecipe(Ingredient("sugar", 300, "grams"));

    Recipe recipe3 = Recipe("Cake3", "a simple sweet delight");

    recipe3.addIngredientToRecipe(Ingredient("egg", 3, "count"));
    recipe3.addIngredientToRecipe(Ingredient("milk", 500, "milliliters"));
    recipe3.addIngredientToRecipe(Ingredient("flour", 250, "grams"));
    recipe3.addIngredientToRecipe(Ingredient("sugar", 300, "grams"));

    Recipe recipe4 = Recipe("Cake4", "a simple sweet delight");

    recipe4.addIngredientToRecipe(Ingredient("egg", 3, "count"));
    recipe4.addIngredientToRecipe(Ingredient("milk", 500, "milliliters"));
    recipe4.addIngredientToRecipe(Ingredient("flour", 250, "grams"));
    recipe4.addIngredientToRecipe(Ingredient("sugar", 300, "grams"));
    recipe4.addIngredientToRecipe(Ingredient("LOVE <3", 0, "unconditional"));

    RecipeCollection collection = RecipeCollection();

    collection.addRecipe(recipe1);
    collection.addRecipe(recipe2);
    collection.addRecipe(recipe3);
    collection.addRecipe(recipe4);

    std::cout << "Printing original collection: " << std::endl;
    collection.printRecipes();
    std::cout << std::endl;

    RecipeCollection filtered = collection.createFilteredRecipesCollection("LOVE <3");

    std::cout << "Printing filtered collection: " << std::endl;
    filtered.printRecipes();
    std::cout << std::endl;

    return 0;
}
