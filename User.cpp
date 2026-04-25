#include "User.h"

void User::copyDynamicMemory(const User& other) {
    this->name = new char[std::strlen(other.name) + 1];
    std::strcpy(this->name, other.name);

    this->password = new char[std::strlen(other.password) + 1];
    std::strcpy(this->password, other.password);
}

void User::freeDynamicMemory() {
    delete[] name;
    delete[] password;
}

User::User() : age(0) {
    this->name = new char[1];
    this->name[0] = '\0';

    this->password = new char[1];
    this->password[0] = '\0';
}

User::User(const char* name, const char* password, unsigned age) : age(age) {
    this->name = new char[std::strlen(name) + 1];
    std::strcpy(this->name, name);

    this->password = new char[std::strlen(password) + 1];
    std::strcpy(this->password, password);
}

User::User(const User & other) : age(other.age) {
    copyDynamicMemory(other);
}

User& User::operator=(const User & other) {
    if (this != &other) {
        this->age = other.age;

        freeDynamicMemory();
        copyDynamicMemory(other);
    }

    return *this;
}

User::~User() {
    freeDynamicMemory();
}

const char* User::getUsername() const {
    return this->name;
}

const char* User::getPassword() const {
    return this->password;
}

unsigned User::getAge() const {
    return this->age;
}
