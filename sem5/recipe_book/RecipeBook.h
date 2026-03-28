#pragma once
#include "Recipe.h"

class RecipeBook
{
private:
	Recipe* recipe = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void resizeBook();
	
	void free();
	void copyFrom(const RecipeBook& other);

public:
	RecipeBook();
	RecipeBook(const RecipeBook& other);
	RecipeBook& operator=(const RecipeBook& other);
	~RecipeBook();

	void addRecipe(const Recipe& recipe);
	void removeRecipe(int id);

	//void searchBy(const char* name) const;
	const Recipe* findRecipe(bool (*match)(const Recipe&)) const;
	//bool isInRecipe(const char* nameIng);

	void printRecipes() const;
	void filterRecipes(bool (*shouldFilter)(const Recipe&)) const;

};

