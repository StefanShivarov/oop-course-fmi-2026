#include "CustomUserExceptions.h"

ValidationFailedException::ValidationFailedException(const std::string& message, const std::vector<std::string>& validationErrors)
    : std::runtime_error(message), validationErrors(validationErrors) {
}

const std::vector<std::string>& ValidationFailedException::getValidationErrors() const {
    return validationErrors;
}

UserAlreadyExistsException::UserAlreadyExistsException(const std::string& message) : std::runtime_error(message) {
}

UserNotFoundException::UserNotFoundException(const std::string& message) : std::runtime_error(message) {
}
