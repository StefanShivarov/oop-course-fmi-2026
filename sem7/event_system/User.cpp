#include "User.h"
#include "Utils.h"
#include <iostream>
#include <utility>

void User::free()
{
	delete[] email;
	email = nullptr;
}

void User::copyFrom(const User& other)
{
	email = Utils::copyDynamicString(other.email);
	age = other.age;
	budget = other.budget;
}

void User::moveFrom(User&& other)
{
	email = other.email;
	age = other.age;
	budget = other.budget;

	other.email = nullptr;
	other.age = 0;
	other.budget = 0;
}

User::User(const char* email, size_t age, double budget) : age(age)
{
	this->email = Utils::copyDynamicString(email);
	setBudget(budget);
}

User::User(const User& other)
{
	copyFrom(other);
}

User& User::operator=(const User& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

User::User(User&& other) noexcept
{
	moveFrom(std::move(other));
}

User& User::operator=(User&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

User::~User()
{
	free();
}

double User::getBudget() const
{
	return budget;
}

void User::setBudget(double budget)
{
	if (budget < 0) {
		this->budget = 0;
		return;
	}
	this->budget = budget;
}

const char* User::getEmail() const
{
	return email;
}

size_t User::getAge() const
{
	return age;
}

bool User::pay(double price) 
{
	if (price < 0 || budget < price) {
		return false;
	}
	budget -= price;
	return true;
}
