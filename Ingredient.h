#pragma once
#include"Unit.h"

class Ingredient
{
private:
	char* name = nullptr;
	double quantity = 0;
	Units unit = Units::OTHER;

	void copyFrom(const Ingredient& other);
	void free();

public:
	Ingredient();

	Ingredient(const char* name, double quantity, Units unit);

	Ingredient(const char* name, double quantity, const char* unit);

	Ingredient(const Ingredient& other);

	Ingredient& operator=(const Ingredient& other);

	~Ingredient();

	void setName(const char* name);

	void setUnit(const char* unit);

	const char* getName() const;

	double getQuantity() const;

	Units getUnit() const;

	void printIngredient() const;
};

bool operator==(const Ingredient& i1, const Ingredient& i2);

