#include "Hall.h"
#include <iostream>

Hall::Hall() : id(0), capacitySeats(0)
{
}

Hall::Hall(int id, size_t capacitySeats) : id(id), capacitySeats(capacitySeats)
{
}

void Hall::printHall() const
{
	std::cout << "Hall Number: " << id << '\n';
	std::cout << "Number of seats: " << capacitySeats << '\n';
}

size_t Hall::getCapacity() const
{
	return capacitySeats;
}
