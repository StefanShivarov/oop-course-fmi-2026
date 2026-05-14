#include "uservalidator.h"
#include <cstring>
uservalidator::uservalidator(int min_length_name,
                             int min_length_password,
                             int min_age,
                             bool password_must_have_digit,
                             bool password_must_have_capital_letter)
    : min_length_name(min_length_name),
      min_length_password(min_length_password),
      min_age(min_age),
      password_must_have_digit(password_must_have_digit),
      password_must_have_capital_letter(password_must_have_capital_letter)
{
}

uservalidator uservalidator::builder::build() const
{
    return uservalidator(this->min_length_name,
                         this->min_length_password,
                         this->min_age,
                         this->password_must_have_digit,
                         this->password_must_have_capital_letter);
}

bool uservalidator::operator()(const user &user)
{
    if (!user.get_password() || !user.get_username())
        return false;
    if (min_age > user.get_age())
        return false;
    if (min_length_name > std::strlen(user.get_username()))
        return false;
    if (min_length_password > std::strlen(user.get_password()))
        return false;
    bool has_capital = false;
    bool has_digit = false;
    if (password_must_have_capital_letter || password_must_have_digit)
    {
        for (int i = 0; i < std::strlen(user.get_password()); i++)
        {
            char current = *(user.get_password() + i);
            if (current >= 'A' && current <= 'Z')
                has_capital = true;
            if (current >= '0' && current <= '9')
                has_digit = true;
        }
    }
    if (password_must_have_capital_letter && !has_capital)
    {
        return false;
    }
    if (password_must_have_digit && !has_digit)
    {
        return false;
    }
    return true;
}
