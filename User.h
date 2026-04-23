#pragma once
class User
{
private:
	char* email = nullptr;
	int age;
	double budget;
	void moverfrom(User&& other);
	void copyfrom(const User& other);
	void free();
public:
	User()=default;
	User(const char* email, int age, double budget);
	User(const User& other);
	User(User&& other) noexcept;
	User& operator=(const User& other);
	User& operator=(User&& other) noexcept;
	bool canAfford(double price) const;
	void pay(double price);
};