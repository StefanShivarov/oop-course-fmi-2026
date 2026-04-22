#pragma once
#include "Registration.h"

enum class Type {
	CONCERT, SEMINAR, SPORTING_EVENT, OTHER
};

class Event
{
private:
	char* name = nullptr;
	char* description = nullptr;
	Type type;
	double minPrice;
	size_t maxPlaces;
	double ticketPrice;

	Registration** seats = nullptr;

	void copyFrom(const Event&);
	void free();
	void moveFrom(Event&&);

	void initSeats();

public:
	Event();
	Event(const char*, const char*, Type, double, size_t, double);
	Event(const Event&);
	Event& operator=(const Event&);
	Event(Event&&) noexcept;
	Event& operator=(Event&&) noexcept;
	~Event();

	double getTicketPrice() const;


	size_t occupiedSeats() const;
	size_t freeSeats() const;

	int findFirstFreeSeat()const;

	bool registerUser(User*);
	bool registerUser(User*, size_t);
	bool registerUser(User&);
	bool registerUser(User&& user);
	bool removeRegistration(const User&);
};

