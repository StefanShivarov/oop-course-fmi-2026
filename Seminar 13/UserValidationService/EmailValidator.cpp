#include "EmailValidator.h"

EmailValidator::EmailValidator(
    bool required,
    std::optional<size_t> minLength,
    std::optional<size_t> maxLength,
    bool digitRequired,
    bool letterRequired
) : StringPropertyValidator(required, minLength, maxLength, digitRequired, letterRequired) {}


std::unique_ptr<UserValidator> EmailValidator::clone() const {
    return std::make_unique<EmailValidator>(*this);
}

EmailValidator EmailValidator::Builder::build() const {
    return EmailValidator(
        requiredValue,
        minLengthValue,
        maxLengthValue,
        digitRequiredValue,
        letterRequiredValue
    );
}

bool EmailValidator::containsOnlyLetters(const std::string& s) {
    return !s.empty() && std::ranges::all_of(s, [](char c) {
        return isalpha(c);
    });
}

bool EmailValidator::isValidLocalPart(const std::string& localPart) {
    if (localPart.empty()) {
        return false;
    }

    if (localPart.front() == '.' || localPart.back() == '.') {
        return false;
    }

    bool previousWasDot = false;

    for (char ch : localPart) {
        if (ch == '.') {
            if (previousWasDot) {
                return false;
            }

            previousWasDot = true;
        }
        else {
            if (!isalnum(ch)) {
                return false;
            }

            previousWasDot = false;
        }
    }

    return true;
}

bool EmailValidator::isValidEmailFormat(const std::string& email) {
    auto atCount = std::ranges::count(email, '@');
    if (atCount != 1) {
        return false;
    }

    size_t atPosition = email.find('@');

    std::string localPart = email.substr(0, atPosition);
    std::string domainAndExtension = email.substr(atPosition + 1);

    std::size_t dotPosition = domainAndExtension.find('.');

    if (dotPosition == std::string::npos) {
        return false;
    }

    if (domainAndExtension.find('.', dotPosition + 1) != std::string::npos) {
        return false;
    }

    std::string domain = domainAndExtension.substr(0, dotPosition);
    std::string extension = domainAndExtension.substr(dotPosition + 1);

    return isValidLocalPart(localPart) &&
        containsOnlyLetters(domain) &&
        containsOnlyLetters(extension);
}

std::vector<std::string> EmailValidator::validate(const User& user) const {
    std::vector<std::string> errors;
    validateCommonStringRules(user.getEmail(), "Email", errors);

    if (!isValidEmailFormat(user.getEmail())) {
        errors.emplace_back("Email must be in format: ^[A-Za-z0-9]+(\\.[A-Za-z0-9]+)*@[A-Za-z]+\\.[A-Za-z]+$");
    }

    return errors;
}
