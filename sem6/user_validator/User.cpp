#include "User.h"
#include "Utils.h"
#include <cstring>
#include "UserValidator.h"

void User::free()
{
	delete[] username;
	delete[] password;

	username = password = nullptr;
}

void User::copyFrom(const User& other)
{
	age = other.age;
	username = Utils::copyDynamicString(other.username);
	password = Utils::copyDynamicString(other.password);
}

User::User() = default;

User::User(const char* username, const char* password, size_t age)
{
	this->age = age;
	this->username = Utils::copyDynamicString(username);
	this->password = Utils::copyDynamicString(password);
}

User& User::operator=(const User& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

User::~User()
{
	free();
}

User::User(const User& other)
{
	copyFrom(other);
}

const char* User::getName() const
{
	return username;
}

const char* User::getPassword() const
{
	return password;
}

size_t User::getAge() const
{
	return age;
}