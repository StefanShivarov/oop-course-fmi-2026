#include "User.h"
#include "Utils.h"
#include <iostream>

void User::copyFrom(const User& other)
{
	age = other.age;
	budget = other.budget;

	email = Utils::copyDynamicString(other.email);
}

void User::free()
{
	delete[] email;
}

void User::moveFrom(User&& other)
{
	age = other.age;
	budget = other.budget;
	email = other.email;

	other.email = nullptr;
	other.age = 0;
	other.budget = 0.0;

}

User::User(): age(0), budget(0.0)
{
	email = new char[1];
	email[0] = '\0';
}

User::User(const char* email, size_t age, double budget):age(age)
{
	setBudget(budget);
	this->email = Utils::copyDynamicString(email);
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

const char* User::getEmail() const
{
	return email;
}

size_t User::getAge() const
{
	return age;
}

double User::getBudget() const
{
	return budget;
}

bool User::setBudget(double budget)
{
	if (budget < 0.0) {
		return false;
	}

	this->budget = budget;
	return true;
}
