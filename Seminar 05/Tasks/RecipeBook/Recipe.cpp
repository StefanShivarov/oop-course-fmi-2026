#include "Recipe.h"
#include <cstring>
#include <iostream>
#pragma warning(disable: 4996)
void Recipe::copyFrom(const Recipe& other) {
	
	ingredientsList = new Ingredient[other.ingredientsCount];
	for (int i = 0; i < other.ingredientsCount; i++)
	{
		ingredientsList[i] = other.ingredientsList[i];
	}

	setName(other.name);
	setDescription(other.description);
	ingredientsCount = other.ingredientsCount;
	myId = other.myId;
}

void Recipe::free()
{
	delete[] ingredientsList;
	delete[] name;
	delete[] description;
	ingredientsList = nullptr;
	name = nullptr;
	description = nullptr;
	ingredientsCount = 0;
}

int Recipe::idCounter = 1;

Recipe::Recipe() : name(nullptr), description(nullptr) , ingredientsList(nullptr), ingredientsCount(0)
{
	myId = idCounter++;
	name = new char[1];
	name[0] = '\0';
	description = new char[1];
	description[0] = '\0';
}

Recipe::Recipe(const Recipe& other)
{
	copyFrom(other);
}

Recipe& Recipe::operator=(const Recipe& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
	// TODO: insert return statement here
}


Recipe::~Recipe()
{
	free();
}
void Recipe::setName(const char* name)
{
	if (name == nullptr)
	{
		return;
	}
	delete[] this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Recipe::setDescription(const char* description)
{
	if (description == nullptr)
	{
		return;
	}
	delete[] this->description;
	this->description = new char[strlen(description) + 1];
	strcpy(this->description, description);
}

void Recipe::addIngredient(const Ingredient& ingredient)
{
	Ingredient* newList = new Ingredient[ingredientsCount + 1];
	for (int i = 0; i < ingredientsCount; i++)
	{
		newList[i] = ingredientsList[i];
	}
	newList[ingredientsCount] = ingredient;
	ingredientsCount++;

	delete[] ingredientsList;
	ingredientsList = newList;
}

void Recipe::removeIngredient(const Ingredient& ingredient)
{
	if (ingredientsList == nullptr || ingredientsCount == 0)
	{
		return;
	}
	for (int i = 0; i < ingredientsCount; i++)
	{
		if (strcmp(ingredientsList[i].getName(), ingredient.getName()) == 0)
		{
			ingredientsList[i] = ingredientsList[ingredientsCount - 1];
			ingredientsCount--;
		}
	}
}

bool Recipe::isRecipeValid(const Recipe& recipe)
{
	if (recipe.description == nullptr || recipe.myId <= 0 || recipe.ingredientsCount == 0 || recipe.ingredientsList == nullptr || recipe.name == nullptr)
	{
		return false;
	}
	return true;
}

bool Recipe::hasIngredient( const char* ingredientName)
{
	if (!isRecipeValid(*this))
	{
		return false;
	}
	for (int i = 0; i <ingredientsCount; i++)
	{
		if (strcmp(ingredientsList[i].getName(), ingredientName) == 0)
		{
			return true;
		}
	}
	return false;
}

void Recipe::printRecipe()
{
	std::cout << "Recipe's id: " << myId << std::endl;
	std::cout << "Recipe's name: " << name << std::endl;
	std::cout << "Recipe's description: " << description << std::endl;
	std::cout << "Recipe's ingredientsCount: " << ingredientsCount << std::endl;
	std::cout << "Ingredients: ";
	for (int i = 0; i < ingredientsCount; i++)
	{
		std::cout << ingredientsList[i].getName() << ", ";
	}
}

const char* Recipe::getNameOfRecipe() const
{
	return name;
}

const char* Recipe::getDescriptionOfRecipe() const
{
	return description;
}

const int Recipe::getId() const
{
	return myId;
}

const int Recipe::getCount() const
{
	return ingredientsCount;
}
