#pragma once
class User
{
private:
	char* username = nullptr;
	char* password = nullptr;
	size_t age = 0;

	void free();
	void copyFrom(const User& other);

public:
	User();
	User(const User& other);
	User& operator=(const User& other);
	~User();

	User(const char* username, const char* password, size_t age);

	const char* getName() const;
	const char* getPassword() const;
	size_t getAge() const;
		 
};

