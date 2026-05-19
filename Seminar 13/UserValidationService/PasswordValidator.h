#pragma once
#include "StringPropertyValidator.h"
#include "StringPropertyValidationBuilder.hpp"

class PasswordValidator : public StringPropertyValidator {
public:
    std::vector<std::string> validate(const User& user) const override;
    std::unique_ptr<UserValidator> clone() const override;

    class Builder : public StringPropertyValidatorBuilderBase<PasswordValidator::Builder> {
    public:
        Builder& requireSpecialCharacter(bool value = true);
        PasswordValidator build() const;

    private:
        bool specialCharacterRequiredValue = true;

    };

private:
    bool specialCharacterRequired;

    PasswordValidator(
        bool required,
        std::optional<size_t> minLength,
        std::optional<size_t> maxLength,
        bool digitRequired,
        bool letterRequired,
        bool specialCharacterRequired
    );

};
