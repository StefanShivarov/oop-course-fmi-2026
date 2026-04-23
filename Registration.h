#pragma once
#include "User.h"

class Registration {
private:
    User* user;
    size_t seatIndex;
    double price;

public:
    Registration(User* user, size_t seat, double price)
        : user(user), seatIndex(seat), price(price) {
    }

    User* getUser() const; 
    size_t getSeat() const;
    double getPrice() const;
};