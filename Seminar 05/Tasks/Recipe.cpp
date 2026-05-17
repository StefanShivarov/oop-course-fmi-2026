#include "Recipe.h"
#pragma warning(disable: 4996)

int Recipe::total = 0;

void Recipe::free()
{
	delete[] name;
	name = nullptr;
	delete[] description;
	description = nullptr;
	delete[] ingrediants;
	ingrediants = nullptr;
	size = 0;
}

void Recipe::copyFrom(const Recipe& other)
{
	copyDynamicMemory(other);
	capacity = other.capacity;
	size = other.size;
	id = other.id;
}

void Recipe::copyDynamicMemory(const Recipe& other)
{
	this->name = new char[strlen(other.name) + 1];
	strcpy(this->name, other.name);

	description = new char[strlen(other.description) + 1];
	strcpy(description, other.description);

	ingrediants = new Ingrediant[other.capacity];
	for (int i = 0; i < other.size; i++) {
		ingrediants[i] = other.ingrediants[i];
	}

}

void Recipe::reSize(const size_t newSize)
{
	if (newSize < 0 || newSize == size) return;
	capacity = newSize;
	Ingrediant* newArr = new Ingrediant[capacity];
	for (int i = 0; i < std::min(size,newSize); i++) {
		newArr[i] = ingrediants[i];
	}
	delete[] ingrediants;
	ingrediants = newArr;
}

Recipe::Recipe() : Recipe("","")
{
}

Recipe::Recipe(const char* name, const char* description) : id(++total), size(0), capacity(5)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name,name);

	this->description = new char[strlen(description) + 1];
	strcpy(this->description,description);

	ingrediants = new Ingrediant[capacity];
}

Recipe::Recipe(const Recipe& other) : id(++total), size(other.size), capacity(other.capacity)
{
	copyDynamicMemory(other);
}

Recipe& Recipe::operator=(const Recipe& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return* this;
}

Recipe::~Recipe()
{
	free();
}

void Recipe::addIngrediant(const Ingrediant& ingrediant)
{
	if (size >= capacity) {
		reSize(capacity + DEFAULT_CAPACITY);
	}
	ingrediants[size++] = ingrediant;
}

void Recipe::removeIngrediant(const char* name)
{
	for (int i = 0; i < size; i++) {
		if (strcmp(name, ingrediants[i].Ingrediant::getName()) == 0) {
			for (int j = i; j < size - 1; j++) {
				ingrediants[j] = ingrediants[j + 1];
			}
			size--;
			return;
		}
	}
}

bool Recipe::contains(const char* name) const
{
	for (int i = 0; i < size; i++) {
		if (strcmp(name, ingrediants[i].Ingrediant::getName()) == 0) {
			return true;
		}
	}
	return false;
}

int Recipe::getId() const
{
	return id;
}

const char* Recipe::getName() const
{
	return name;
}

const char* Recipe::getDescription() const
{
	return description;
}

const Ingrediant* Recipe::getIngrediants() const
{
	return ingrediants;
}

size_t Recipe::getSize() const
{
	return size;
}

void printRecipe(const Recipe& recipe, std::ostream& os)
{
	os << "ID: " << recipe.getId() << '\n';
	os << "Name: " << recipe.getName() << '\n';
	os << "Description: " << recipe.getDescription() << '\n';
	const Ingrediant* ingrediants = recipe.getIngrediants();
	os << "Ingrediants:";
	for (int i = 0; i < recipe.getSize(); i++) {
		printIngrediant(ingrediants[i], os);
	}
}
