#pragma once
class User
{
private:
	char* email;
	int age;
	double budget;

	char* copyString(const char* input);
	void copyForm(const User& other);
	void free();

public:

	User(const char* email, int age,double budget);
	User(const User& other);
	User& operator=(const User& other);
	~User();
	const char* getEmail() const;
	int getAge() const;
	double getBudget() const;


	bool canAfford(double amount) const;
	bool spend(double amount);
	void addBudget(double amount);

};

