#include"Unit.h"
#include<cstring>

const char* Unit::convertToString(Units unit)
{
	switch (unit)
	{
	case Units::GRAMS:return "gr";
	case Units::KILOGRAMS:return "kg";
	case Units::LITERS:return "l";
	case Units::MILLILITERS:return "ml";
	default:return "other";
	}
}

Units Unit::convertToUnit(const char* name)
{
	if (strcmp(name, "gr") == 0)
	{
		return Units::GRAMS;
	}
	else if (strcmp(name, "kg") == 0)
	{
		return Units::KILOGRAMS;
	}
	else if (strcmp(name, "l") == 0)
	{
		return Units::LITERS;
	}
	else if (strcmp(name, "ml") == 0)
	{
		return Units::MILLILITERS;
	}
	else
	{
		return Units::OTHER;
	}
}