#define _CRT_SECURE_NO_WARNINGS
#include "User.h"
#include<cstring>

User::User() :age(0)
{
	username = new char[1];
	username[0] = '\0';

	password = new char[1];
	password[0] = '\0';
}

User::User(const char* username, const char* password, int age)
{
	setName(username);
	setPassword(password);
	setAge(age);
}

void User::setName(const char* username)
{
	if (username == nullptr)
	{
		return;
	}

	char* newName = new char[strlen(username) + 1];
	strcpy(newName, username);

	delete[] this->username;
	this->username = newName;
}

void User::setPassword(const char* password)
{
	if (password == nullptr)
	{
		return;
	}

	char* newPassword = new char[strlen(password) + 1];
	strcpy(newPassword, password);

	delete[] this->password;
	this->password = newPassword;
}

void User::setAge(int age)
{
	if (age < 0 || age > MAX_AGE)
	{
		this->age = 0;
		return;
	}

	this->age = age;
}

void User::copyFrom(const User& other)
{
	username = new char[strlen(other.username) + 1];
	strcpy(username, other.username);

	password = new char[strlen(other.password) + 1];
	strcpy(password, other.password);

	age = other.age;
}

void User::free()
{
	delete[]username;
	username = nullptr;
	delete[]password;
	password = nullptr;
	age = 0;
}

User::~User()
{
	free();
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

const char* User::getUsername()const
{
	return username;
}

const char* User::getPassword()const
{
	return password;
}

int User::getAge()const
{
	return age;
}

std::ostream& operator<<(std::ostream& os, const User& user)
{
	os << user.username << " " << user.password << " " << user.age;
	return os;
}