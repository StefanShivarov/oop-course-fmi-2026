#include "Ingrediant.h"
#include <iostream>
#include <cstring>
#pragma warning(disable: 4996)

const char* Utils::UnitToString(Unit unit)
{
	switch (unit) {
	case MG:return "mg";
	case ML:return "ml";
	case G:return "g";
	case KG:return "kg";
	case L:return "L";
	default: return nullptr;
	}
}

Ingrediant::~Ingrediant()
{
	free();
}

void Ingrediant::setName(const char* name)
{
	if (!name) {
		this->name = new char[1];
		this->name[0] = '\0';
		return;
	}
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Ingrediant::setUnit(Unit unit)
{
	this->unit = unit;
}

const char* Ingrediant::getName() const
{
	return name;
}

Unit Ingrediant::getUnit() const
{
	return unit;
}

unsigned Ingrediant::getQuantity() const
{
	return quantity;
}

void Ingrediant::copyFrom(const Ingrediant& other)
{
	setName(other.name);
	setUnit(other.unit);
	quantity = other.quantity;
}

void Ingrediant::free()
{
	delete[] name;
	name = nullptr;
	quantity = 0;
	unit = Unit::Unknown;
}

Ingrediant::Ingrediant() : quantity(0), unit(Unit::Unknown)
{
}

Ingrediant::Ingrediant(const char* name,unsigned quantity, Unit unit) : quantity(quantity), unit(unit)
{
	setName(name);
}

Ingrediant::Ingrediant(const Ingrediant& other)
{
	copyFrom(other);
}

Ingrediant& Ingrediant::operator=(const Ingrediant& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

void printIngrediant(const Ingrediant& ingrediant, std::ostream& os)
{
	os << "Name: " << ingrediant.getName() << '\n';
	os << "Unit: " << Utils::UnitToString(ingrediant.getUnit()) << '\n';
	os << "Quantity: " << ingrediant.getQuantity() << '\n';
}
