#pragma once
#include <iostream>

class User {
private:
    char* username;
    char* password;
    int age;

    void copyFrom(const User& other);
    void free();

public:

    User(const char* username, const char* password, int age);
    User(const User& other);
    User& operator=(const User& other);
    ~User();

    const char* getUsername() const;
    const char* getPassword() const;
    int getAge() const;
};