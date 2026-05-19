#include "Event.h"
#include "Utils.h"
#include<iostream>

void Event::free()
{
	delete[] name;
	delete[] description;
	delete[] type;

	name = description = type = nullptr;

	for (size_t i = 0; i < capacity; i++)
	{
		delete seats[i];
	}
	delete[] seats;
	seats = nullptr;

}

void Event::copyFrom(const Event& other)
{
	name = Utils::copyDynamicString(other.name);
	description = Utils::copyDynamicString(other.description);
	type = Utils::copyDynamicString(other.type);

	capacity = other.capacity;
	countSeats = other.countSeats;
	firstFreeSpaceIndex = other.firstFreeSpaceIndex;

	priceForParticipation = other.priceForParticipation;
	pricePerTicket = other.pricePerTicket;

	seats = new Registration*[capacity] {};
	for (size_t i = 0; i < capacity; i++)
	{
		if (other.seats[i] != nullptr) {
			seats[i] = new Registration(*other.seats[i]);
		}
	}

}

void Event::moveFrom(Event&& other)
{
	seats = other.seats;
	name = other.name;
	description = other.description;
	type = other.type;

	capacity = other.capacity;
	countSeats = other.countSeats;

	priceForParticipation = other.priceForParticipation;
	pricePerTicket = other.pricePerTicket;

	other.seats = nullptr;
	other.name = other.description = other.type = nullptr;
	other.priceForParticipation = 0;
	other.pricePerTicket = 0;
	other.capacity = 0;
	other.countSeats = 0;     
	other.firstFreeSpaceIndex = 0;
}

Event::Event(const char* name, const char* description, const char* type, size_t capacity, double priceForParticipation, double pricePerTicket)
: capacity(capacity), countSeats(0), firstFreeSpaceIndex(0),
priceForParticipation(priceForParticipation), pricePerTicket(pricePerTicket)
{
	this->name = Utils::copyDynamicString(name);
	this->description = Utils::copyDynamicString(description);
	this->type = Utils::copyDynamicString(type);

	this->seats = new Registration * [capacity]{};
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

size_t Event::getTakenSpacesCount() const {
	return countSeats;
}

size_t Event::getFreeSpacesCount() const {
	return capacity - countSeats;
}

size_t Event::getMaxCapacity() const {
	return capacity;
}

void Event::updateFirstFreeSpaceIndex() {
	for (size_t i = 0; i < capacity; i++)
	{
		if (seats[i] == nullptr) {
			firstFreeSpaceIndex = i;
			return;
		}
	}
	firstFreeSpaceIndex = capacity;
}

bool Event::registеrUserAt(const Registration& p, size_t index)
{
	if (countSeats >= capacity || firstFreeSpaceIndex >= capacity) {
		return false;
	}

	if (index >= capacity || seats[index]) {
		index = firstFreeSpaceIndex;
	}

	seats[index] = new Registration(p);
	updateFirstFreeSpaceIndex();
	countSeats++;
	return true;
}

bool Event::registеrUserAt(Registration&& p, size_t index)
{
	if (countSeats >= capacity || firstFreeSpaceIndex >= capacity) {
		return false;
	}

	if (index >= capacity || seats[index]) {
		index = firstFreeSpaceIndex;
	}

	seats[index] = new Registration(std::move(p));
	updateFirstFreeSpaceIndex();
	countSeats++;
	return true;
}

bool Event::registеrUserAt(Registration* p, size_t index)
{
	if (countSeats >= capacity || firstFreeSpaceIndex >= capacity) {
		return false;
	}

	if (index >= capacity || seats[index]) {
		index = firstFreeSpaceIndex;
	}

	seats[index] = p;
	updateFirstFreeSpaceIndex();
	countSeats++;
	return true;
}

bool Event::registеrUser(const Registration& p)
{
	return registеrUserAt(p, firstFreeSpaceIndex);
}

bool Event::registеrUser(Registration&& p)
{
	return registеrUserAt(p, firstFreeSpaceIndex);
}

bool Event::registеrUser(Registration* p)
{
	return registеrUserAt(p, firstFreeSpaceIndex);
}

void Event::remove(size_t index)
{
	if (index < capacity && seats[index] != nullptr) {
		delete seats[index];
		seats[index] = nullptr;
		countSeats--;
		updateFirstFreeSpaceIndex();
	}
}

const Registration* Event::operator[](size_t index) const {
	return seats[index];
}

double Event::calculateProfit(const EventProfit& profitCalculator) const
{
	double totalIncome = countSeats * (priceForParticipation + pricePerTicket);
	return profitCalculator(totalIncome, countSeats);
}

