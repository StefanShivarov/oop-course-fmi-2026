#include "RecipeBook.h"
#include <cstring>
#include <iostream>
#pragma warning(disable: 4996)

RecipeBook::RecipeBook() : count(0), capacity(INITIAL_NUM_OF_RECIPES)
{
	
	book = new Recipe[capacity];
}

RecipeBook::RecipeBook(int capacity) : count(0), capacity(capacity)
{
	book = new Recipe[capacity];
}

RecipeBook::~RecipeBook()
{
	delete[] book;
	book = nullptr;
	capacity = 0;
}

void RecipeBook::resize()
{
	if (count >= capacity)
	{
		int newCapacity = (capacity == 0) ? INITIAL_NUM_OF_RECIPES : capacity * 2;
		Recipe* newBook = new Recipe[newCapacity];
		for (int i = 0; i < count; i++)
		{
			newBook[i] = book[i];
		}
		delete[] book;
		book = newBook;
		capacity = newCapacity;
	}
}

void RecipeBook::addRecipe(const Recipe& recipe)
{
	if (count >= capacity)
	{
		resize();
	}
	book[count] = recipe;
	count++;
}

void RecipeBook::removeRecipe(int id)
{
	if (id <= 0)
	{
		return;
	}
	for (int i = 0; i < count; i++)
	{
		if (book[i].getId() == id)
		{
			book[i] = book[count - 1];
			count--;
		}
	}
}

bool RecipeBook::searchRecipe(const char* ingredientName)
{
	if (ingredientName == nullptr)
	{
		return false;
	}
	for (int i = 0; i < count; i++)
	{
		if (book[i].hasIngredient(ingredientName))
		{
			return true;
		}
	}
	return false;
}

void RecipeBook::printEveryRecipe() const
{
	if (book == nullptr)
	{
		return;
	}
	for (int i = 0; i < count; i++)
	{
		std::cout << i + 1 << ".  Recipe is ";
		book[i].printRecipe();
		std::cout << "\n------------------\n";
	}
}
