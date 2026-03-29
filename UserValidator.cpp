#include "UserValidator.h"
#include <cstring>

UserValidator::UserValidator(
    bool hasMinUsernameLength,
    int minUsernameLength,
    bool hasMinPasswordLength,
    int minPasswordLength,
    bool hasMinAge,
    int minAge,
    bool requiresDigit,
    bool requiresUppercase
) 
    : hasMinUsernameLength(hasMinUsernameLength), 
    minUsernameLength(minUsernameLength),
    hasMinPasswordLength(hasMinPasswordLength),
    minPasswordLength(minPasswordLength),
    hasMinAge(hasMinAge),
    minAge(minAge),
    requiresDigit(requiresDigit),
    requiresUppercase(requiresUppercase)
{
}

bool UserValidator::operator()(const User& user) const
{
    if (hasMinUsernameLength && strlen(user.getUsername()) < minUsernameLength) {
        return false;
    }

    if (hasMinPasswordLength && strlen(user.getPassword()) < minPasswordLength) {
        return false;
    }

    if (hasMinAge && user.getAge() < minAge) {
        return false;
    }

    if (requiresDigit) {
        bool hasDigit = false;

        const char* pass = user.getPassword();

        for (size_t i = 0; pass[i] != '\0'; i++)
        {
            if (pass[i] >= '0' && pass[i] <= '9') {
                hasDigit = true;
                break;
            }
        }

        if (!hasDigit) {
            return false;
        }
    }

    if (requiresUppercase) {
        bool hasUpper = false;

        const char* pass = user.getPassword();

        for (size_t i = 0; pass[i] != '\0'; i++)
        {
            if (pass[i] >= 'A' && pass[i] <= 'Z') {
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

UserValidator::Builder UserValidator::builder()
{
    return Builder();
}

UserValidator::Builder& UserValidator::Builder::setMinUsernameLength(int length)
{
    minUsernameLength = length;
    hasMinUsernameLength = true;
    return *this;
}

UserValidator::Builder& UserValidator::Builder::setMinPasswordLength(int length)
{
    minPasswordLength = length;
    hasMinPasswordLength = true;
    return *this;
}

UserValidator::Builder& UserValidator::Builder::setMinAge(int age)
{
    minAge = age;
    hasMinAge = true;
    return *this;
}

UserValidator::Builder& UserValidator::Builder::requireDigit()
{
    requiresDigit = true;
    return *this;
}

UserValidator::Builder& UserValidator::Builder::requireUppercase()
{
    requiresUppercase = true;
    return *this;
}

UserValidator UserValidator::Builder::build() const
{
    return UserValidator(
        hasMinUsernameLength,
        minUsernameLength,
        hasMinPasswordLength,
        minPasswordLength,
        hasMinAge,
        minAge,
        requiresDigit,
        requiresUppercase
    );
}
