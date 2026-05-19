#pragma once
class User
{
private:
	char* email = nullptr;
	size_t age = 0;
	double budget = 0;

	void free();
	void copyFrom(const User& other);
	void moveFrom(User&& other);

public:
	User() = default;
	User(const char* email, size_t age, double budget);

	User(const User& other);
	User& operator=(const User& other);

	User(User&& other)noexcept;
	User& operator=(User&& other)noexcept;

	~User();

	double getBudget() const;
	void setBudget(double budget);

	const char* getEmail() const;
	size_t getAge() const;

	bool pay(double price);
};

