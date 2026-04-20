#pragma once
#include <iostream>
#include <cstring>
#pragma warning(disable: 4996)

enum class Unit {
	G,MG,KG,ML,L,Unknown
};

namespace Utils {
	using enum Unit;
	const char* UnitToString(Unit unit);
}

class Ingrediant {
	char* name = nullptr;
	unsigned quantity;
	Unit unit;

	void copyFrom(const Ingrediant& other);
	void free();
public:
	Ingrediant();
	Ingrediant(const char* name,unsigned quantity,Unit unit);
	Ingrediant(const Ingrediant& other);
	Ingrediant& operator=(const Ingrediant& other);
	~Ingrediant();

	void setName(const char* name);
	void setUnit(Unit unit);

	const char* getName() const;
	Unit getUnit() const;
	unsigned getQuantity() const;
};

void printIngrediant(const Ingrediant& ingrediant, std::ostream& os = std::cout);