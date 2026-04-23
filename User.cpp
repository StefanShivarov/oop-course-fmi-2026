#define _CRT_SECURE_NO_WARNINGS
#include "User.h"
#include<cstring>
#include<iostream>

User::User() :age(0), budget(0)
{
	email = new char[1];
	email[0] = '\0';
}

User::User(const char* email, int age, double budget)
{
	setEmail(email);
	setAge(age);
	setBudget(budget);
}

void User::setAge(int age)
{
	if (age < 0 || age > MAX_AGE)
	{
		return;
	}
	this->age = age;
}

void User::setBudget(double budget)
{
	if (budget < 0)
	{
		return;
	}
	this->budget = budget;
}

void User::setEmail(const char* email)
{
	if (email == nullptr)
	{
		return;
	}
	delete[]this->email;
	this->email = new char[strlen(email) + 1];
	strcpy(this->email, email);
}

void User::copyFrom(const User& other)
{
	email = new char[strlen(other.email) + 1];
	strcpy(email, other.email);
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

void User::free()
{
	delete[]email;
	email = nullptr;
	age = 0;
	budget = 0;
}

User::User(const User& other)
{
	copyFrom(other);
}

User& User::operator=(const User& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

User::User(User&& other)noexcept
{
	moveFrom(std::move(other));
}

User& User::operator=(User&& other)noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

User::~User()
{
	free();
}

bool User::canAfford(double price)const
{
	return budget >= price;
}

void User::pay(double price)
{
	budget -= price;
}