#include <iostream>
#include "User.h"
#include "UserValidator.h"
using namespace std;

int main() {
    const User u1("Rumen", "Pass123", 20);
    const auto validator = User::validator()
                        .withMinLenUsername(3)
                        .withMinLenPass(6)
                        .withMinAge(18)
                        .withDigit()
                        .withUppercase();
    if (validator(u1)) {
        println("User is valid!");
    }
    else {
        println("User is invalid!");
    }
}