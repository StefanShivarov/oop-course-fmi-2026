#pragma once
#include "StringPropertyValidator.h"
#include "StringPropertyValidationBuilder.hpp"

class EmailValidator : public StringPropertyValidator {
public:
    std::vector<std::string> validate(const User& user) const override;
    std::unique_ptr<UserValidator> clone() const override;

    class Builder: public StringPropertyValidatorBuilderBase<EmailValidator::Builder> {
    public:
        EmailValidator build() const;
    };

private:
    EmailValidator(
        bool required,
        std::optional<size_t> minLength,
        std::optional<size_t> maxLength,
        bool digitRequired,
        bool letterRequired
    );

    static bool containsOnlyLetters(const std::string& s);
    static bool isValidLocalPart(const std::string& s);
    static bool isValidEmailFormat(const std::string& s);
};
