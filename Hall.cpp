#include "Hall.h"

Hall::Hall(int seats) : id(++totalHalls), seatsCount(seats) {}

unsigned Hall::getId() const {
	return id;
}

unsigned Hall::getSeatsCount() const {
	return seatsCount;
}

unsigned Hall::totalHalls = 0;