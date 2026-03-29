#define _CRT_SECURE_NO_WARNINGS
#include "Recipe.h"
#include<cstring>
#include<print>

size_t Recipe::nextId = 0;

Recipe::Recipe() :countIngredients(0), capacity(MAX_CAPACITY), name(nullptr),
description(nullptr),id(nextId++)
{
	ingredients = new Ingredient[capacity];
}

Recipe::Recipe(const char* name, const char* description, 
	Ingredient* ingredients, size_t countIngredients, size_t capacity)
	:id(nextId++),countIngredients(countIngredients),capacity(capacity)
{
	setName(name);
	setDescription(description);
	
	this->ingredients = new Ingredient[capacity];
	for (size_t i = 0;i < countIngredients;i++)
	{
		this->ingredients[i] = ingredients[i];
	}
}

void Recipe::setName(const char* name)
{
	if (name == nullptr)
	{
		return;
	}

	if (this->name != nullptr)
	{
		delete[]this->name;
	}
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Recipe::setDescription(const char* description)
{
	if (description == nullptr)
	{
		return;
	}

	if (this->description != nullptr)
	{
		delete[]this->description;
	}
	this->description = new char[strlen(description) + 1];
	strcpy(this->description, description);
}


Recipe::~Recipe()
{
	free();
}

void Recipe::resize(size_t newCapacity)
{
	capacity = newCapacity;
	Ingredient* newIngredients = new Ingredient[capacity];

	for (size_t i = 0;i < countIngredients;i++)
	{
		newIngredients[i] = ingredients[i];
	}

	delete[]ingredients;
	ingredients = newIngredients;
}

void Recipe::copyFrom(const Recipe& other)
{
	setName(other.name);
	setDescription(other.description);
	
	countIngredients = other.countIngredients;
	capacity = other.capacity;
	ingredients = new Ingredient[capacity];

	for (size_t i = 0;i < countIngredients;i++)
	{
		ingredients[i] = other.ingredients[i];
	}
}

void Recipe::free()
{
	delete[]name;
	name = nullptr;

	delete[]description;
	description = nullptr;

	delete[]ingredients;
	ingredients = nullptr;

	countIngredients = 0;
}

Recipe::Recipe(const Recipe& other)
{
	copyFrom(other);
	id = nextId++;
}

Recipe& Recipe::operator=(const Recipe& other)
{
	if (this == &other)
	{
		return *this;
	}

	free();
	copyFrom(other);
	
	return *this;
}

size_t Recipe::getId()const
{
	return id;
}

const char* Recipe::getName()const
{
	return name;
}

const char* Recipe::getDescription()const
{
	return description;
}

void Recipe::addIngredient(const Ingredient& ingredient)
{
	if (countIngredients == capacity)
	{
		resize(capacity * 2);
	}

	ingredients[countIngredients++] = ingredient;
}

void Recipe::removeIngredient(const Ingredient& ingredient)
{
	for (size_t i = 0;i < countIngredients;i++)
	{
		if (ingredients[i]==ingredient)
		{
			for (size_t j = i + 1;j < countIngredients;j++)
			{
				ingredients[j - 1] = ingredients[j];
			}
			countIngredients--;
			return;
		}
	}
}

const Ingredient* Recipe::getIngredients()const
{
	return ingredients;
}

size_t Recipe::getCountIngredients()const
{
	return countIngredients;
}

void Recipe::printRecipe()const
{
	std::println("Name: {},Description: {}", name,description);
	std::println("Ingredients:");
	for (size_t i = 0;i < countIngredients;i++)
	{
		ingredients[i].printIngredient();
	}
}