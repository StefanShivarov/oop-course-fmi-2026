//
// Created by Boris Bozhilov on 3/24/2026.
//

#ifndef OOP_COURSE_FMI_2026_RECIPECOLLECTION_H
#define OOP_COURSE_FMI_2026_RECIPECOLLECTION_H
#include "Recipe.h"


class RecipeCollection {

    static constexpr unsigned int RECIPES_BUFFER_COUNT = 5;
    unsigned int bufferSizeMultiplier = 1;

private:

    Recipe *recipes;
    unsigned int countOfRecipes = 0;

public:
    RecipeCollection();

    RecipeCollection(const RecipeCollection &other);
    RecipeCollection& operator=(const RecipeCollection &other) = delete;

    ~RecipeCollection();

    unsigned int getCountOfRecipes() const;

    void addRecipe(const Recipe &recipe);
    bool removeRecipe(const unsigned int id);

    int findRecipe(const unsigned int id) const;
    int findRecipe(const MyString name) const;

    void printRecipes() const;

    RecipeCollection createFilteredRecipesCollection(const MyString &ingredientName) const;
};


#endif //OOP_COURSE_FMI_2026_RECIPECOLLECTION_H