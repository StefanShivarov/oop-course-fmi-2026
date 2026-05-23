#include "StringPropertyValidator.h"
#include <format>

StringPropertyValidator::StringPropertyValidator(
    bool required,
    std::optional<size_t> minLength,
    std::optional<size_t> maxLength,
    bool digitRequired,
    bool letterRequired
) : required(required), minLength(minLength), maxLength(maxLength), digitRequired(digitRequired),
    letterRequired(letterRequired) {}

void StringPropertyValidator::validateCommonStringRules(
    const std::string& value,
    const std::string& field,
    std::vector<std::string>& errors
) const {
    if (value.empty()) {
        if (required) {
            errors.push_back(std::format("{} is required.", field));
        }
        return;
    }

    if (minLength.has_value() && value.length() < minLength.value()) {
        errors.push_back(std::format("{} is too short. Expected at least {} symbols.", field, minLength.value()));
    }

    if (maxLength.has_value() && value.length() > maxLength.value()) {
        errors.push_back(std::format("{} is too long. Expected no more than {} symbols.", field, maxLength.value()));
    }

    if (digitRequired && std::ranges::none_of(value, isdigit)) {
        errors.push_back(std::format("{} must contain at least one digit.", field));
    }

    if (letterRequired && std::ranges::none_of(value, isalpha)) {
        errors.push_back(std::format("{} must contain at least one letter.", field));
    }
}
