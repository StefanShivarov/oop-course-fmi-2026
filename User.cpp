#include "User.h"
#include <cstring>
#include <utility>
#pragma warning(disable:4996)
void User::moverfrom(User&& other)
{
	this->email = other.email;
	this->age = other.age;
	this->budget = other.budget;

	other.email = nullptr;
	other.age = 0;
	other.budget = 0.0;
}

void User::copyfrom(const User& other)
{
	this->email = new char[strlen(other.email) + 1];
	strcpy(this->email, other.email);
	age = other.age;
	budget = other.budget;
}

void User::free()
{
	delete[] email;
	email = nullptr;
	age = 0;
	budget = 0;
}

User::User(const char* email, int age, double budget)
{
	this->email = new char[strlen(email) + 1];
	strcpy(this->email, email);
	this->age = age;
	this->budget = budget;
}

User::User(const User& other)
{
	copyfrom(other);
}

User::User(User&& other) noexcept
{
	moverfrom(std::move(other));
}

User& User::operator=(const User& other)
{
	if (this != &other) {
		free();
		copyfrom(other);	
	}
	return *this;
}

User& User::operator=(User&& other) noexcept
{
	if (this != &other) {
		free();
		moverfrom(std::move(other));
	}
	return *this;
}

bool User::canAfford(double price) const
{
	return budget >= price;
}

void User::pay(double price)
{
	budget -= price;
}
