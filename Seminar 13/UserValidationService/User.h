#pragma once
#include <string>
#include <ostream>

class User {
public:
    User(const std::string& username, const std::string& email, const std::string& password, size_t age);

    const std::string& getUsername() const;
    const std::string& getEmail() const;
    size_t getAge() const;

private:
    std::string username;
    std::string email;
    std::string password;
    size_t age = 0;

    friend class PasswordValidator;
};

std::ostream& operator<<(std::ostream& os, const User& user);
