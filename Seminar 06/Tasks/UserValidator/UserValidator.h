#pragma once
#include <iostream>
#include "User.h"

class UserValidator {
public:
    class Builder;

private:
    bool useMinUsernameLength;
    bool useMinPasswordLength;
    bool useMinAge;
    bool requireDigit;
    bool requireUppercase;

    size_t minUsernameLength;
    size_t minPasswordLength;
    size_t minAge;

    static bool containsDigit(const char* str);
    static bool containsUppercase(const char* str);

    bool validateUsernameLength(const User& user) const;
    bool validatePasswordLength(const User& user) const;
    bool validateAge(const User& user) const;
    bool validatePasswordDigit(const User& user) const;
    bool validatePasswordUppercase(const User& user) const;

    UserValidator(
        bool useMinUsernameLength,
        int minUsernameLength,
        bool useMinPasswordLength,
        int minPasswordLength,
        bool useMinAge,
        int minAge,
        bool requireDigit,
        bool requireUppercase
    );

public:
    bool operator()(const User& user) const;

    static Builder builder();
};

class UserValidator::Builder {
private:
    bool useMinUsernameLength = false;
    bool useMinPasswordLength = false;
    bool useMinAge = false;
    bool requireDigit = false;
    bool requireUppercase = false;

    int minUsernameLength = 0;
    int minPasswordLength = 0;
    int minAge = 0;

public:
    Builder() = default;

    Builder& withMinUsernameLength(int minUsernameLength);
    Builder& withMinPasswordLength(int minPasswordLength);
    Builder& withMinAge(int minAge);
    Builder& requireDigitInPassword();
    Builder& requireUppercaseInPassword();

    UserValidator build() const;
};
