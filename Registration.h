#pragma once
#include"User.h"

class Event;

class Registration
{
private:
	User* user = nullptr;
	Event* event = nullptr;
	size_t seatIndex = 0;
	double paidPrice = 0;

public:
	Registration();
	Registration(User* user, Event* event, size_t seatIndex, double paidPrice);
	
	User* getUser() const;
	Event* getEvent() const;
	size_t getSeatIndex() const;
	double getPaidPrice() const;

	void setPaidPrice(double paidPrice);

};

