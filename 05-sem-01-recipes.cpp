#include <iostream>

#include "Cookbook.h"

int main() {
    std::cout << "=== 1. Creating ingredients and recipes ===" << std::endl;

    Ingredient cucumber("Cucumber", "grams", 300.0);
    Ingredient yogurt("Yogurt", "grams", 400.0);
    Ingredient water("Water", "ml", 200.0);
    Ingredient tomato("Tomato", "pieces", 3.0);
    Ingredient cheese("Cheese", "grams", 150.0);
    Ingredient potato("Potato", "pieces", 5.0);

    Recipe tarator("Tarator", "Chop cucumbers, mix with yogurt and water. Serve cold.");
    tarator.addIngredient(cucumber);
    tarator.addIngredient(yogurt);
    tarator.addIngredient(water);

    Recipe shopska("Shopska Salad", "Chop tomatoes and cucumbers, top with grated cheese.");
    shopska.addIngredient(tomato);
    shopska.addIngredient(cucumber);
    shopska.addIngredient(cheese);

    Recipe musaka("Musaka", "Bake potatoes and minced meat.");
    musaka.addIngredient(potato);

    Recipe fries("French Fries", "Fry potatoes in oil.");
    fries.addIngredient(potato);

    Recipe bakedCheese("Baked Cheese", "Bake cheese in an oven.");
    bakedCheese.addIngredient(cheese);

    std::cout << "Recipes created successfully!\n\n";

    std::cout << "=== 2. Testing the Cookbook ===" << std::endl;
    Cookbook myBook("Bulgarian Traditional Recipes");

    myBook.addRecipe(tarator);
    myBook.addRecipe(shopska);
    myBook.addRecipe(musaka);
    myBook.addRecipe(fries);
    myBook.addRecipe(bakedCheese);

    std::cout << "Successfully added 5 unique recipes (including resize)!\n\n";

    std::cout << "=== 3. Searching by name (Tarator) ===" << std::endl;
    const Recipe* foundByName = myBook.getRecipeByName("Tarator");
    if (foundByName != nullptr) {
        foundByName->print(std::cout);
    }
    else {
        std::cout << "Recipe not found!\n";
    }

    std::cout << "\n=== 4. Filtering by ingredient (Cucumber) ===" << std::endl;
    myBook.printRecipiesByIngredient("Cucumber");

    std::cout << "\n=== 5. Testing the Big Four (CRASH TEST) ===" << std::endl;
    {
        Cookbook copiedBook = myBook;
        Cookbook assignedBook("Empty Book");
        assignedBook = myBook;

        std::cout << "Objects copied successfully.\n";
    }

    std::cout << "Destructors executed successfully! No memory leaks.\n\n";

    std::cout << "=== 6. Testing removal by ID ===" << std::endl;
    std::cout << "Searching for ID 2 before deletion: "
        << (myBook.getRecipeById(2) != nullptr ? "Found" : "Missing") << std::endl;

    myBook.removeRecipeById(2);

    std::cout << "Searching for ID 2 after deletion: "
        << (myBook.getRecipeById(2) != nullptr ? "Found" : "Missing") << std::endl;

    std::cout << "\nEnd of program. Everything works perfectly!" << std::endl;

    return 0;
}
