#include "User.h"
#include <cstring>
#pragma warning(disable:4996)

void User::deepCopyDynamicMemory(const User& other) {
    username = new char[strlen(other.username) + 1];
    strcpy(username, other.username);

    password = new char[strlen(other.password) + 1];
    strcpy(password, other.password);
}

void User::copyFrom(const User& other) {
    deepCopyDynamicMemory(other);
    age = other.age;
}

void User::free() {
    delete[] username;
    delete[] password;
}

User::User(const char* username, const char* password, int age) : age(age) {
    this->username = new char[strlen(username) + 1];
    strcpy(this->username, username);

    this->password = new char[strlen(password) + 1];
    strcpy(this->password, password);
}

User::User(const User& other) : age(other.age) {
    deepCopyDynamicMemory(other);
}

User& User::operator=(const User& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

User::~User() {
    free();
}

const char* User::getUsername() const {
    return username;
}

const char* User::getPassword() const {
    return password;
}

int User::getAge() const {
    return age;
}
