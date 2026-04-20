#pragma once
#include <iostream>
#include <cstring>
#include "Recipe.h"
#pragma warning(disable: 4996)

class Cookbook {
	char* name = nullptr;
	Recipe* recipies = nullptr;
	size_t size;
	size_t capacity;

	void free();
	void copyFrom(const Cookbook& other);
	void reSize();
public:
	Cookbook(const char* name);
	Cookbook(const Cookbook& other);
	Cookbook& operator=(const Cookbook& other);
	~Cookbook();

	const char* getName() const;
	const Recipe* getRecipes() const;
    size_t getRecipiesCount() const;

	void addRecipe(Recipe& recipe);
	void removeRecipe(const char* name);
	bool containsRecipe(const char* name) const;

};
void printCookbook(const Cookbook& cookbook, std::ostream& os = std::cout);
void filterRecipes(const Cookbook& cookbook, bool (*shouldFilter) (const Recipe&), std::ostream& os = std::cout);
