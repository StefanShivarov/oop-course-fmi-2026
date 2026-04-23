#pragma once
#include"EventType.h"
#include"Registration.h"
#include"ProfitCalculator.h"

class Event
{
private:
	static constexpr size_t DEFAULT_MAX_SEATS = 16;
	char* name = nullptr;
	char* description = nullptr;
	Type type = Type::SEMINAR;
	double basePrice = 0;
	size_t maxSeats = DEFAULT_MAX_SEATS;
	double ticketPrice = 0;
	Registration** seats = nullptr;

	void copyFrom(const Event& other);
	void moveFrom(Event&& other);
	void free();

	int findFirstFreeSeat()const;

public:
	Event();
	Event(const char* name, const char* description, Type type, double basePrice,
		size_t maxSeats, double ticketPrice);
	Event(const char* name, const char* description, const char* type, double basePrice,
		size_t maxSeats, double ticketPrice);

	Event(const Event& other);
	Event& operator=(const Event& other);
	Event(Event&& other)noexcept;
	Event& operator=(Event&& other)noexcept;
	~Event();

	void setName(const char* name);
	void setDescription(const char* description);
	void setType(const char* type);
	void setBasePrice(double basePrice);
	void setTicketPrice(double ticketPrice);

	void addUser(User* user);
	void addUser(User* user, size_t index);
	void addUser(User&);
	void addUser(User&& user);
	void addUser(User& user, size_t index);
	void addUser(User&& user, size_t index);

	void removeUser(size_t index);

	size_t takenSeats()const;
	size_t freeSeats()const;

	double calculateRevenue()const;
	double calculateProfit(const ProfitCalculator& calc) const;
};

