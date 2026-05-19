#include "UsersSystem.h"
#include <format>
#include <iostream>
#include "CustomUserExceptions.h"

UsersSystem::UsersSystem(const std::shared_ptr<const UserValidationService>& validationService) : validationService(validationService) {
}

const std::vector<User>& UsersSystem::getUsers() const {
    return users;
}

std::optional<User> UsersSystem::operator[](const std::string& username) const {
    auto it = std::ranges::find_if(users, [&username](const User& user) {
        return user.getUsername() == username;
    });

    if (it == users.end()) {
        return std::nullopt;
    }

    return *it;
}

void UsersSystem::addUser(const User& user) {
    if (this->operator[](user.getUsername()).has_value()) {
        throw UserAlreadyExistsException(std::format("User with username {} already exists.", user.getUsername()));
    }
    std::vector<std::string> errors = validationService->validate(user);
    if (!errors.empty()) {
        throw ValidationFailedException("User validation failed!", errors);
    }
    users.push_back(user);
}

void UsersSystem::removeUser(const std::string& username) {
    auto it = std::ranges::find_if(users, [&username](const User& user) {
        return user.getUsername() == username;
    });

    if (it == users.end()) {
        throw UserNotFoundException(std::format("User with username {} not found", username));
    }

    users.erase(it);
}
