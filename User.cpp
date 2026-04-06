#define _CRT_SECURE_NO_WARNINGS
#include "User.h"
#include <cstring>

char* User::copyString(const char* input)
{
    if (!input)
    {
        return nullptr;
    }

    size_t len = std::strlen(input);
    char* result = new char[len + 1];
    std::strcpy(result, input);
    return result;
}

void User::copyForm(const User& other)
{
    email = copyString(other.email);
    age = other.age;
    budget = other.budget;

}

void User::free()
{
    delete[] email;
    email = nullptr;
}

User::User(const char* email, int age, double budget)
{
    this->email = copyString(email);
	this->age = age;
	this->budget = budget;
}

User::User(const User& other)
{
    copyForm(other);
}


User& User::operator=(const User& other)
{
    if (this != &other) {
        free();
        copyForm(other);
    }
    return *this;
}

User::~User()
{
    free();
}

const char* User::getEmail() const
{
    return email;
}

int User::getAge() const
{
    return age;
}

double User::getBudget() const
{
    return budget;
}

bool User::canAfford(double amount) const
{
    if (amount <= budget) {
        return true;
    }
    return false;
}

bool User::spend(double amount)
{
    if (amount<0 || amount>budget) {
        return false;
    }
    budget -= amount;
    return true;
}

void User::addBudget(double amount)
{
    if (amount > 0) {
        budget += amount;
    }
}




