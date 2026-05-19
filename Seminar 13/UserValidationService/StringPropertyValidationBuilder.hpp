#pragma once
#include <optional>

template <class DerivedBuilder>
class StringPropertyValidatorBuilderBase {
protected:
    bool requiredValue = false;
    std::optional<size_t> minLengthValue;
    std::optional<size_t> maxLengthValue;
    bool digitRequiredValue = false;
    bool letterRequiredValue = false;

public:
    DerivedBuilder& required(bool value = true) {
        requiredValue = value;
        return self();
    }

    DerivedBuilder& minLength(size_t value) {
        minLengthValue = value;
        return self();
    }

    DerivedBuilder& maxLength(size_t value) {
        maxLengthValue = value;
        return self();
    }

    DerivedBuilder& requireDigit(bool value = true) {
        digitRequiredValue = value;
        return self();
    }

    DerivedBuilder& requireLetter(bool value = true) {
        letterRequiredValue = value;
        return self();
    }

private:
    DerivedBuilder& self() {
        return static_cast<DerivedBuilder&>(*this);
    }
};
