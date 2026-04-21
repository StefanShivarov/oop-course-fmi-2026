#include "Ticket.h"
#include<iostream>


Ticket::Ticket(const Person& person, double pricePaid): person(person), pricePaid(pricePaid) {}

Ticket::Ticket(Person&& person, double pricePaid): person(std::move(person)), pricePaid(pricePaid) {}

const Person& Ticket::getPerson() const {
	return person; 
}
double Ticket::getPricePaid() const { 
	return pricePaid;
}
