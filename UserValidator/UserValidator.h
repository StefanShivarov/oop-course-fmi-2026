#ifndef USERVALIDATOR_USERVALIDATOR_H
#define USERVALIDATOR_USERVALIDATOR_H
#include "User.h"

class User::UserValidator {
    int minUsernameLen = 0;
    int minPasswordLen = 0;
    int minAge = 0;
    bool requireDigit = false;
    bool requireUppercase = false;
public:
    UserValidator& withMinLenUsername(int len);
    UserValidator& withMinLenPass(int len);
    UserValidator& withMinAge(int age);
    UserValidator& withDigit();
    UserValidator& withUppercase();

    bool operator()(const User& u) const;
};

#endif //USERVALIDATOR_USERVALIDATOR_H
