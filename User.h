#pragma once
#include <iostream>

class User
{
private:
	char* userName = nullptr;
	char* password = nullptr;
	int age;

	void copyFrom(const User&);
	void free();

public:
	User();
	User(const char*, const char*, int);
	User(const User&);
	User& operator=(const User&);
	~User();

	const char* getUsername()const;
	const char* getPassword()const;
	int getAge()const;

};

std::ostream& operator<<(std::ostream& os, const User&);

