#pragma once
#include "User.h"
#include <vector>

class UserValidator {
public:
    virtual ~UserValidator() = default;

    virtual std::vector<std::string> validate(const User& user) const = 0;

    virtual std::unique_ptr<UserValidator> clone() const = 0;
};
