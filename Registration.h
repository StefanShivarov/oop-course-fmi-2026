#pragma once
#include "User.h"

class Registration
{
private:
	const User* user;
	size_t seatIndex;

public:
	Registration(User*, size_t);
	const User* getUser() const;
	size_t getSeatIndex() const;
};

