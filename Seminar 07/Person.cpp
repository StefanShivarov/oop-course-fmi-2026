
#include "Person.h"
#include <iostream>
void Person::copyDynamicMemory(const Person& other)
{
	email = new char[strlen(other.email) + 1];
	strcpy(email, other.email);
}

void Person::copyFrom(const Person& other)
{
	copyDynamicMemory(other);
	age = other.age;
	budget = other.budget;
}

void Person::moveFrom(Person&& other) noexcept
{
	age = other.age;
	budget = other.budget;
	email = other.email;
	other.email = nullptr;
}



void Person::free()
{
	delete[] email;
	email = nullptr;
}



Person::Person(const char* email, unsigned age, double budget):age(age), budget(budget)
{
	setEmail(email);
}

Person::Person(const Person& other):age(other.age), budget(other.budget)
{
	copyDynamicMemory(other);
}

Person& Person::operator=(const Person& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Person::Person(Person&& other) noexcept
{
	moveFrom(std::move(other));
}

Person& Person::operator=(Person&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Person::~Person()
{
	free();
}

const char* Person::getEmail() const
{
	return email;
}

unsigned Person::getAge() const
{
	return age;
}

double Person::getBudget() const
{
	return budget;
}

void Person::setBudget(double budget)
{
	this->budget = budget;
}

void Person::setEmail(const char* email)
{
	delete[] this->email;
	this->email = new char[strlen(email) + 1];
	strcpy(this->email,email);
}



