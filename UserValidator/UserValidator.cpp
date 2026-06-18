#include <iostream>
#include "UserValidator.h"
using namespace std;

User::UserValidator & User::UserValidator::withMinLenUsername(const int len) {
    minUsernameLen = len;
    return *this;
}
User::UserValidator & User::UserValidator::withMinLenPass(const int len) {
    minPasswordLen = len;
    return *this;
}
User::UserValidator & User::UserValidator::withMinAge(const int a) {
    minAge = a;
    return *this;
}
User::UserValidator & User::UserValidator::withDigit() {
    requireDigit = true;
    return *this;
}
User::UserValidator & User::UserValidator::withUppercase() {
    requireUppercase = true;
    return *this;
}
bool User::UserValidator::operator()(const User &u) const {
    if (strlen(u.getUsername()) < minUsernameLen) {
        return false;
    }
    if (strlen(u.getPassword()) < minPasswordLen) {
        return false;
    }
    if (u.getAge() < minAge) {
        return false;
    }
    if (requireDigit) {
        bool hasDigit = false;
        const char* pass = u.getPassword();
        for (int i = 0; pass[i]; i++) {
            if (isdigit(pass[i])) {
                hasDigit = true;
                break;
            }
        }
        if (!hasDigit) {
            return false;
        }
    }
    if (requireUppercase) {
        bool hasUpper = false;
        const char* pass = u.getPassword();
        for (int i = 0; pass[i]; i++) {
            if (isupper(pass[i])) {
                hasUpper = true;
                break;
            }
        }
        if (!hasUpper) {
            return false;
        }
    }
    return true;
}