#include "UserValidator.h"
#include <cstring>
#include <cctype>

UserValidator::UserValidator( bool useMinUsernameLen, int minUsernameLen, bool useMinPasswordLen, int minPasswordLen,
    bool useMinAge, int minAge, bool useRequireDigit,bool useRequireUpper) : useMinUsernameLen(useMinUsernameLen), minUsernameLen(minUsernameLen),
    useMinPasswordLen(useMinPasswordLen), minPasswordLen(minPasswordLen), useMinAge(useMinAge), minAge(minAge),
    useRequireDigit(useRequireDigit),  useRequireUpper(useRequireUpper) { }

bool UserValidator::operator()(const User& user) const {

    if (useMinUsernameLen && (int)strlen(user.getUsername()) < minUsernameLen) 
    {
        return false;
    }

    if (useMinPasswordLen && (int)strlen(user.getPassword()) < minPasswordLen) 
    {
        return false;
    }

    if (useMinAge && user.getAge() < minAge) 
    {
        return false;
    }

    if (useRequireDigit) 
    {
        bool hasDigit = false;
        for (const char* p = user.getPassword(); *p!='\0'; p++) 
        {
            if (isdigit((char)*p)) {
                hasDigit = true;
                break;
            }
        }
        if (!hasDigit) return false;
    }

    if (useRequireUpper) {
        bool hasUpper = false;
        for (const char* p = user.getPassword(); *p!='\0'; p++) 
        {
            if (isupper((char)*p)) 
            {
                hasUpper = true; 
                break; 
            }
        }
        if (!hasUpper) return false;
    }

    return true;
}

UserValidator::Builder UserValidator::builder() {
    return Builder();
}


UserValidator::Builder& UserValidator::Builder::withMinUsernameLen(int len) {
    minUsernameLen = len;
    useMinUsernameLen = true;
    return *this;
}

UserValidator::Builder& UserValidator::Builder::withMinPasswordLen(int len) {
    minPasswordLen = len;
    useMinPasswordLen = true;
    return *this;
}

UserValidator::Builder& UserValidator::Builder::withMinAge(int age) {
    minAge = age;
    useMinAge = true;
    return *this;
}

UserValidator::Builder& UserValidator::Builder::withRequireDigit() {
    useRequireDigit = true;
    return *this;
}

UserValidator::Builder& UserValidator::Builder::withRequireUpper() {
    useRequireUpper = true;
    return *this;
}

UserValidator UserValidator::Builder::build() const {
    return UserValidator(useMinUsernameLen, minUsernameLen, useMinPasswordLen,
        minPasswordLen, useMinAge, minAge, useRequireDigit, useRequireUpper);
}