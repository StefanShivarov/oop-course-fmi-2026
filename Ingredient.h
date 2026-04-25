#pragma once
#include <cstring>
#include <fstream>
#include <iostream>
#pragma warning (disable: 4996)

class Ingredient {
private:
    char* name;
    char* unit;
    double quantity;

    void copyDynamicMemoryFrom(const Ingredient& other);
    void freeDynamicMemory();

public:
    Ingredient();
    Ingredient(const char* name, const char* unit, double quantity);
    Ingredient(const Ingredient& other);
	Ingredient& operator=(const Ingredient& other);
	~Ingredient();

    const char* getName() const;
    double getQuantity() const;
    const char* getUnit() const;
    void print(std::
        ostream& os = std::cout) const;
};

