#include "User.h"
#include "Utils.h"
#include <cstring>

void User::copyFrom(const User& other)
{
	userName = Utils::copyDynamicString(other.userName);
	password = Utils::copyDynamicString(other.password);

	age = other.age;
}

void User::free()
{
	delete[] userName;
	userName = nullptr;
	delete[] password;
	password = nullptr;
}

User::User():age(0)
{
	userName = new char[1];
	userName[0] = '\0';

	password = new char[1];
	password[0] = '\0';
}

User::User(const char* userName, const char* password, int age) :age(age)
{
	this->userName = Utils::copyDynamicString(userName);
	this->password= Utils::copyDynamicString(password);
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

User::~User()
{
	free();
}

const char* User::getUsername() const
{
	return userName;
}

const char* User::getPassword() const
{
	return password;
}

int User::getAge() const
{
	return age;
}

std::ostream& operator<<(std::ostream& os, const User& user)
{
	os << user.getUsername() << " " << user.getPassword() << " " << user.getAge();
	return os;
}
