#include <iostream>
#include "User.h"
#include "UserValidator.h"
using std::cin;
using std::cout;

void checkUser(const User& user, const UserValidator& validator)
{
    cout << user.getUsername() << ": " << (validator(user) ? "valid" : "invalid") << '\n';
}

int main() {
    User u1("gosho", "241106", 19);
    User u2("sevim", "S261106", 19);
    User u3("dimi", "D260407", 18);

    UserValidator validator = UserValidator::builder()
        .withMinUsernameLen(4)
        .withMinPasswordLen(6)
        .withMinAge(18)
        .withRequireDigit()
        .withRequireUpper()
        .build();

    checkUser(u1, validator);  
    checkUser(u2, validator);  
    checkUser(u3, validator);  
}