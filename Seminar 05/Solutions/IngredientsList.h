//
// Created by Boris Bozhilov on 3/24/2026.
//

#ifndef OOP_COURSE_FMI_2026_INGREDIENTSLIST_H
#define OOP_COURSE_FMI_2026_INGREDIENTSLIST_H
#include <complex.h>

#include "Ingredient.h"


class IngredientsList {

    static constexpr unsigned int INGREDIENTS_BUFFER_COUNT = 5;
    unsigned int bufferSizeMultiplier = 1;

private:
    unsigned int size;
    Ingredient* ingredients;

public:

    IngredientsList();
    IngredientsList(unsigned int size);
    IngredientsList(const unsigned int size, const Ingredient *ingredients);

    IngredientsList(const IngredientsList &other);
    IngredientsList& operator=(const IngredientsList &other);

    ~IngredientsList();

    void addIngredient(const Ingredient &ingredient);
    int findIngredient(const MyString &name) const;
    bool removeIngredient(const MyString &name);

    void printIngredients() const;
};


#endif //OOP_COURSE_FMI_2026_INGREDIENTSLIST_H