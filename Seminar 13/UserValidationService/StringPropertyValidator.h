#pragma once
#include "UserValidator.h"
#include <optional>

class StringPropertyValidator : public UserValidator {
protected:
    StringPropertyValidator(
        bool required,
        std::optional<size_t> minLength,
        std::optional<size_t> maxLength,
        bool digitRequired,
        bool letterRequired
    );

    void validateCommonStringRules(
        const std::string& value,
        const std::string& field,
        std::vector<std::string>& errors
    ) const;

private:
    bool required;
    std::optional<size_t> minLength;
    std::optional<size_t> maxLength;
    bool digitRequired;
    bool letterRequired;
};
