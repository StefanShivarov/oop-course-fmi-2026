#include "Ingredient.h"
#include "Utils.h"
#include <cstring>
#include <iostream>
#include <print>
#pragma warning(disable : 4996)

void Ingredient::free()
{
	delete[] name;
	name = nullptr;
}

void Ingredient::copyFrom(const Ingredient& other)
{
	name = Utils::copyDynamicString(other.name);
	quantity = other.quantity;
	unit = other.unit;
}


Ingredient::Ingredient() : quantity(0), unit(MeasurementUnit::g)
{
	name = new char[1];
	name[0] = '\0';
}

Ingredient::Ingredient(const Ingredient& other)
{
	copyFrom(other);
}

Ingredient& Ingredient::operator=(const Ingredient& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Ingredient::~Ingredient()
{
	free();
}

Ingredient::Ingredient(const char* name, double quantity) : quantity(quantity)
{
	this->name = Utils::copyDynamicString(name);
	this->unit = MeasurementUnit::other;
}

const char* Ingredient::getName() const
{
	return name;
}


const char* Ingredient::toString(const MeasurementUnit unit) const
{
	switch (unit) {
	case MeasurementUnit::g: return " g.";
	case MeasurementUnit::l: return " l";
	case MeasurementUnit::ml: return " ml";
	default:
		return "";
	}
}

void Ingredient::printIngredient() const
{
	std::cout << name << " - " << quantity;
	std::cout << toString(unit);
}


