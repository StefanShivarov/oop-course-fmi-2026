#pragma once
#include"Recipe.h"

class RecipeBook
{
private:
	static constexpr size_t MAX_CAPACITY = 16;
	Recipe* recipes = nullptr;
	size_t count = 0;
	size_t capacity = MAX_CAPACITY;

	void resize(size_t newCapacity);
	void copyFrom(const RecipeBook& other);
	void free();

public:
	RecipeBook();
	~RecipeBook();

	RecipeBook(const RecipeBook& other);
	RecipeBook& operator=(const RecipeBook& other);

	void addRecipe(const Recipe& recipe);
	void removeRecipe(size_t id);

	Recipe& getRecipeByName(const char* name);
	Recipe& getRecipeById(size_t id);

	void addIngredient(const Ingredient& ingredient,size_t id);
	void removeIngredient(const Ingredient& ingredient, size_t id);

	void printRecipe(const Recipe& recipe)const;
	void printRecipeBook()const;

	bool containsIngredient(const char* ingredientName)const;
	void filterRecipesByIngredient(const char* ingredientName)const;
	void filterRecipesByName(const char* name)const;
	void filterRecipesByDescription(const char* description)const;
};

