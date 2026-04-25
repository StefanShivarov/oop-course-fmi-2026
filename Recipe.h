#pragma once
#include "Ingredient.h"
#include <iostream>
#include <cstring>
#pragma warning (disable: 4996)

class Recipe {
private:
	static int totalRecipes;

	int id;
	char* name;
	char* instructions;
	Ingredient* ingredients;
	int size;
	int capacity;

	void copyDynamicMemoryFrom(const Recipe& other);
	void freeDynamicMemory();
	void resize();

public:
	Recipe();
	Recipe(const char* name, const char* instructions);
	Recipe(const Recipe& other);
	Recipe& operator=(const Recipe& other);
	~Recipe();

	int getId() const;
	const char* getName() const;
	void addIngredient(const Ingredient& ingredient);
	void removeIngredient(const char* ingredientName);
	bool containsIngredient(const char* ingredientName) const;
	void print(std::ostream& os = std::cout) const;

};

