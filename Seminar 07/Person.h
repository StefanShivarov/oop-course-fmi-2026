#pragma once

class Person
{
private:
	char* email = nullptr;
	unsigned age;
	double budget;

	void copyDynamicMemory(const Person& other);
	void copyFrom(const Person& other);
	void moveFrom(Person&& other) noexcept;
	void free();
public:
	Person(const char* email, unsigned age, double budget);
	Person(const Person& other);
	Person& operator=(const Person& other);
	Person(Person&& other) noexcept;
	Person& operator=(Person&& other) noexcept;
	~Person();

	const char* getEmail()const;
	unsigned getAge() const;
	double getBudget() const;

	void setBudget(double budget);
	void setEmail(const char* email);

};