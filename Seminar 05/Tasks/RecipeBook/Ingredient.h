#pragma once
enum class Unit {
	grams,
	kilograms,
	mililitres,
	litres,
	pieces,
	teaspoon,
	tablespoon
};
inline const char*  unitToString(Unit u) {
	switch (u)
	{
	case Unit::grams: return "g";
		break;
	case Unit::kilograms: return "kg";
		break;
	case Unit::mililitres: return "ml";
		break;
	case Unit::litres: return "l";
		break;
	case Unit::pieces: return "pcs";
		break;
	case Unit::teaspoon: return "tsp";
		break;
	case Unit::tablespoon: return "tbsp";
		break;
	default: return "unknown";
		break;
	}
}
class Ingredient
{
private:
	char* name;
	double quantity;
	Unit unit;

	void copyIngredient(const Ingredient& other);
	void freeIngredient();

public:
	Ingredient();
	Ingredient(const Ingredient& other);
	Ingredient& operator=(const Ingredient& other);
	Ingredient(const char* name, double quantity, Unit unit);
	~Ingredient();

	const char* getName() const;
	void setName(const char* name);
	
	const double getQuantity() const;
	
	const Unit getUnit() const;
};

