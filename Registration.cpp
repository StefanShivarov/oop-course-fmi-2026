#include "Registration.h"

User* Registration::getUser() const
{
	return user;
}

size_t Registration::getSeat() const
{
	return seatIndex;
}

double Registration::getPrice() const
{
	return price;
}