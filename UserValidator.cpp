#include "UserValidator.h"
#include <cstring>
#pragma warning(disable:4996)
bool myIsDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

bool myIsUpper(char ch) {
    return ch >= 'A' && ch <= 'Z';
}
void UserValidator::copyFrom(const UserValidator& other) {
    minUserLenght = other.minUserLenght;
    minPassLenght = other.minPassLenght;
    minAgeok = other.minAgeok;
    hasNumber = other.hasNumber;
    hasCapital = other.hasCapital;

    minUsernameLenght = other.minUsernameLenght;
    minPasswordLenght = other.minPasswordLenght;
    minAge = other.minAge;
    needNumber = other.needNumber;
    needCapital = other.needCapital;
}

void UserValidator::free() {
    // няма динамична памет
}

UserValidator::UserValidator(
    bool minUserLenght,
    int minUsernameLenght,
    bool minPassLenght,
    int minPasswordLenght,
    bool minAgeok,
    int minAge,
    bool hasNumber,
    bool needNumber,
    bool hasCapital,
    bool needCapital
)
    : minUserLenght(minUserLenght),
    minUsernameLenght(minUsernameLenght),
    minPassLenght(minPassLenght),
    minPasswordLenght(minPasswordLenght),
    minAgeok(minAgeok),
    minAge(minAge),
    hasNumber(hasNumber),
    needNumber(needNumber),
    hasCapital(hasCapital),
    needCapital(needCapital) {
}

UserValidator::UserValidator(const UserValidator& other) {
    copyFrom(other);
}

UserValidator& UserValidator::operator=(const UserValidator& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

UserValidator::~UserValidator() {
    free();
}

bool UserValidator::operator()(const User& user) const {
    if (minUserLenght && strlen(user.getUserName()) < minUsernameLenght) {
        return false;
    }

    if (minPassLenght && strlen(user.getPassword()) < minPasswordLenght) {
        return false;
    }

    if (minAgeok && user.getAge() < minAge) {
        return false;
    }

    if (hasNumber && needNumber) {
        bool found = false;
        const char* pass = user.getPassword();
        for (size_t i = 0; i < strlen(pass); i++) {
            if (myIsDigit(pass[i])) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }

    if (hasCapital && needCapital) {
        bool found = false;
        const char* pass = user.getPassword();
        for (size_t i = 0; i < strlen(pass); i++) {
            if (myIsUpper(pass[i])) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }

    return true;
}

UserValidator::Builder UserValidator::builder() {
    return Builder();
}

// ===== Builder =====

UserValidator::Builder::Builder() = default;

UserValidator::Builder::~Builder() = default;

UserValidator::Builder& UserValidator::Builder::withUsernameLeght(int minUsernameLenght) {
    this->minUsernameLenght = minUsernameLenght;
    minUserLenght = true;
    return *this;
}

UserValidator::Builder& UserValidator::Builder::withPasswordLeght(int minPasswordLenght) {
    this->minPasswordLenght = minPasswordLenght;
    minPassLenght = true;
    return *this;
}

UserValidator::Builder& UserValidator::Builder::withMinAge(int minAge) {
    this->minAge = minAge;
    minAgeok = true;
    return *this;
}

UserValidator::Builder& UserValidator::Builder::withNumber(bool needNumber) {
    this->needNumber = needNumber;
    hasNumber = true;
    return *this;
}

UserValidator::Builder& UserValidator::Builder::withCapital(bool needCapital) {
    this->needCapital = needCapital;
    hasCapital = true;
    return *this;
}

UserValidator UserValidator::Builder::build() const {
    return UserValidator(
        minUserLenght,
        minUsernameLenght,
        minPassLenght,
        minPasswordLenght,
        minAgeok,
        minAge,
        hasNumber,
        needNumber,
        hasCapital,
        needCapital
    );
}