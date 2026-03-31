#include "UserValidator.h"
#include <cstring>
#pragma warning(disable:4996)

UserValidator::UserValidator(
    bool useMinNameLen, size_t minNameLen,
    bool useMinPassLen, size_t minPassLen,
    bool useMinAge,     size_t minAge,
    bool requireDigit,  
    bool requireCapitalLetter

)   : useMinNameLen(useMinNameLen), minNameLen(minNameLen),
    useMinPassLen(useMinPassLen),   minPassLen(minPassLen),
    useMinAge(useMinAge),           minAge(minAge),
    requireDigit(requireDigit), 
    requireCapitalLetter(requireCapitalLetter)
{
}

bool UserValidator::operator()(const User& user) const
{
    if (!user.getName() || !user.getPassword()) return false;

	if (useMinNameLen && (strlen(user.getName()) < minNameLen)) {
		return false;
	}

	if (useMinPassLen && (strlen(user.getPassword()) < minPassLen)) {
		return false;
	}

	if (useMinAge && user.getAge() < minAge) {
		return false;
	}

    if (requireDigit) {
        const char* pass = user.getPassword();

        if (!pass) return false;

        bool hasDigit = false;
        for (size_t i = 0; pass[i] != '\0'; i++) {
            if (pass[i] >= '0' && pass[i] <= '9') {
                hasDigit = true;
                break;
            }
        }

        if (!hasDigit) return false;
    }

    if (requireCapitalLetter) {
        const char* pass = user.getPassword();

        if (!pass) return false;

        bool hasCapital = false;
        for (size_t i = 0; pass[i] != '\0'; i++) {
            if (pass[i] >= 'A' && pass[i] <= 'Z') {
                hasCapital = true;
                break;
            }
        }

        if (!hasCapital) return false;
    }

    return true;
}

UserValidator::Builder UserValidator::builder() {
    return Builder();
}

UserValidator::Builder& UserValidator::Builder::withMinNameLen(size_t len) {
    useMinNameLen = true;
    minNameLen = len;
    return *this;
}

UserValidator::Builder& UserValidator::Builder::withMinPassLength(size_t len) {
    useMinPassLen = true;
    minPassLen = len;
    return *this;
}

UserValidator::Builder& UserValidator::Builder::withMinAge(size_t age) {
    useMinAge = true;
    minAge = age;
    return *this;
}

UserValidator::Builder& UserValidator::Builder::withRequireDigit() {
    requireDigit = true;
    return *this;
}

UserValidator::Builder& UserValidator::Builder::withRequireCapitalLetter() {
    requireCapitalLetter = true;
    return *this;
}

UserValidator UserValidator::Builder::build() const {
    return UserValidator(
        useMinNameLen, minNameLen,
        useMinPassLen, minPassLen,
        useMinAge, minAge,
        requireDigit, requireCapitalLetter
    );
}