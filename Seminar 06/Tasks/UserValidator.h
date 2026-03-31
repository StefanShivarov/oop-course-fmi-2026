#pragma once
#include "User.h"

class UserValidator {
public:
    class Builder;

private:
    bool useMinUsernameLen;
    bool useMinPasswordLen;
    bool useMinAge;
    bool useRequireDigit;
    bool useRequireUpper;

    int minUsernameLen;
    int minPasswordLen;
    int minAge;

    UserValidator( bool useMinUsernameLen, int minUsernameLen, bool useMinPasswordLen, int minPasswordLen, 
        bool useMinAge, int minAge, bool useRequireDigit, bool useRequireUpper );

public:
    UserValidator(const UserValidator& other) = default;
    UserValidator& operator=(const UserValidator& other) = default;
    ~UserValidator() = default;

    bool operator()(const User& user) const;

    static Builder builder();
};

class UserValidator::Builder {
private:
    bool useMinUsernameLen = false;
    bool useMinPasswordLen = false;
    bool useMinAge = false;
    bool useRequireDigit = false;
    bool useRequireUpper = false;
    int minUsernameLen = 0;
    int minPasswordLen = 0;
    int minAge = 0;

public:
    Builder() = default;
 
    ~Builder() = default;

    Builder& withMinUsernameLen(int len);
    Builder& withMinPasswordLen(int len);
    Builder& withMinAge(int age);
    Builder& withRequireDigit();
    Builder& withRequireUpper();

    UserValidator build() const;
};