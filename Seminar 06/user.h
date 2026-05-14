#pragma once
class user
{
private:
    char *username = nullptr;
    char *password = nullptr;
    int age = 0;
    void copyFrom(const user &other);
    void free();

public:
    user();
    user(const char* username, const char* password, int age);
    ~user();
    user(const user &other);
    user &operator=(const user &other);
    const char *get_username() const;
    const char *get_password() const;
    int get_age() const;
};