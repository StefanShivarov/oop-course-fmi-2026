#include "UserValidator.h"
#include <cstring>
#include <print>
#pragma warning(disable:4996)

using std::println;

UserValidator::UserValidator(
    bool useMinUsernameLength,
    int minUsernameLength,
    bool useMinPasswordLength,
    int minPasswordLength,
    bool useMinAge,
    int minAge,
    bool requireDigit,
    bool requireUppercase
)
    : useMinUsernameLength(useMinUsernameLength),
      useMinPasswordLength(useMinPasswordLength),
      useMinAge(useMinAge),
      requireDigit(requireDigit),
      requireUppercase(requireUppercase),
      minUsernameLength(minUsernameLength),
      minPasswordLength(minPasswordLength),
      minAge(minAge) {}

bool UserValidator::containsDigit(const char* str) {
    while (*str) {
        if (*str >= '0' && *str <= '9') {
            return true;
        }
        str++;
    }

    return false;
}

bool UserValidator::containsUppercase(const char* str) {
    while (*str) {
        if (*str >= 'A' && *str <= 'Z') {
            return true;
        }
        str++;
    }

    return false;
}

bool UserValidator::validateUsernameLength(const User& user) const {
    if (!useMinUsernameLength) {
        return true;
    }

    if (strlen(user.getUsername()) < minUsernameLength) {
        println("Validation failed: username must be at least {} symbols long", minUsernameLength);
        return false;
    }

    return true;
}

bool UserValidator::validatePasswordLength(const User& user) const {
    if (!useMinPasswordLength) {
        return true;
    }

    if (strlen(user.getPassword()) < minPasswordLength) {
        println("Validation failed: password must be at least {} symbols long", minPasswordLength);
        return false;
    }

    return true;
}

bool UserValidator::validateAge(const User& user) const {
    if (!useMinAge) {
        return true;
    }

    if (user.getAge() < minAge) {
        println("Validation failed: age must be at least {}", minAge);
        return false;
    }

    return true;
}

bool UserValidator::validatePasswordDigit(const User& user) const {
    if (!requireDigit) {
        return true;
    }

    if (!containsDigit(user.getPassword())) {
        println("Validation failed: password must contain at least one digit");
        return false;
    }

    return true;
}

bool UserValidator::validatePasswordUppercase(const User& user) const {
    if (!requireUppercase) {
        return true;
    }

    if (!containsUppercase(user.getPassword())) {
        println("Validation failed: password must contain at least one uppercase letter");
        return false;
    }

    return true;
}

bool UserValidator::operator()(const User& user) const {
    // by passing through all validations, we can see all the invalid values of the user
    bool isValid = true;

    if (!validateUsernameLength(user)) {
        isValid = false;
    }

    if (!validatePasswordLength(user)) {
        isValid = false;
    }

    if (!validateAge(user)) {
        isValid = false;
    }

    if (!validatePasswordDigit(user)) {
        isValid = false;
    }

    if (!validatePasswordUppercase(user)) {
        isValid = false;
    }

    return isValid;
}

UserValidator::Builder UserValidator::builder() {
    return Builder();
}

UserValidator::Builder& UserValidator::Builder::withMinUsernameLength(int minUsernameLength) {
    this->minUsernameLength = minUsernameLength;
    useMinUsernameLength = true;
    return *this;
}

UserValidator::Builder& UserValidator::Builder::withMinPasswordLength(int minPasswordLength) {
    this->minPasswordLength = minPasswordLength;
    useMinPasswordLength = true;
    return *this;
}

UserValidator::Builder& UserValidator::Builder::withMinAge(int minAge) {
    this->minAge = minAge;
    useMinAge = true;
    return *this;
}

UserValidator::Builder& UserValidator::Builder::requireDigitInPassword() {
    requireDigit = true;
    return *this;
}

UserValidator::Builder& UserValidator::Builder::requireUppercaseInPassword() {
    requireUppercase = true;
    return *this;
}

UserValidator UserValidator::Builder::build() const {
    return UserValidator(
        useMinUsernameLength,
        minUsernameLength,
        useMinPasswordLength,
        minPasswordLength,
        useMinAge,
        minAge,
        requireDigit,
        requireUppercase
    );
}
