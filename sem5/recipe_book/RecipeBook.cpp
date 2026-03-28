#include "RecipeBook.h"
#include <iostream>
#include <print>

void RecipeBook::resizeBook()
{
	capacity *= 2;
	Recipe* temp = new Recipe[capacity];

	for (size_t i = 0; i < size; i++)
	{
		temp[i] = recipe[i];
	}
	delete[] recipe;
	recipe = temp;
}

void RecipeBook::free() {
	delete[] recipe;
	recipe = nullptr;
}

void RecipeBook::copyFrom(const RecipeBook& other)
{
	size = other.size;
	capacity = other.capacity;

	if (other.recipe != nullptr) {
		recipe = new Recipe[capacity];

		for (size_t i = 0; i < size; i++)
		{
			recipe[i] = other.recipe[i];
		}
	}
}

RecipeBook::RecipeBook() : size(0), capacity(2)
{
	recipe = new Recipe[capacity];
}

RecipeBook::RecipeBook(const RecipeBook& other)
{
	copyFrom(other);
}

RecipeBook& RecipeBook::operator=(const RecipeBook& other)
{
	if (&other != this) {
		free();
		copyFrom(other);
	}

	return *this;
}

RecipeBook::~RecipeBook()
{
	free();
}

void RecipeBook::addRecipe(const Recipe& recipe)
{
	if (size == capacity) {
		resizeBook();
	}

	this->recipe[size] = recipe;
	size++;
}

void RecipeBook::removeRecipe(int id)
{
	for (size_t i = 0; i < size; i++)
	{
		if (recipe[i].getId() == id) {
			recipe[i] = recipe[size - 1];
			size--;
			return;
		}
	}
}

const Recipe* RecipeBook::findRecipe(bool(*match)(const Recipe&)) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (match(recipe[i])) {
			return &recipe[i];
		}
	}

	return nullptr;
}

void RecipeBook::printRecipes() const
{
	std::println(" --- RECIPE BOOK ---");
	for (size_t i = 0; i < size; i++)
	{
		recipe[i].printRecipeInfo();
	}
}

void RecipeBook::filterRecipes(bool(*shouldFilter)(const Recipe&)) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (shouldFilter(recipe[i])) {
			recipe[i].printRecipeInfo();
		}
	}
}
