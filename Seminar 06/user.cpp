#include "user.h"
#include <iostream>
#include <cstring>
user::user()
{
}
user::~user()
{
    free();
}
user::user(const user &other) : age(other.age)
{
    copyFrom(other);
}

void copy(char *&dest, const char *source)
{
    if (source != nullptr)
    {
        dest = new char[std::strlen(source) + 1];
        std::strcpy(dest, source);
    }
    else
    {
        dest = nullptr;
    }
}

void user::copyFrom(const user &other)
{
    copy(username, other.username);
    copy(password, other.password);
}

void user::free()
{
    delete[] username;
    delete[] password;
}

user &user::operator=(const user &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

const char *user::get_username() const
{
    return username;
}
const char *user::get_password() const
{
    return password;
}
int user::get_age() const
{
    return age;
}
user::user(const char *username, const char *password, int age) : age(age)
{
    copy(this->username, username);
    copy(this->password, password);
}