#pragma once
#include "User.h"
#include "Registration.h"

enum class TicketType {
    STANDARD,
    JUNIOR,
    STUDENT,
    VIP
};

class Registration {
public:
    Registration(const User* user, double paidPrice, TicketType ticketType = TicketType::STANDARD);
    Registration(const User& user, double paidPrice, TicketType ticketType = TicketType::STANDARD);

    const User& getUser() const;
    double getPaidPrice() const;
    TicketType getTicketType() const;

private:
    const User* user = nullptr;
    double paidPrice = 0.0;
    TicketType ticketType = TicketType::STANDARD;
};
