#include "Registration.h"

Registration::Registration(User* user)
{
	this->user = user;
	this->seatIndex = -1;
	this->paidPrice = 0.0;
}

User* Registration::getUser() const
{
	return user;
}

int Registration::getSeatIndex() const
{
	return seatIndex;
}

void Registration::setSeatIndex(int seatIndex)
{
	this->seatIndex = seatIndex;
}

double Registration::getPaidPrice() const
{
	return paidPrice;
}

void Registration::setPaidPrice(double price)
{
	paidPrice = price;
}
