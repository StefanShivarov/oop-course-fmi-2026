#pragma once
class Ingredient
{
private:
    char* name;
    double quantity;
    char* unit;


public:
    Ingredient();
    Ingredient(const char* name, double quantity, const char* unit);
    Ingredient(const Ingredient& other);
    Ingredient& operator=(const Ingredient& other);
    ~Ingredient();
    void copyFrom(const Ingredient& other);
    void free();
    const char* getName() const;
    double getQuantity() const;
    const char* getUnit() const;
    void print() const;
};

