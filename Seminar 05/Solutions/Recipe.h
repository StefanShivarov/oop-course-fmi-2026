//
// Created by Boris Bozhilov on 3/23/2026.
//

#ifndef OOP_COURSE_FMI_2026_RECIPE_H
#define OOP_COURSE_FMI_2026_RECIPE_H
#include "Ingredient.h"
#include "IngredientsList.h"


class Recipe {

    static unsigned int countOfRecipes;

private:
    unsigned int id;
    MyString name;
    MyString description;
    IngredientsList ingredients;


public:
    Recipe();
    Recipe(const MyString &name, const MyString &description);

    Recipe(const Recipe &other);
    Recipe& operator=(const Recipe &other);

    ~Recipe();

    void addIngredientToRecipe(const Ingredient &ingredient);

    bool removeIngredientFromRecipe(const Ingredient &ingredient);

    bool checkIfIngredientIsInRecipe(const char* name) const;

    void printInfo() const;

    unsigned int getID() const;

    const MyString& getName() const;
};


#endif //OOP_COURSE_FMI_2026_RECIPE_H