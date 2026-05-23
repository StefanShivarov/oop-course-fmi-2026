#pragma once
#include "UserValidator.h"
#include <optional>

class AgeValidator : public UserValidator {
public:
    std::vector<std::string> validate(const User& user) const override;
    std::unique_ptr<UserValidator> clone() const override;

    class Builder {
    public:
        Builder& min(size_t value);
        Builder& max(size_t value);

        AgeValidator build() const;

    private:
        std::optional<size_t> minVal;
        std::optional<size_t> maxVal;
    };

private:
    AgeValidator(
        std::optional<size_t> minValue,
        std::optional<size_t> maxValue
    );

    std::optional<size_t> minValue;
    std::optional<size_t> maxValue;
};
