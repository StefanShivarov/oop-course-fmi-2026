#pragma once
#include <iostream>
#include "Cookbook.h"
#include <cstring>
#pragma warning(disable: 4996)

void Cookbook::free()
{
	delete[] name;
	delete[] recipies;

	name = nullptr;
	recipies = nullptr;
	size = 0;
}

void Cookbook::copyFrom(const Cookbook& other)
{
	size = other.size;
	capacity = other.capacity;
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	recipies = new Recipe[other.capacity];
	for (size_t i = 0; i < size; i++) {
		recipies[i] = other.recipies[i];
	}
}

void Cookbook::reSize()
{
	Recipe* newRecipies = new Recipe[capacity + 5];
	for (size_t i = 0; i < size; i++) {
		newRecipies[i] = recipies[i];
	}
	delete[] recipies;
	recipies = newRecipies;
	capacity += 5;
}

Cookbook::Cookbook(const char* name) : size(0), capacity(5)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	recipies = new Recipe[capacity];
}

Cookbook::Cookbook(const Cookbook& other) : size(other.size), capacity(other.capacity)
{
	copyFrom(other);
}

Cookbook& Cookbook::operator=(const Cookbook& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Cookbook::~Cookbook()
{
	free();
}

const char* Cookbook::getName() const
{
	return name;
}

const Recipe* Cookbook::getRecipes() const
{
	return recipies;
}

 size_t Cookbook::getRecipiesCount() const
{
	return size;
}

void Cookbook::addRecipe(Recipe& recipe)
{
	if (size >= capacity) reSize();
	if (containsRecipe(recipe.getName())) return;
	recipies[size++] = recipe;
}

void Cookbook::removeRecipe(const char* name)
{
	for (int i = 0; i < size; i++) {
		if (strcmp(name, recipies[i].getName()) == 0) {
			for (int j = i; j < size - 1; j++) {
				recipies[j] = recipies[j + 1];
			}
			size--;
			return;
		}
	}
}

bool Cookbook::containsRecipe(const char* name) const
{
	for (int i = 0; i < size; i++) {
		if (strcmp(name, recipies[i].getName()) == 0)
			return true;
	}
	return false;
}

void printCookbook(const Cookbook& cookbook, std::ostream& os)
{
	os << "Name: " << cookbook.getName() << '\n';
	for (int i = 0; i < cookbook.getRecipiesCount(); i++) {
		os << "Recipe#" << i + 1 << '\n';
		printRecipe(cookbook.getRecipes()[i]);
	}
}

void filterRecipes(const Cookbook& cookbook, bool(*shouldFilter)(const Recipe&), std::ostream& os)
{
	for (int i = 0; i < cookbook.getRecipiesCount(); i++) {
		if (shouldFilter(cookbook.getRecipes()[i]))
			printRecipe(cookbook.getRecipes()[i], os);
	}
}
