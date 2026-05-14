#include "user.h"
#include "uservalidator.h"
#include <iostream>

int main()
{
    uservalidator v = uservalidator::builder()
                          .set_min_length_password(8)
                          .set_min_age(18)
                      //  .set_password_must_have_digit()
                      //  .set_password_must_have_capital_letter()
                          .build();
    user Stefo("Stefo", "password", 23);
    user Serhan(Stefo);
    std::cout << v(Stefo);
    std::cout << v(Serhan);
    return 0;
}