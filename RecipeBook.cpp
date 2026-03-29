#include "RecipeBook.h"
#include<cstring>
#include<print>

RecipeBook::RecipeBook():count(0), capacity(MAX_CAPACITY)
{
	recipes = new Recipe[capacity];
}

RecipeBook::~RecipeBook()
{
	free();
}

void RecipeBook::resize(size_t newCapacity)
{
	capacity = newCapacity;
	Recipe* newRecipes = new Recipe[capacity];

	for (size_t i = 0;i < count;i++)
	{
		newRecipes[i] = recipes[i];
	}
	delete[]recipes;

	recipes = newRecipes;
}

void RecipeBook::copyFrom(const RecipeBook& other)
{
	count = other.count;
	capacity = other.capacity;
	recipes = new Recipe[capacity];

	for (size_t i = 0;i < count;i++)
	{
		recipes[i] = other.recipes[i];
	}
}

void RecipeBook::free()
{
	delete[]recipes;
	recipes = nullptr;
	count = 0;
	capacity = 0;
}

RecipeBook::RecipeBook(const RecipeBook& other)
{
	copyFrom(other);
}

RecipeBook& RecipeBook::operator=(const RecipeBook& other)
{
	if (this == &other)
	{
		return *this;
	}

	free();
	copyFrom(other);

	return *this;
}

void RecipeBook::addRecipe(const Recipe& recipe)
{
	if (count == capacity)
	{
		resize(capacity * 2);
	}

	recipes[count++] = recipe;
}

void RecipeBook::removeRecipe(size_t id)
{
	for (size_t i = 0;i < count;i++)
	{
		if (recipes[i].getId() == id)
		{
			for (size_t j = i + 1;j < count;j++)
			{
				recipes[j - 1] = recipes[j];
			}
			count--;
			break;
		}
	}
}

Recipe& RecipeBook::getRecipeByName(const char* name)
{
	for (size_t i = 0;i < count;i++)
	{
		if (strcmp(recipes[i].getName(), name) == 0)
		{
			return recipes[i];
		}
	}
}

Recipe& RecipeBook::getRecipeById(size_t id)
{
	for (size_t i = 0;i < count;i++)
	{
		if (recipes[i].getId() == id)
		{
			return recipes[i];
		}
	}

	std::println("Recipe not found by id.");
}

void RecipeBook::addIngredient(const Ingredient& ingredient,size_t id)
{
	for (size_t i = 0;i < count;i++)
	{
		if (recipes[i].getId() == id)
		{
			recipes[i].addIngredient(ingredient);
			return;
		}
	}
}

void RecipeBook::removeIngredient(const Ingredient& ingredient, size_t id)
{
	for (size_t i = 0;i < count;i++)
	{
		if (recipes[i].getId() == id)
		{
			recipes[i].removeIngredient(ingredient);
			return;
		}
	}
}

void RecipeBook::printRecipe(const Recipe& recipe)const
{
	recipe.printRecipe();
}

void RecipeBook::printRecipeBook()const
{
	for (size_t i = 0;i < count;i++)
	{
		recipes[i].printRecipe();
	}
}

void RecipeBook::filterRecipesByIngredient(const char* ingredientName)const
{
	for (size_t i = 0;i < count;i++)
	{
		const Ingredient* ingredients = recipes[i].getIngredients();
		size_t countIngredients = recipes[i].getCountIngredients();

		for (size_t j = 0;j < countIngredients;j++)
		{
			if (strcmp(ingredients[j].getName(), ingredientName) == 0)
			{
				recipes[i].printRecipe();
				break;
			}
		}
	}
}

bool RecipeBook::containsIngredient(const char* ingredientName)const
{
	for (size_t i = 0;i < count;i++)
	{
		const Ingredient* ingredients = recipes[i].getIngredients();
		size_t countIngredients = recipes[i].getCountIngredients();

		for (size_t j = 0;j < countIngredients;j++)
		{
			if (strcmp(ingredients[j].getName(), ingredientName) == 0)
			{
				return true;
			}
		}
	}
	return false;
}

void RecipeBook::filterRecipesByName(const char* name)const
{
	if (name == nullptr)
	{
		return;
	}

	for (size_t i = 0;i < count;i++)
	{
		if(strcmp(recipes[i].getName(), name) == 0)
		{
			recipes[i].printRecipe();
		}
	}
}

void RecipeBook::filterRecipesByDescription(const char* description)const
{
	if (description == nullptr)
	{
		return;
	}

	for (size_t i = 0;i < count;i++)
	{
		if (strcmp(recipes[i].getDescription(), description) == 0)
		{
			recipes[i].printRecipe();
		}
	}
}