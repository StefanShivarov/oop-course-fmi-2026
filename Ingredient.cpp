#define _CRT_SECURE_NO_WARNINGS
#include "Ingredient.h"
#include<cstring>
#include<print>

Ingredient::Ingredient():quantity(0), unit(Units::OTHER)
{
	name = new char[1];
	name[0] = '\0';
}

Ingredient::Ingredient(const char* name, double quantity, Units unit) 
	:quantity(quantity), unit(unit)
{
	setName(name);
}

Ingredient::Ingredient(const char* name, double quantity, const char* unit)
	:quantity(quantity)
{
	setName(name);
	setUnit(unit);
}

void Ingredient::setName(const char* name)
{
	if (name == nullptr)
	{
		return;
	}

	if (this->name != nullptr)
	{
		delete[]this->name;
	}
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Ingredient::setUnit(const char* unit)
{
	if (unit == nullptr)
	{
		return;
	}

	this->unit = Unit::convertToUnit(unit);
}

void Ingredient::copyFrom(const Ingredient& other)
{
	setName(other.name);
	quantity = other.quantity;
	unit = other.unit;
}

void Ingredient::free()
{
	delete[] name;
	name = nullptr;
}

Ingredient::Ingredient(const Ingredient& other)
{
	copyFrom(other);
}

Ingredient& Ingredient::operator=(const Ingredient& other)
{
	if (this == &other)
	{
		return *this;
	}

	free();
	copyFrom(other);

	return *this;
}

bool operator==(const Ingredient& i1, const Ingredient& i2)
{
	return strcmp(i1.getName(), i2.getName()) == 0;
}

Ingredient::~Ingredient()
{
	free();
}

const char* Ingredient::getName() const
{
	return name;
}

double Ingredient::getQuantity() const
{
	return quantity;
}

Units Ingredient::getUnit() const
{
	return unit;
}

void Ingredient::printIngredient()const
{
	std::println("Name: {}, Quantity: {}, Unit: {}", 
		name, quantity, Unit::convertToString(unit));
}