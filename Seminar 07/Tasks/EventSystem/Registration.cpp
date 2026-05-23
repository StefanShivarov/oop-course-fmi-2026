#include "Registration.h"

Registration::Registration(const User* user, double paidPrice, TicketType ticketType)
    : user(user), paidPrice(paidPrice), ticketType(ticketType) {
}

Registration::Registration(const User& user, double paidPrice, TicketType ticketType)
    : Registration(&user, paidPrice, ticketType) {
}

const User& Registration::getUser() const {
    return *user;
}

double Registration::getPaidPrice() const {
    return paidPrice;
}

TicketType Registration::getTicketType() const {
    return ticketType;
}
