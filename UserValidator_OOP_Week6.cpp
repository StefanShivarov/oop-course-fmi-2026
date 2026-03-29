#include <iostream>
#include"User.h"
#include"UserValidator.h"
#include<print>

int main()
{
    User user("Maya", "12A3", 19);
    std::cout << user << "\n";

    UserValidator validator = UserValidator::builder()
        .withMinNameLen(2)
        .withMinPasswordLen(4)
        .withMinAge(18)
        .withMaxAge(60)
        .withDigitPassword()
        .withUpperCasePassword()
        .build();

    std::println("{}", validator(user));
    return 0;
}
