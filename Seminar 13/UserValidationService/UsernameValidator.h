#pragma once
#include "StringPropertyValidator.h"
#include "StringPropertyValidationBuilder.hpp"

class UsernameValidator : public StringPropertyValidator {
public:
    std::vector<std::string> validate(const User& user) const override;
    std::unique_ptr<UserValidator> clone() const override;

    class Builder : public StringPropertyValidatorBuilderBase<UsernameValidator::Builder> {
    public:
        Builder& allowSpecialCharacters(bool value = true);
        UsernameValidator build() const;

    private:
        bool specialCharactersAllowed = true;

    };

private:
    bool specialCharactersAllowed;

    UsernameValidator(bool required,
        std::optional<size_t> minLength,
        std::optional<size_t> maxLength,
        bool digitRequired,
        bool letterRequired,
        bool specialCharactersAllowed
    );
};
