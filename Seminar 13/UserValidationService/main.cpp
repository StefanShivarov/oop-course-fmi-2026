#include "User.h"
#include "UsersSystem.h"
#include "UserValidationService.h"
#include "UsernameValidator.h"
#include "PasswordValidator.h"
#include "EmailValidator.h"
#include "AgeValidator.h"
#include "CustomUserExceptions.h"

#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <vector>

void printValidationErrors(const std::vector<std::string>& errors) {
    for (const std::string& error : errors) {
        std::cout << "- " << error << '\n';
    }
}

void tryAddUser(UsersSystem& system, const User& user) {
    try {
        system.addUser(user);
        std::cout << "Successfully added user: " << user.getUsername() << '\n';
    }
    catch (const ValidationFailedException& ex) {
        std::cout << ex.what() << '\n';
        printValidationErrors(ex.getValidationErrors());
    }
    catch (const UserAlreadyExistsException& ex) {
        std::cout << ex.what() << '\n';
    }
}

void tryRemoveUser(UsersSystem& system, const std::string& username) {
    try {
        system.removeUser(username);
        std::cout << "Successfully removed user: " << username << '\n';
    }
    catch (const UserNotFoundException& ex) {
        std::cout << ex.what() << '\n';
    }
}

void tryFindUser(const UsersSystem& system, const std::string& username) {
    std::optional<User> user = system[username];

    if (user.has_value()) {
        std::cout << "Found user:\n";
        std::cout << user.value();
    }
    else {
        std::cout << "User with username " << username << " was not found.\n";
    }
}

void printAllUsers(const UsersSystem& system) {
    const std::vector<User>& users = system.getUsers();

    if (users.empty()) {
        std::cout << "No users in the system.\n";
        return;
    }

    for (const User& user : users) {
        std::cout << user;
    }
}

int main() {
    auto validationService = std::make_shared<UserValidationService>();

    UsernameValidator usernameValidator = UsernameValidator::Builder()
            .required()
            .minLength(3)
            .maxLength(20)
            .requireLetter()
            .allowSpecialCharacters(false)
            .build();

    PasswordValidator passwordValidator = PasswordValidator::Builder()
            .required()
            .minLength(8)
            .requireLetter()
            .requireDigit()
            .requireSpecialCharacter(true)
            .build();

    EmailValidator emailValidator = EmailValidator::Builder()
            .required()
            .build();

    AgeValidator ageValidator = AgeValidator::Builder()
            .min(18)
            .max(120)
            .build();

    validationService->addValidator(usernameValidator);
    validationService->addValidator(passwordValidator);
    validationService->addValidator(emailValidator);
    validationService->addValidator(ageValidator);

    UsersSystem usersSystem(validationService);

    User validUser("john_doe", "john.doe@example.com", "Password1!", 25);
    User anotherValidUser("test123", "test123@test.bg", "StrongPass2@", 30);
    User invalidUser("ab!", "invalid-email", "pass", 15);

    std::cout << "=== Add valid user ===\n";
    tryAddUser(usersSystem, validUser);

    std::cout << "\n=== Add another valid user ===\n";
    tryAddUser(usersSystem, anotherValidUser);

    std::cout << "\n=== Add invalid user ===\n";
    tryAddUser(usersSystem, invalidUser);

    std::cout << "\n=== Add duplicate user ===\n";
    tryAddUser(usersSystem, validUser);

    std::cout << "\n=== Find existing user ===\n";
    tryFindUser(usersSystem, "john_doe");

    std::cout << "\n=== Find missing user ===\n";
    tryFindUser(usersSystem, "missing_user");

    std::cout << "\n=== Current users ===\n";
    printAllUsers(usersSystem);

    std::cout << "\n=== Remove existing user ===\n";
    tryRemoveUser(usersSystem, "john_doe");

    std::cout << "\n=== Remove same user again ===\n";
    tryRemoveUser(usersSystem, "john_doe");

    std::cout << "\n=== Final users ===\n";
    printAllUsers(usersSystem);
}
