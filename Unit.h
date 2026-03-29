#pragma once

enum class Units
{
	GRAMS,
	LITERS,
	KILOGRAMS,
	MILLILITERS,
	OTHER
};

class Unit
{
public:
	static const char* convertToString(Units unit);
	static Units convertToUnit(const char* unit);
};