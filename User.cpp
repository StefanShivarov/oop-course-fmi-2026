#include "User.h"
#include <cstring>
#pragma warning (disable:4996)

void User::copyFrom(const User& other)
{
	username = new char[std::strlen(other.username) + 1];
	std::strcpy(username, other.username);
	password = new char[std::strlen(other.password) + 1];
	std::strcpy(password, other.password);
	age = other.age;
}

void User::free()
{
	delete[] username;
	username = nullptr;
	delete[] password;
	password = nullptr;
}

User::User(const char* name, const char* password, int age)
{
	this->username = new char[std::strlen(name) + 1];
	std::strcpy(username, name);
	this->password = new char[std::strlen(password) + 1];
	std::strcpy(this->password, password);
	this->age = age;
}

User::User(const User& other)
{
	copyFrom(other);
}

User& User::operator=(const User& other)
{
	if (&other != this) {
		free();
		copyFrom(other);
	}
	return *this;
}

User::~User()
{
	free();
}

char* User::getUserName() const
{
	return username;
}

char* User::getPassword() const
{
	return password;
}

int User::getAge() const
{
	return age;
}
