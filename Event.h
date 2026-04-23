#pragma once
#include "Registration.h"
#include "ProfitCalculator.h"
enum EventType {
	SEMINAR,
	CONCERT,
	SPORT,
	OTHER
};
class Event
{
private:
	char* name = nullptr;
	char* description = nullptr;
	EventType type;
	double basePriceParticipation;
	int maxCapasity;
	double priceTicket;
	int freeplaces;
	int ocupiedplaces;
	Registration** spaces =  nullptr;
	void moverfrom(Event&& other);
	void copyfrom(const Event& other);
	void free();
public:
	Event(const char* name, const char* description, EventType type, int capacity, double price, double basePriceParticipation);
	Event(const Event& other);
	Event(Event&& other) noexcept;
	Event& operator=(const Event& other);
	Event& operator=(Event&& other) noexcept;
	bool addUser(User* user);
	bool addUserAtPosition(User* user, int possition);
	void removeUser(User& user);
	double getRevenue() const;

	double getProfit(const ProfitCalculator& calc) const;
	int getOcupiedplaces();
	int getFreespaces();
};