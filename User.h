#pragma once
class User
{
private:
	char* email = nullptr;
	size_t age;
	double budget;

	void copyFrom(const User&);
	void free();
	void moveFrom(User&&);

public:
	User();
	User(const char*, size_t, double);

	User(const User&);
	User& operator=(const User&);

	User(User&&) noexcept;
	User& operator=(User&&) noexcept;

	~User();

	const char* getEmail()const;
	size_t getAge()const;
	double getBudget()const;

	bool setBudget(double);
};

