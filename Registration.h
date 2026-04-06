#pragma once
#include "User.h"
class Registration
{
private:
    User* user;
    int seatIndex;
    double paidPrice;

public:
    Registration(User* user = nullptr);
    User* getUser() const;
    int getSeatIndex() const;
    void setSeatIndex(int seatIndex);
    double getPaidPrice() const;
    void setPaidPrice(double price);
};

