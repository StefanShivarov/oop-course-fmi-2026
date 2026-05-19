#include "User.h"

User::User(const std::string& username, const std::string& email, const std::string& password, size_t age)
    : username(username), email(email), password(password), age(age) {}

const std::string& User::getUsername() const {
    return username;
}

const std::string& User::getEmail() const {
    return email;
}

size_t User::getAge() const {
    return age;
}

std::ostream& operator<<(std::ostream& os, const User& user) {
    return os << "User("
        << "username = " << user.getUsername()
        << ", email = " << user.getEmail()
        << ", age = " << user.getAge()
        << ")\n";
}
