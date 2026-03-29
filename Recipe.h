#pragma once
#include "Ingredient.h"

class Recipe
{
private:
	static constexpr size_t MAX_CAPACITY = 16;
	static size_t nextId;
	size_t id = 0;
	char* name = nullptr;
	char* description = nullptr;
	Ingredient* ingredients = nullptr;
	size_t countIngredients = 0;
	size_t capacity = MAX_CAPACITY;

	void copyFrom(const Recipe& other);
	void free();
	void resize(size_t newCapacity);

public:
	Recipe();

	Recipe(const char* name, const char* description,
		Ingredient* ingredients, size_t countIngredients, size_t capacity);

	~Recipe();

	Recipe(const Recipe& other);

	Recipe& operator=(const Recipe& other);

	void setName(const char* name);
	void setDescription(const char* description);

	size_t getId()const;
	const char* getName()const;
	const char* getDescription()const;
    const Ingredient* getIngredients()const;
	size_t getCountIngredients()const;

	void addIngredient(const Ingredient& ingredient);
	void removeIngredient(const Ingredient& ingredient);

	void printRecipe()const;
};

