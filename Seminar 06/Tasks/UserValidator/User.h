#pragma once

class User {
private:
    char* username = nullptr;
    char* password = nullptr;
    int age = 0;

    void deepCopyDynamicMemory(const User& other);
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
