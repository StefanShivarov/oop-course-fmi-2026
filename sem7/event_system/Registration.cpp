#include "Registration.h"
#include "User.h"
#include <iostream>

Registration::Registration(User* user, double price) : user(user), paidPrice(price) {}

User* Registration::getUser() const
{
	return user;
}

double Registration::getPaidPrice() const
{
	return paidPrice;
}
