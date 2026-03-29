#include <iostream>
#include "User.h"
#include "UserValidator.h"

void validateUsers(const User* users, size_t count, const UserValidator& validator)
{
    for (size_t i = 0; i < count; i++)
    {
        if (validator(users[i]))
        {
            std::cout << users[i] << std::endl;
        }
    }
}

int main()
{
    User u1("ivan123", "pass123", 20);
    User u2("maria", "hello", 17);
    User u3("georgi", "Password1", 25);
    User u4("ani", "abc", 30);
    User u5("petar", "qwerty9", 19);

    User users[] = { u1, u2, u3, u4, u5 };
    size_t usersCount = sizeof(users) / sizeof(users[0]);


    UserValidator validator = UserValidator::builder()
        .setMinUsernameLength(5)
        .setMinPasswordLength(6)
        .setMinAge(18)
        .requireDigit()
        .requireUppercase()
        .build();

    validateUsers(users, usersCount, validator);

    return 0;
}