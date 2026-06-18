#include "User.h"
#include <cstring>
#include "UserValidator.h"


User::User(const char *username, const char *password, const int age) : age(age) {
    this -> username = new char[strlen(username) + 1];
    strcpy(this -> username, username);
    this -> password = new char[strlen(password) + 1];
    strcpy(this -> password, password);
}
User::User(const User &other) : age(other.age) {
    this -> username = new char[strlen(other.username) + 1];
    strcpy(this -> username, other.username);
    this -> password = new char[strlen(other.password) + 1];
    strcpy(this -> password, other.password);
}
User& User::operator=(const User &other) {
    if (this != &other) {
        delete [] this -> username;
        delete [] this->password;
        this -> username = new char[strlen(other.username) + 1];
        strcpy(this -> username, other.username);
        this -> password = new char[strlen(other.password) + 1];
        strcpy(this -> password, other.password);
        this -> age = other.age;
    }
    return *this;
}
User::~User() {
    delete[] this -> username;
    delete[] this -> password;
}
const char * User::getUsername() const {
    return this -> username;
}
const char * User::getPassword() const {
    return this -> password;
}
int User::getAge() const {
    return this -> age;
}
User::UserValidator User::validator() {
    return {};
}