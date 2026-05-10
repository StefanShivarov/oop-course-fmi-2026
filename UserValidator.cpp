#include "UserValidator.h"

UserValidator::Builder& UserValidator::Builder::withMinNameLength(unsigned minNameLength) {
    usesMinNameLength = true;
    this->minNameLength = minNameLength;
    return *this;
}

UserValidator::Builder& UserValidator::Builder::withMinPasswordLength(unsigned minPasswordLength) {
    usesMinPasswordLength = true;
    this->minPasswordLength = minPasswordLength;
    return *this;
}

UserValidator::Builder& UserValidator::Builder::withMinAge(unsigned minAge) {
    usesMinAge = true;
    this->minAge = minAge;
    return *this;
}

UserValidator::Builder& UserValidator::Builder::withPasswordContainsDigit() {
    usesPasswordContainsDigit = true;
    return *this;
}

UserValidator::Builder& UserValidator::Builder::withPasswordContainsCapital() {
    usesPasswordContainsCapital = true;
    return *this;
}

UserValidator UserValidator::Builder::build() const {
    return UserValidator(
        usesMinNameLength,
        minNameLength,
        usesMinPasswordLength,
        minPasswordLength,
        usesMinAge,
        minAge,
        usesPasswordContainsDigit,
        usesPasswordContainsCapital
    );
}

bool UserValidator::operator()(const User& user)
{
    if (usesMinNameLength && !validateMinNameLength(user)) {
        return false;
    }

    if (usesMinPasswordLength && !validateMinPasswordLength(user)) {
        return false;
    }

    if (usesMinAge && !validateMinAge(user)) {
        return false;
    }

    if (usesPasswordContainsDigit && !validatePasswordContainsDigit(user)) {
        return false;
    }

    if (usesPassswordContainsCapital && !validatePassswordContainsCapital(user)) {
        return false;
    }

    return true;
}

bool UserValidator::validateMinNameLength(const User& user) const {
    return std::strlen(user.getUsername()) >= this->minNameLength;
}

bool UserValidator::validateMinPasswordLength(const User& user) const {
    return std::strlen(user.getPassword()) >= this->minPasswordLength;
}

bool UserValidator::validateMinAge(const User& user) const
{
    return user.getAge() >= this->minAge;
}

bool UserValidator::containsDigit(const char* str) const {
    while (*str) {
        if (*str >= '0' && *str <= '9') {
            return true;
        }
        str++;
    }

    return false;
}

bool UserValidator::containsUppercase(const char* str) const {
    while (*str) {
        if (*str >= 'A' && *str <= 'Z') {
            return true;
        }
        str++;
    }

    return false;
}

bool UserValidator::validatePasswordContainsDigit(const User& user) const
{
    return containsDigit(user.getPassword());
}

bool UserValidator::validatePassswordContainsCapital(const User& user) const
{
    return containsUppercase(user.getPassword());
}

UserValidator::UserValidator(
    bool usesMinNameLength, unsigned minNameLength,
    bool usesMinPasswordLength, unsigned minPasswordLength,
    bool usesMinAge, unsigned minAge,
    bool usesPasswordContainsDigit, bool usesPassswordContainsCapital)
    : usesMinNameLength(usesMinNameLength),
    minNameLength(minNameLength),
    usesMinPasswordLength(usesMinPasswordLength),
    minPasswordLength(minPasswordLength),
    usesMinAge(usesMinAge),
    minAge(minAge),
    usesPasswordContainsDigit(usesPasswordContainsDigit),
    usesPassswordContainsCapital(usesPassswordContainsCapital) {};