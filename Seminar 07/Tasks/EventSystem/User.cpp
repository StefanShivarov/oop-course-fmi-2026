#include "User.h"
#include "utils.h"
#include <utility>

User::User(const char* name, const char* email, unsigned age, double budget)
    : age(age), budget(budget) {
    setName(name);
    setEmail(email);
}

void User::free() {
    delete[] name;
    delete[] email;
    name = nullptr;
    email = nullptr;
    age = 0;
    budget = 0.0;
}

void User::copyFrom(const User& other) {
    StrUtils::deepCopyString(name, other.name);
    StrUtils::deepCopyString(email, other.email);
    age = other.age;
    budget = other.budget;
}

void User::moveFrom(User&& other) noexcept {
    name = other.name;
    email = other.email;
    age = other.age;
    budget = other.budget;

    other.name = nullptr;
    other.email = nullptr;
    other.age = 0;
    other.budget = 0.0;
}

User::User(const User& other) {
    copyFrom(other);
}

User& User::operator=(const User& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

User::User(User&& other) noexcept {
    moveFrom(std::move(other));
}

User& User::operator=(User&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}

User::~User() {
    free();
}

const char* User::getName() const {
    return name;
}

const char* User::getEmail() const {
    return email;
}

unsigned User::getAge() const {
    return age;
}

double User::getBudget() const {
    return budget;
}

void User::setName(const char* name) {
    delete[] this->name;
    StrUtils::deepCopyString(this->name, name);
}

void User::setEmail(const char* email) {
    delete[] this->email;
    StrUtils::deepCopyString(this->email, email);
}

void User::setAge(unsigned age) {
    this->age = age;
}

void User::setBudget(double budget) {
    this->budget = budget;
}

bool User::pay(double amount) {
    if (amount < 0 || budget < amount) {
        return false;
    }

    budget -= amount;
    return true;
}

void printUser(const User& user) {
    std::cout << "User: " << user.getName()
              << " | email: " << user.getEmail()
              << " | age: " << user.getAge()
              << " | budget: " << user.getBudget()
              << '\n';
}
