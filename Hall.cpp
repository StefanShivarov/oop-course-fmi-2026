#include "Hall.h"
#include<print>

size_t Hall::nextId = 1;

Hall::Hall() :id(nextId++), countSeats(0) {}

Hall::Hall(size_t countSeats) : id(nextId++), countSeats(countSeats) {}

void Hall::setCountSeats(size_t countSeats)
{
	this->countSeats = countSeats;
}

size_t Hall::getId() const
{
	return id;
}

size_t Hall::getCountSeats() const
{
	return countSeats;
}

void Hall::printHall()const
{
	std::println("Hall id: {}, Count seats: {}", id, countSeats);
}