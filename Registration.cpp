#include "Registration.h"

Registration::Registration(User* user, size_t seatIndex)
{
	this->user = user;
	this->seatIndex = seatIndex;
}

const User* Registration::getUser() const
{
	return user;
}

size_t Registration::getSeatIndex() const
{
	return seatIndex;
}
