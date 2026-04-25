#include "Cookbook.h"

void Cookbook::copyDynamicMemory(const Cookbook& other) {
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);

	recipes = new Recipe[other.capacity];
	for (int i = 0; i < other.size; i++) {
		recipes[i] = other.recipes[i];
	}
}

void Cookbook::freeDynamicMemory() {
	delete[] name;
	delete[] recipes;
}

void Cookbook::resize() {
	this->capacity *= 2;
	Recipe* newRecipies = new Recipe[this->capacity];
	for (int i = 0; i < this->size; i++) {
		newRecipies[i] = recipes[i];
	}

	delete[] recipes;
	recipes = newRecipies;
}

Cookbook::Cookbook() : size(0), capacity(4) {
	name = new char[1];
	strcpy(name, "");

	this->recipes = new Recipe[this->capacity];
}

Cookbook::Cookbook(const char* name) : size(0), capacity(4) {
	this->name = new char[std::strlen(name) + 1];
	std::strcpy(this->name, name);

	this->recipes = new Recipe[this->capacity];

}

Cookbook::Cookbook(const Cookbook & other) : size(other.size), capacity(other.capacity) {
	copyDynamicMemory(other);
}

Cookbook& Cookbook::operator=(const Cookbook & other)
{
	if (this != &other) {
		size = other.size;
		capacity = other.capacity;

		freeDynamicMemory();
		copyDynamicMemory(other);
	}

	return *this;
}

Cookbook::~Cookbook() {
	freeDynamicMemory();
}

void Cookbook::addRecipe(const Recipe& recipe) {
	if (size == capacity) resize();

	recipes[size++] = recipe;
}

void Cookbook::removeRecipeById(int id) {
	for (int i = 0; i < size; i++) {
		if (id == recipes[i].getId()) {
			for (int j = i; j < size - 1; j++) {
				recipes[j] = recipes[j + 1];
			}
			
			size--;
			return;
		}
	}
}

const Recipe* Cookbook::getRecipeById(int id) const {
	for (int i = 0; i < size; i++) {
		if (id == recipes[i].getId()) {
			return &recipes[i];
		}
	}

	return nullptr;
}

const Recipe* Cookbook::getRecipeByName(const char* name) const {
	for (int i = 0; i < size; i++) {
		if (std::strcmp(name, recipes[i].getName()) == 0) {
			return &recipes[i];
		}
	}

	return nullptr;
}

void Cookbook::printRecipiesByIngredient(const char* name) const {
	for (int i = 0; i < size; i++) {
		if (recipes[i].containsIngredient(name)) {
			recipes[i].print();
		}
	}
}
