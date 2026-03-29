#pragma once
#include<fstream>

class User
{
private:
	static constexpr int MAX_AGE = 100;

	char* username = nullptr;
	char* password = nullptr;
	int age = 0;

	void copyFrom(const User& other);
	void free();

public:
	User();
	User(const char* name, const char* password, int age);
	~User();

	User(const User& other);
	User& operator=(const User& other);

	void setName(const char* username);
	void setPassword(const char* password);
	void setAge(int age);

	const char* getUsername()const;
	const char* getPassword()const;
	int getAge()const;

	friend std::ostream& operator<<(std::ostream& os, const User& user);
};


