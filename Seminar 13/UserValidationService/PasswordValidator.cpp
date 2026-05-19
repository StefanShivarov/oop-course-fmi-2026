#include "PasswordValidator.h"

PasswordValidator::PasswordValidator(
    bool required,
    std::optional<size_t> minLength,
    std::optional<size_t> maxLength,
    bool digitRequired,
    bool letterRequired,
    bool specialCharacterRequired
) : StringPropertyValidator(required, minLength, maxLength, digitRequired, letterRequired)
    , specialCharacterRequired(specialCharacterRequired) {}

std::unique_ptr<UserValidator> PasswordValidator::clone() const {
    return std::make_unique<PasswordValidator>(*this);
}

std::vector<std::string> PasswordValidator::validate(const User& user) const {
    std::vector<std::string> errors;
    validateCommonStringRules(user.password, "Password", errors);

    if (specialCharacterRequired && std::ranges::none_of(user.password,
        [](char c) { return !isalnum(c) && !isspace(c) && c != '_'; })) {
        errors.emplace_back("Password must contain at least one special symbol.");
    }

    return errors;
}

PasswordValidator::Builder& PasswordValidator::Builder::requireSpecialCharacter(bool value) {
    specialCharacterRequiredValue = value;
    return *this;
}

PasswordValidator PasswordValidator::Builder::build() const {
    return PasswordValidator(
        requiredValue,
        minLengthValue,
        maxLengthValue,
        digitRequiredValue,
        letterRequiredValue,
        specialCharacterRequiredValue
    );
}
