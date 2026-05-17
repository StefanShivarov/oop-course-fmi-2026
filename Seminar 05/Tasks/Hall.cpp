#include "Hall.h"
#include <iostream>
#include <cstring>
#pragma warning(disable: 4996)

unsigned Hall::roomNumber = 0;

Hall::Hall(unsigned seatsCount) : seatsCount(seatsCount), counter(++roomNumber)
{
	
}

unsigned Hall::getRoomNumber() const
{
	return counter;
}

unsigned Hall::getSeatsCount() const
{
	return seatsCount;
}

void printHall(const Hall& hall, std::ostream& os)
{
	os << "Room# " << hall.getRoomNumber() << '\n';
	os << "Seats: " << hall.getSeatsCount() << '\n';
}
