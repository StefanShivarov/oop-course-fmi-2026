#pragma once
#include <iostream>
#include <cstring>
#include "ingrediant.h"
#pragma warning(disable: 4996)

class Recipe {
	char* name = nullptr;
	char* description = nullptr;
	Ingrediant* ingrediants = nullptr;
	static int total;
	int id;
	size_t capacity;
	size_t size;
	const size_t DEFAULT_CAPACITY = 5;

	void free();
	void copyFrom(const Recipe& other);
	void copyDynamicMemory(const Recipe& other);

	void reSize(const size_t newSize);
public:
	Recipe();
	Recipe(const char* name, const char* description);
	Recipe(const Recipe& other);
	Recipe& operator=(const Recipe& other);
	~Recipe();

	void addIngrediant(const Ingrediant& ingrediant);
	void removeIngrediant(const char* name);
	bool contains(const char* name) const;

	int getId() const;
	const char* getName() const;
	const char* getDescription() const;
	const Ingrediant* getIngrediants() const;
	size_t getSize() const;
};

void printRecipe(const Recipe& recipe, std::ostream& os = std::cout);