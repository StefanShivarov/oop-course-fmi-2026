#pragma once
#include "Ingredient.h"
class Recipe
{
private:
	static int idCounter;
	int myId;
	char* name;
	char* description;
	Ingredient* ingredientsList;
	int ingredientsCount;
	

	void copyFrom(const Recipe& other);
	void free();

public:
	Recipe();
	Recipe(const Recipe& other);
	Recipe& operator=(const Recipe& other);
	~Recipe();

	void setName(const char* name);
	void setDescription(const char* description);

	void addIngredient(const Ingredient& ingredient);
	void removeIngredient(const Ingredient& ingredient);

	bool isRecipeValid(const Recipe& recipe);
	bool hasIngredient(const char* ingredientName);

	void printRecipe();

	const char* getNameOfRecipe() const;
	const char* getDescriptionOfRecipe() const;
	const int getId() const;
	const int getCount() const;

};

