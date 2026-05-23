#include "UserValidationService.h"

void UserValidationService::copyFrom(const UserValidationService& other) {
    std::vector<std::unique_ptr<UserValidator>> copiedValidators;
    copiedValidators.reserve(other.validators.size());

    for (const std::unique_ptr<UserValidator>& validator : other.validators) {
        copiedValidators.push_back(validator->clone());
    }

    validators = std::move(copiedValidators);
}

UserValidationService::UserValidationService(const UserValidationService& other) {
    copyFrom(other);
}

UserValidationService& UserValidationService::operator=(const UserValidationService& other) {
    if (this != &other) {
        copyFrom(other);
    }
    return *this;
}

void UserValidationService::addValidator(const UserValidator& validator) {
    validators.push_back(validator.clone());
}

std::vector<std::string> UserValidationService::validate(const User& user) const {
    std::vector<std::string> allErrors;
    for (const auto& validator : validators) {
        std::vector<std::string> errors = validator->validate(user);
        if (!errors.empty()) {
            allErrors.insert(allErrors.end(), errors.begin(), errors.end());
        }
    }
    return allErrors;
}
