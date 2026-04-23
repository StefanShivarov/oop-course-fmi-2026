#include "Event.h"
#include <cstring>
#include <utility>
#pragma warning(disable:4996)
void Event::moverfrom(Event&& other)
{
	this->name = other.name;
	this->description = other.description;
	this->type = other.type;
	this->basePriceParticipation = other.basePriceParticipation;
	this->maxCapasity = other.maxCapasity;
	this->priceTicket = other.priceTicket;
	this->freeplaces = other.freeplaces;
	this->ocupiedplaces = other.ocupiedplaces;
	this->spaces = other.spaces;

	other.name = nullptr;
	other.description = nullptr;
	other.basePriceParticipation = 0.0;
	other.priceTicket = 0.0;
	other.freeplaces = 0;
	other.ocupiedplaces = 0;
	other.spaces = nullptr;
	other.maxCapasity = 0;
}

void Event::copyfrom(const Event& other)
{
	this->name = new char[strlen(other.name) + 1];
	strcpy(this->name, other.name);
	this->description = new char[strlen(other.description) + 1];
	strcpy(this->description, other.description);
	this->type = other.type;
	this->basePriceParticipation = other.basePriceParticipation;
	this->maxCapasity = other.maxCapasity;
	this->priceTicket = other.priceTicket;
	this->freeplaces = other.freeplaces;
	this->ocupiedplaces = other.ocupiedplaces;
	this->spaces = new Registration * [maxCapasity];
	for (size_t i = 0; i < maxCapasity; i++) {
		if (other.spaces[i]) {
			spaces[i] = new Registration(*other.spaces[i]);
		}
		else {
			spaces[i] = nullptr;
		}
	}
}
void Event::free() {
	delete[] name;
	name = nullptr;
	delete[] description;
	description = nullptr;
	basePriceParticipation = 0.0;
	priceTicket = 0.0;
	freeplaces = 0;
	ocupiedplaces = 0;
	if (spaces) {
		for (int i = 0; i < maxCapasity; i++) {
			if (spaces[i]) {
				delete spaces[i];
				spaces[i] = nullptr;
			}
		}
		delete[] spaces;
		spaces = nullptr;
	}
	maxCapasity = 0;
}

Event::Event(const char* name, const char* description, EventType type, int capacity, double price, double basePriceParticipation)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	this->description = new char[strlen(description) + 1];
	strcpy(this->description, description);
	this->type = type;
	maxCapasity = capacity;
	priceTicket = price;
	this->basePriceParticipation = basePriceParticipation;
	spaces = new Registration * [maxCapasity];
	for (int i = 0; i < maxCapasity; ++i) {
		spaces[i] = nullptr;
	}
	freeplaces = maxCapasity;
	ocupiedplaces = 0;
}

Event::Event(const Event& other)
{
	copyfrom(other);
}

Event::Event(Event&& other) noexcept
{
	moverfrom(std::move(other));
}

Event& Event::operator=(const Event& other)
{
	if (this != &other) {
		free();
		copyfrom(other);
	}
	return *this;
}

Event& Event::operator=(Event&& other) noexcept
{
	if (this != &other) {
		free();
		moverfrom(std::move(other));
	}
	return *this;
}

bool Event::addUser(User* user)
{
	if (!user->canAfford(priceTicket) || freeplaces == 0) {
		return false;
	}
	for (int i = 0; i < maxCapasity; i++) {
		if (spaces[i] == nullptr) {
			spaces[i] = new Registration(user, i, priceTicket);
			--freeplaces;
			++ocupiedplaces;
			user->pay(priceTicket);
			return true;
		}
	}
	return false;
}

bool Event::addUserAtPosition(User* user, int possition)
{
	if (possition < 0 || possition >= maxCapasity) {
		return false;
	}
	if (!user->canAfford(priceTicket) || freeplaces == 0) {
		return false;
	}
	if (spaces[possition] == nullptr) {
		spaces[possition] = new Registration(user, possition, priceTicket);
		--freeplaces;
		++ocupiedplaces;
		user->pay(priceTicket);
		return true;
	}
	else {
		return addUser(user);
	}
	return false;
}

void Event::removeUser(User& user)
{
	for (int i = 0; i < maxCapasity; i++) {
		if (spaces[i] && spaces[i]->getUser() == &user) {
			delete spaces[i];
			spaces[i] = nullptr;
			++freeplaces;
			--ocupiedplaces;
			break;
		}
	}
}

double Event::getRevenue() const
{
	double sum = 0;
	for (size_t i = 0; i < maxCapasity; i++) {
		if (spaces[i])
			sum += spaces[i]->getPrice();
	}
	return sum;
}

double Event::getProfit(const ProfitCalculator& calc) const
{
	return calc.calculate(getRevenue(), ocupiedplaces);
}

int Event::getOcupiedplaces()
{
	return ocupiedplaces;
}

int Event::getFreespaces()
{
	return freeplaces;
}