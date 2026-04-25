#include "Recipe.h"
#include <cstring>

#pragma warning (disable:4996)

int Recipe::totalRecipes = 0;

void Recipe::copyDynamicMemoryFrom(const Recipe& other) {
	name = new char[std::strlen(other.name) + 1];
	std::strcpy(name, other.name);

	instructions = new char[std::strlen(other.instructions) + 1];
	std::strcpy(instructions, other.instructions);

	ingredients = new Ingredient[other.capacity];
	for (int i = 0; i < other.size; i++) {
		ingredients[i] = other.ingredients[i];
	}
}

void Recipe::freeDynamicMemory() {
	delete[] name;
	delete[] instructions;
	delete[] ingredients;
}

void Recipe::resize() {
	this->capacity *= 2;
	Ingredient* newIngredients = new Ingredient[capacity];
	for (int i = 0; i < size; i++) {
		newIngredients[i] = ingredients[i];
	}

	delete[] ingredients;
	ingredients = newIngredients;
}

Recipe::Recipe() : id(++totalRecipes), name(nullptr), instructions(nullptr), size(0), capacity(4) {
	ingredients = new Ingredient[capacity];
}

Recipe::Recipe(const char* name, const char* instructions) : id(++totalRecipes), size(0), capacity(4) {
	this->name = new char[std::strlen(name) + 1];
	std::strcpy(this->name, name);

	this->instructions = new char[std::strlen(instructions) + 1];
	std::strcpy(this->instructions, instructions);

	ingredients = new Ingredient[capacity];
}

Recipe::Recipe(const Recipe& other) : id(other.id), size(other.size), capacity(other.capacity) {
	copyDynamicMemoryFrom(other);
}

Recipe& Recipe::operator=(const Recipe& other) {
	if (this != &other) {
		freeDynamicMemory();

		id = other.id;
		size = other.size;
		capacity = other.capacity;

		copyDynamicMemoryFrom(other);
	}

	return *this;
}

Recipe::~Recipe() {
	freeDynamicMemory();
}

int Recipe::getId()  const {
	return id;
}

const char* Recipe::getName()  const {
	return name;
}

void Recipe::addIngredient(const Ingredient& ingredient) {
	if (size == capacity) resize();

	ingredients[size++] = ingredient;
}

void Recipe::removeIngredient(const char* ingredientName) {
	for (int i = 0; i < size; i++) {
		if (strcmp(ingredients[i].getName(), ingredientName) == 0) {
			for (int j = i; j < size - 1; j++) {
				ingredients[j] = ingredients[j + 1];
			}

			size--;
			return;
		}
	}
}

bool Recipe::containsIngredient(const char* ingredientName) const {
	for (int i = 0; i < size; i++) {
		if (strcmp(ingredients[i].getName(), ingredientName) == 0) {
			return true;
		}
	}

	return false;
}

void Recipe::print(std::ostream& os) const {
	os << "Recipe #" << id << std::endl;
	os << "Name: " << name << std::endl;
	os << "Instructions: " << instructions << std::endl;

	os << "Ingredients: " << std::endl;
	for (int i = 0; i < size; i++) {
		os << "\t- ";
		ingredients[i].print(os);
		os << std::endl;
	}
}