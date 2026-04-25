#pragma once
#include "Recipe.h"
#include <cstring>
#pragma warning (disable: 4996)

class Cookbook {
private:
	int size;
	int capacity;
	char* name;
	Recipe* recipes;

	void copyDynamicMemory(const Cookbook& other);
	void freeDynamicMemory();
	void resize();

public:
	Cookbook();
	Cookbook(const char* name);
	Cookbook(const Cookbook& other);
	Cookbook& operator=(const Cookbook& other);
	~Cookbook();

	void addRecipe(const Recipe& recipe);
	void removeRecipeById(int id);
	const Recipe* getRecipeById(int id) const;
	const Recipe* getRecipeByName(const char* name) const;
	void printRecipiesByIngredient(const char* name) const;
};

