#include <iostream>
#include "Cookbook.h"
#include "Recipe.h"
#include "Ingrediant.h"
#pragma warning(disable: 4996)

bool hasSugar(const Recipe& r) {
    return r.contains("Sugar");
}

int main() {
    using enum Unit;
    Recipe pancakes("Pancakes", "Mix and fry");
    pancakes.addIngrediant(Ingrediant("Flour", 200, G));
    pancakes.addIngrediant(Ingrediant("Milk", 300, ML));
    pancakes.addIngrediant(Ingrediant("Sugar", 20, G));

    Recipe omelette("Omelette", "Beat eggs and cook");
    omelette.addIngrediant(Ingrediant("Eggs", 3, G));
    omelette.addIngrediant(Ingrediant("Cheese", 1, G));

    Recipe tunaWithPasta("Tuna fish with pasta", "");
    tunaWithPasta.addIngrediant(Ingrediant("Tuna fish", 100, G));
    tunaWithPasta.addIngrediant(Ingrediant("Pasta", 200, G));
    tunaWithPasta.addIngrediant(Ingrediant("Mozzarella", 50, G));

    Cookbook book("My Cookbook");

    book.addRecipe(pancakes);
    book.addRecipe(omelette);
    book.addRecipe(tunaWithPasta);

    std::cout << "=== All recipes ===\n";
    printCookbook(book);

    std::cout << "\nContains Pancakes: "
        << (book.containsRecipe("Pancakes") ? "Yes" : "No") << "\n";

    book.removeRecipe("Omelette");

    std::cout << "\n=== After removing Omelette ===\n";
    printCookbook(book);

    std::cout << "\n=== Recipes containing sugar ===\n";
    filterRecipes(book, hasSugar);

    Cookbook copy = book;

    std::cout << "\n=== Copy of cookbook ===\n";
    printCookbook(copy);
}