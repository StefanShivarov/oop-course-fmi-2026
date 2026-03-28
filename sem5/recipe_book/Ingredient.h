#pragma once

enum class MeasurementUnit {
	g,
	l,
	ml,
	other
};

class Ingredient
{
private:
	char* name = nullptr;
	double quantity = 0;
	MeasurementUnit unit = MeasurementUnit::other;

	void free();
	void copyFrom(const Ingredient& other);

public:
	Ingredient();
	Ingredient(const Ingredient& other);
	Ingredient& operator=(const Ingredient& other);
	~Ingredient();

	Ingredient(const char* name, double quantity);

	const char* getName() const;
	void printIngredient() const;
	const char* toString(const MeasurementUnit unit) const;
};

