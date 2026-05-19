#pragma once
#include <vector>
#include <string>
#include <optional>
#include <memory>
#include "User.h"
#include "UserValidationService.h"

class UsersSystem {
public:
    explicit UsersSystem(const std::shared_ptr<const UserValidationService>& validationService);

    const std::vector<User>& getUsers() const;
    std::optional<User> operator[](const std::string& username) const;

    void addUser(const User& user);
    void removeUser(const std::string& username);

private:
    std::vector<User> users;
    std::shared_ptr<const UserValidationService> validationService;
};
