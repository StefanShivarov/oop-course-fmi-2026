#pragma once
#include <iostream>
#include "User.h"

class Registration
{
	User* user; //aggregation
	double paidPrice = 0;

public:
	Registration(User* user, double price);
	User* getUser() const;
	double getPaidPrice() const;
};