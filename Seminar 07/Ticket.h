#pragma once
#include "Person.h"

class Ticket
{
private:
    Person person;
    double pricePaid;
public:
    Ticket(const Person& person, double pricePaid);
    Ticket(Person&& person, double pricePaid);

    const Person& getPerson() const;
    double getPricePaid() const;
};
