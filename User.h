#pragma once

#include <cstring>
#pragma warning (disable: 4996)

class User {
private:
	char* name;
	char* password;
	unsigned age;

	void copyDynamicMemory(const User& other);
	void freeDynamicMemory();

public:
	User();
	User(const char* name, const char* password, unsigned age);
	User(const User& other);
	User& operator=(const User& other);
	~User();

	const char* getUsername() const;
	const char* getPassword() const;
	unsigned getAge() const;
};

