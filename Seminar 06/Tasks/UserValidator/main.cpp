#include <iostream>
#include "User.h"
#include "UserValidator.h"

int main() {
    User u1("stef123", "abc123", 22);
    User u2("testUser1", "Password1", 22);
    User u3("John Doe", "test", 17);

    UserValidator validator = UserValidator::builder()
        .withMinUsernameLength(5)
        .withMinPasswordLength(8)
        .withMinAge(18)
        .requireDigitInPassword()
        .requireUppercaseInPassword()
        .build();

    std::cout << validator(u1) << '\n'; // false
    std::cout << validator(u2) << '\n'; // true
    std::cout << validator(u3) << '\n'; // false

    return 0;
}