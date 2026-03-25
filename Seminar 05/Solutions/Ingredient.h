//
// Created by Boris Bozhilov on 3/23/2026.
//

#ifndef OOP_COURSE_FMI_2026_INGREDIENT_H
#define OOP_COURSE_FMI_2026_INGREDIENT_H
#include "MyString.h"


class Ingredient {

private:
    MyString name;
    unsigned int quantity;
    MyString metricUnit;

public:
    Ingredient();
    Ingredient(const MyString &name, const unsigned int quantity, const MyString &metricUnit);

    Ingredient(const Ingredient &other);
    Ingredient& operator=(const Ingredient &other);

    ~Ingredient();

    const MyString& getName() const;

    void printInfo() const;
};


#endif //OOP_COURSE_FMI_2026_INGREDIENT_H