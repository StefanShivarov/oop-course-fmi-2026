#pragma once
#include "Recipe.h"
class RecipeBook
{
private:
	Recipe* book;
	int count;
	int capacity;

	const int INITIAL_NUM_OF_RECIPES = 10;
public:
	RecipeBook();
	RecipeBook(int capacity);
	~RecipeBook();

	void resize();
	void addRecipe(const Recipe& recipe);
	void removeRecipe(int id);

	bool searchRecipe(const char* ingredientName);
	void printEveryRecipe() const;
};

