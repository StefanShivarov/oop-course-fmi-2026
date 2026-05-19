#pragma once
#include <stdexcept>
#include <vector>
#include <string>

class ValidationFailedException : public std::runtime_error {
public:
    ValidationFailedException(const std::string& message, const std::vector<std::string>& validationErrors);
    using std::runtime_error::what;
    const std::vector<std::string>& getValidationErrors() const;

private:
    std::vector<std::string> validationErrors;
};

class UserAlreadyExistsException : public std::runtime_error {
public:
    explicit UserAlreadyExistsException(const std::string& message);
    using std::runtime_error::what;
};

class UserNotFoundException : public std::runtime_error {
public:
    explicit UserNotFoundException(const std::string& message);
    using std::runtime_error::what;
};
