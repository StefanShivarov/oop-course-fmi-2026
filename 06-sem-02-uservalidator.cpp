#include <iostream>

#include "User.h"
#include "UserValidator.h"

int main() {
    User user1("Nikolay", "frwidovBlinFIJV3988_KOq?1", 20);
    User user2("Viktor", "OBnujiNUlJvfsd3H94UTEOq7_", 21);
    User user3("Viktoria", "kjhngfdsnhgfd564534", 22);

    UserValidator validator = UserValidator::Builder()
        .withMinNameLength(7)
        .withPasswordContainsCapital()
        .withMinAge(20)
        .build();

    std::cout << validator(user1) << std::endl;
    std::cout << validator(user2) << std::endl;
    std::cout << validator(user3) << std::endl;
}