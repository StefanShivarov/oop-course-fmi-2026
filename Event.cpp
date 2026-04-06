#define _CRT_SECURE_NO_WARNINGS
#include "Event.h"
#include<cstring>
#include<iostream>
#include<print>


Event::Event() :type(Type::SEMINAR), basePrice(0), maxSeats(DEFAULT_MAX_SEATS), ticketPrice(0)
{
	name = new char[1];
	name[0] = '\0';
	description = new char[1];
	description[0] = '\0';
	seats = new Registration * [maxSeats] {nullptr};
}

Event::Event(const char* name, const char* description, Type type, double basePrice,
	size_t maxSeats, double ticketPrice)
{
	setName(name);
	setDescription(description);
	this->type = type;
	setBasePrice(basePrice);
	this->maxSeats = maxSeats;
	setTicketPrice(ticketPrice);

	this->seats = new Registration * [maxSeats] {nullptr};
}

Event::Event(const char* name, const char* description, const char* type, 
	double basePrice,size_t maxSeats, double ticketPrice)
{
	setName(name);
	setDescription(description);
	this->type = EventType::convertToType(type);
	setBasePrice(basePrice);
	this->maxSeats = maxSeats;
	setTicketPrice(ticketPrice);

	this->seats = new Registration * [maxSeats] {nullptr};
}

void Event::setName(const char* name)
{
	if (name == nullptr)
	{
		return;
	}
	delete[]this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Event::setDescription(const char* description)
{
	if (description == nullptr)
	{
		return;
	}
	delete[]this->description;
	this->description = new char[strlen(description) + 1];
	strcpy(this->description, description);
}

void Event::setBasePrice(double basePrice)
{
	if (basePrice < 0)
	{
		return;
	}
	this->basePrice = basePrice;
}

void Event::setTicketPrice(double ticketPrice)
{
	if (ticketPrice < 0)
	{
		return;
	}
	this->ticketPrice = ticketPrice;
}

void Event::setType(const char* type)
{
	if (type == nullptr)
	{
		return;
	}
	this->type = EventType::convertToType(type);
}

void Event::copyFrom(const Event& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);

	description = new char[strlen(other.description) + 1];
	strcpy(description, other.description);

	type = other.type;
	basePrice = other.basePrice;
	maxSeats = other.maxSeats;
	ticketPrice = other.ticketPrice;

	seats = new Registration * [maxSeats];
	for (size_t i = 0;i < maxSeats;i++)
	{
		if (other.seats[i])
		{
			seats[i] = new Registration(*other.seats[i]);
		}
		else
		{
			seats[i] = nullptr;
		}
	}
}

void Event::moveFrom(Event&& other)
{
	name = other.name;
	description = other.description;
	type = other.type;
	basePrice = other.basePrice;
	maxSeats = other.maxSeats;
	ticketPrice = other.ticketPrice;
	seats = other.seats;

	other.name = nullptr;
	other.description = nullptr;
	other.type = Type::OTHER;
	other.basePrice = 0;
	other.maxSeats = 0;
	other.ticketPrice = 0;
	other.seats = nullptr;
}

void Event::free()
{
	delete[]name;
	name = nullptr;
	delete[]description;
	description = nullptr;
	
	for (size_t i = 0;i < maxSeats;i++)
	{
		delete seats[i];
	}
	delete[]seats;
	seats = nullptr;

	type = Type::OTHER;
	basePrice = 0;
	maxSeats = 0;
	ticketPrice = 0;
}

Event::Event(const Event& other)
{
	copyFrom(other);
}

Event& Event::operator=(const Event& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Event::Event(Event&& other)noexcept
{
	moveFrom(std::move(other));
}

Event& Event::operator=(Event&& other)noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Event::~Event()
{
	free();
}

int Event::findFirstFreeSeat()const
{
	for (size_t i = 0;i < maxSeats;i++)
	{
		if (seats[i] == nullptr)
		{
			return i;
		}
	}
	return -1;
}

void Event::addUser(User* user)
{
	int index = findFirstFreeSeat();
	if (index == -1 || !user->canAfford(ticketPrice))
	{
		return;
	}

	user->pay(ticketPrice);
	seats[index] = new Registration(user, this, index, ticketPrice);
}

void Event::addUser(User& user)
{
	addUser(&user);
}

void Event::addUser(User&& user)
{
	addUser(user);
}

void Event::addUser(User* user, size_t index)
{
	if (index >= maxSeats || !user->canAfford(ticketPrice))
	{
		return;
	}

	if (seats[index] != nullptr)
	{
		addUser(user);
		return;
	}
	user->pay(ticketPrice);
	seats[index] = new Registration(user, this, index, ticketPrice);
}

void Event::addUser(User& user, size_t index)
{
	addUser(&user, index);
}

void Event::addUser(User&& user, size_t index)
{
	addUser(user,index);
}

void Event::removeUser(size_t index)
{
	if (index >= maxSeats)
	{
		return;
	}
	delete seats[index];
	seats[index] = nullptr;
}

size_t Event::takenSeats()const
{
	size_t result = 0;
	for (size_t i = 0;i < maxSeats;i++)
	{
		if (seats[i] != nullptr)
		{
			result++;
		}
	}

	return result;
}

size_t Event::freeSeats()const
{
	size_t taken = takenSeats();
	return maxSeats - taken;
}

double Event::calculateRevenue()const
{
	size_t taken = takenSeats();
	return ticketPrice * taken;
}

double Event::calculateProfit(const ProfitCalculator& calc) const
{
	return calc(calculateRevenue(), takenSeats());
}