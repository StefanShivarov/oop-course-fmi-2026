#pragma once
#include "Ingredient.h"

class Recipe
{
private:
	char* name = nullptr;
	char* description = nullptr;

	Ingredient* list;
	size_t size = 0;
	size_t capacity = 0;

	int id = 0;
	static int count;

	void resize();

	void free();
	void copyFrom(const Recipe& other);

public:
	Recipe();
	Recipe(const Recipe& other);
	Recipe& operator=(const Recipe& other);
	~Recipe();

	Recipe(const char* name, const char* description);

	int getId() const;

	void addIngredient(const Ingredient& ingredient);
	void removeIngredient(const Ingredient& ingredient);

	bool isInRecipe(const char* nameIng) const;

	void printRecipeInfo() const;
};

