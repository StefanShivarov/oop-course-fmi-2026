#include "Ingredient.h"
#include <cstring>
#include <iostream>
#include "Recipe.h"
#pragma warning(disable: 4996)
void Ingredient::copyIngredient(const Ingredient& other) 
{
	
	setName(other.name);
	quantity = other.quantity;
	unit = other.unit;
}
void Ingredient::freeIngredient()
{
	delete[] name;
	name = nullptr;
	quantity = 0;
}
Ingredient::Ingredient() : Ingredient(nullptr, 0, unit)
{
	name = new char[1];
	name[0] = '\0';
	
}

Ingredient::Ingredient(const Ingredient& other)
{
		copyIngredient(other);
}

Ingredient& Ingredient::operator=(const Ingredient& other)
{
	if (this != &other)
	{
		freeIngredient();
		copyIngredient(other);
	}
	return *this;
	// TODO: insert return statement here
}

Ingredient::Ingredient(const char* name, double quantity, Unit unit) : quantity(quantity), unit(unit)
{
	setName(name);
}

Ingredient::~Ingredient() 
{
	freeIngredient();
}

const char* Ingredient::getName() const
{
	return name;
}

void Ingredient::setName(const char* name) 
{
	if (name == nullptr)
	{
		return;
	}
	delete[] this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

const double Ingredient::getQuantity() const
{
	return quantity;
}

const Unit Ingredient::getUnit() const
{
	return unit;
}
