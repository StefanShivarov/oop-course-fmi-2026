#pragma once
#include <vector>
#include <memory>
#include "UserValidator.h"

class UserValidationService {
public:
    UserValidationService() = default;

    UserValidationService(const UserValidationService& other);
    UserValidationService& operator=(const UserValidationService& other);

    UserValidationService(UserValidationService&& other) noexcept = default;
    UserValidationService& operator=(UserValidationService&& other) noexcept = default;

    void addValidator(const UserValidator& validator);

    std::vector<std::string> validate(const User& user) const;

private:
    std::vector<std::unique_ptr<UserValidator>> validators;

    // defining the copy operations is optional,
    // only if we want the validation services to be copiable
    // here we can do it just for learning purposes
    void copyFrom(const UserValidationService& other);
};
