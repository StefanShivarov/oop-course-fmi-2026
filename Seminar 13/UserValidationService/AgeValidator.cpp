#include "AgeValidator.h"
#include <format>

AgeValidator::AgeValidator(std::optional<size_t> minValue, std::optional<size_t> maxValue) {
    if (minValue.has_value() && maxValue.has_value() && minValue.value() > maxValue.value()) {
        minValue.reset();
        maxValue.reset();
    }

    this->minValue = minValue;
    this->maxValue = maxValue;
}

std::unique_ptr<UserValidator> AgeValidator::clone() const {
    return std::make_unique<AgeValidator>(*this);
}

std::vector<std::string> AgeValidator::validate(const User& user) const {
    std::vector<std::string> errors;
    if (minValue.has_value() && user.getAge() < minValue.value()) {
        errors.push_back(std::format("Age must be at least {}.", minValue.value()));
    }

    if (maxValue.has_value() && user.getAge() > maxValue.value()) {
        errors.push_back(std::format("Age must not be higher than {}.", maxValue.value()));
    }

    return errors;
}

AgeValidator::Builder& AgeValidator::Builder::min(size_t value) {
    this->minVal = value;
    return *this;
}

AgeValidator::Builder& AgeValidator::Builder::max(size_t value) {
    this->maxVal = value;
    return *this;
}

AgeValidator AgeValidator::Builder::build() const {
    return AgeValidator(minVal, maxVal);
}
