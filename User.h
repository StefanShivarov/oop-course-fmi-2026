#pragma once

class User
{
private:
	static constexpr int MAX_AGE = 120;
	char* email = nullptr;
	int age = 0;
	double budget = 0;

	void copyFrom(const User& other);
	void free();
	void moveFrom(User&& other);

public:
	User();
	User(const char* email, int age, double budget);

	User(const User& other);
	User& operator=(const User& other);
	User(User&& other)noexcept;
	User& operator=(User&& other)noexcept;
	~User();

	void setEmail(const char* email);
	void setAge(int age);
	void setBudget(double budget);

	bool canAfford(double price)const;
	void pay(double price);

};

