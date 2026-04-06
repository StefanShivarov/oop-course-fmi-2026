#include "Event.h"
#include "Utils.h"
#include <iostream>
#include <cstring>

void Event::copyFrom(const Event& other)
{
	type = other.type;
	minPrice = other.minPrice;
	maxPlaces = other.maxPlaces;
	ticketPrice = other.ticketPrice;

	name = Utils::copyDynamicString(other.name);
	description = Utils::copyDynamicString(other.description);

	seats = new Registration * [maxPlaces];

	for (size_t i = 0; i < maxPlaces; i++)
	{
		if (other.seats[i] != nullptr) {
			seats[i] = new Registration(*other.seats[i]);
		}
		else {
			seats[i] = nullptr;
		}
	}

}

void Event::free()
{
	delete[] name;
	delete[] description;
	name = nullptr;
	description = nullptr;

	for (size_t i = 0; i < maxPlaces; i++)
	{
		delete seats[i];
	}

	delete[] seats;
	seats = nullptr;
}

void Event::moveFrom(Event&& other)
{
	type = other.type;
	minPrice = other.minPrice;
	maxPlaces = other.maxPlaces;
	ticketPrice = other.ticketPrice;
	name = other.name;
	description = other.description;
	seats = other.seats;

	other.type = Type::OTHER;
	other.minPrice = 0.0;
	other.maxPlaces = 0;
	other.ticketPrice = 0.0;
	other.name = nullptr;
	other.description = nullptr;
	other.seats = nullptr;

}

void Event::initSeats()
{
	seats = new Registration * [maxPlaces];
	for (size_t i = 0; i < maxPlaces; i++)
	{
		seats[i] = nullptr;
	}
}

Event::Event():type(Type::OTHER), minPrice(0.0), maxPlaces(50), ticketPrice(0.0)
{
	name = new char[1];
	name[0] = '\0';
	description = new char[1];
	description[0] = '\0';

	initSeats();
}

Event::Event(const char* name, const char* description, Type type, double minPrice, size_t maxPlaces, double ticketPrice)
	: type(type), minPrice(minPrice), maxPlaces(maxPlaces), ticketPrice(ticketPrice)
{
	this->name = Utils::copyDynamicString(name);
	this->description = Utils::copyDynamicString(description);

	initSeats();
}

Event::Event(const Event& other)
{
	copyFrom(other);
}

Event& Event::operator=(const Event& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

Event::Event(Event&& other) noexcept
{
	moveFrom(std::move(other));
}

Event& Event::operator=(Event&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Event::~Event()
{
	free();
}

double Event::getTicketPrice() const
{
	return ticketPrice;
}

size_t Event::occupiedSeats() const
{
	size_t count = 0;
	for (size_t i = 0; i < maxPlaces; i++)
	{
		if (seats[i] != nullptr) {
			count++;
		}
	}

	return count;
}

size_t Event::freeSeats() const
{
	return maxPlaces-occupiedSeats();
}

int Event::findFirstFreeSeat() const
{
	for (size_t i = 0; i < maxPlaces; i++)
	{
		if (seats[i] == nullptr)
			return i;
	}
	return -1;
}

bool Event::registerUser(User* user)
{
	if (!user) {
		return false;
	}
		

	if (user->getBudget() < ticketPrice || user->getBudget()<minPrice) {
		return false;
	}
		

	int index = findFirstFreeSeat();
	if (index == -1) {
		return false;
	}
		
	user->setBudget(user->getBudget() - ticketPrice);
	seats[index] = new Registration(user, index);
	return true;
}

bool Event::registerUser(User* user, size_t index)
{
	if (!user) {
		return false;
	}
		

	if (user->getBudget() < ticketPrice || user->getBudget() < minPrice) {
		return false;
	}
		

	if (index >= maxPlaces) {
		return false;
	}
		

	if (seats[index] == nullptr)
	{
		user->setBudget(user->getBudget() - ticketPrice);
		seats[index] = new Registration(user, index);
		return true;
	}

	int freeIndex = findFirstFreeSeat();
	if (freeIndex == -1) {
		return false;
	}
		
	user->setBudget(user->getBudget() - ticketPrice);
	seats[freeIndex] = new Registration(user, freeIndex);
	
	return true;
}

bool Event::registerUser(User& user)
{
	return registerUser(&user);
}

bool Event::registerUser(User&& user)
{
	return registerUser(&user);
}

bool Event::removeRegistration(const User& user)
{
	for (size_t i = 0; i < maxPlaces; i++)
	{
		if (seats[i] != nullptr) {
			if (strcmp(seats[i]->getUser()->getEmail(), user.getEmail()) == 0) {
				delete seats[i];
				seats[i] = nullptr;
				return true;
			}
		}
	}

	return false;
}
