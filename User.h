#pragma once
class User
{
private:
	char* username = nullptr;
	char* password=nullptr;
	int age;
	void copyFrom(const User& other);
	void free();
public:
	User(const char* name, const char* password, int age);
	User(const User& other);
	User& operator=(const User& other);
	~User();

	char* getUserName() const;
	char* getPassword() const;
	int getAge() const;
};