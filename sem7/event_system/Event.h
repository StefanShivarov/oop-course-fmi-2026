#pragma once
#include "Registration.h"
#include "EventProfit.h"
class Event
{
	char* name = nullptr;
	char* description = nullptr;
	char* type = nullptr;

	Registration** seats = nullptr;
	
	double priceForParticipation = 0;
	double pricePerTicket = 0;

	size_t capacity = 0; 
	size_t countSeats = 0;

	size_t firstFreeSpaceIndex = 0;

	void updateFirstFreeSpaceIndex();

	void free();
	void copyFrom(const Event& other);
	void moveFrom(Event&& other);

public:
	Event() = default;
	Event(const char* name, const char* description, const char* type, size_t capacity, double priceForParticipation, double pricePerTicket);

	Event(const Event& other);
	Event& operator=(const Event& other);

	Event(Event&& other) noexcept;
	Event& operator=(Event&& other) noexcept;

	~Event();

	size_t getTakenSpacesCount() const;
	size_t getFreeSpacesCount() const;
	size_t getMaxCapacity() const;

	bool registеrUserAt(const Registration& p, size_t index);
	bool registеrUserAt(Registration&& p, size_t index);
	bool registеrUserAt(Registration* p, size_t index);

	bool registеrUser(const Registration& p);
	bool registеrUser(Registration&& p);
	bool registеrUser(Registration* p);

	void remove(size_t index);
	const Registration* operator[](size_t index) const;

	double calculateProfit(const EventProfit& profitCalculator) const;
};

