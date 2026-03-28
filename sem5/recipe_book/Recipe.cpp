#include "Recipe.h"
#include "Utils.h"
#include <cstring>
#include <iostream>
#include <print>
#include "RecipeBook.h"
#pragma warning(disable : 4996)

int Recipe::count = 0;

void Recipe::resize()
{
	capacity *= 2;
	Ingredient* temp = new Ingredient[capacity];
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = list[i];
	}

	delete[] list;
	list = temp;
}

void Recipe::free()
{
	delete[] name;
	delete[] description;
	delete[] list;

	description = name = nullptr;
	list = nullptr;
}

void Recipe::copyFrom(const Recipe& other)
{
	name = Utils::copyDynamicString(other.name);
	description = Utils::copyDynamicString(other.description);

	size = other.size;
	capacity = other.capacity;

	if (other.list != nullptr) {
		list = new Ingredient[capacity];
		for (size_t i = 0; i < size; i++)
		{
			this->list[i] = other.list[i];
		}
	}

	id = other.id;
}

Recipe::Recipe() :size(0), capacity(2), id(count++)
{
	name = new char[1];
	name[0] = '\0';

	description = new char[1];
	description[0] = '\0';

	list = new Ingredient[capacity];
}

Recipe::Recipe(const Recipe& other)
{
	copyFrom(other);
}

Recipe& Recipe::operator=(const Recipe& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

Recipe::~Recipe()
{
	free();
}

Recipe::Recipe(const char* name, const char* description) 
	: size(0), capacity(2), id(count++)
{
	list = new Ingredient[capacity];
	this->name = Utils::copyDynamicString(name);
	this->description = Utils::copyDynamicString(description);
}

int Recipe::getId() const
{
	return id;
}


void Recipe::addIngredient(const Ingredient& ingredient)
{
	if (size == capacity) {
		resize();
	}

	list[size++] = ingredient;
}

void Recipe::removeIngredient(const Ingredient& ingredient)
{
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(list[i].getName(), ingredient.getName()) == 0) {
			list[i] = list[size - 1];
			size--;
			return;;
		}
	}
}

bool Recipe::isInRecipe(const char* nameIng) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(list[i].getName(), nameIng) == 0) {
			return true;
		}
	}
	return false;
}

void Recipe::printRecipeInfo() const
{
	std::println("Recipe name: {}", name);
	std::println("Preparation instructions {}", description);
	std::println("List of ingredients:");

	for (size_t i = 0; i < size; i++)
	{
		std::cout << "-";
		list[i].printIngredient();
	}
	std::cout << '\n';
}
