#include "Registration.h"

Registration::Registration():user(nullptr),event(nullptr),seatIndex(0),paidPrice(0){}

Registration::Registration(User* user, Event* event, size_t seatIndex, double paidPrice)
    : user(user), event(event), seatIndex(seatIndex)
{
    setPaidPrice(paidPrice);
}

void Registration::setPaidPrice(double paidPrice)
{
    if (paidPrice < 0)
    {
        return;
    }
    this->paidPrice = paidPrice;
}

User* Registration::getUser()const
{
    return user;
}

Event* Registration::getEvent()const
{
    return event;
}

size_t Registration::getSeatIndex()const
{
    return seatIndex;
}

double Registration::getPaidPrice()const
{
    return paidPrice;
}
