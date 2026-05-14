#pragma once
#include "user.h"
class uservalidator
{
private:
    int min_length_name;
    int min_length_password;
    int min_age;
    bool password_must_have_digit;
    bool password_must_have_capital_letter;
    uservalidator(int min_length_name,
                  int min_length_password,
                  int min_age,
                  bool password_must_have_digit,
                  bool password_must_have_capital_letter);

public:
    bool operator()(const user &user);
    class builder
    {
    private:
        int min_length_name = 0;
        int min_length_password = 0;
        int min_age = 0;
        bool password_must_have_digit = false;
        bool password_must_have_capital_letter = false;

    public:
        builder &set_min_length_name(int n)
        {
            min_length_name = n;
            return *this;
        }
        builder &set_min_length_password(int n)
        {
            min_length_password = n;
            return *this;
        }
        builder &set_min_age(int n)
        {
            min_age = n;
            return *this;
        }
        builder &set_password_must_have_digit()
        {
            password_must_have_digit = true;
            return *this;
        }
        builder &set_password_must_have_capital_letter()
        {
            password_must_have_capital_letter = true;
            return *this;
        }
        uservalidator build() const;
    };
};