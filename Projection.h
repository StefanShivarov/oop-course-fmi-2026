#pragma once

#include "Movie.h"
#include "Hall.h"
#include <iostream>
#include <cstring>
#pragma warning (disable: 4996)

class Projection {
private:
	static unsigned totalCount;
	int id;
	Movie* movie;
	Hall* hall;
	char* time;
	unsigned takenSeats;
	bool* reservations;

	void copyDynamicMemory(const Projection& other);
	void freeDynamicMemory();

public:
	Projection();
	Projection(Movie* movie, Hall* hall, const char* time);
	Projection(const Projection& other);
	Projection& operator=(const Projection& other);
	~Projection();

	unsigned getId();
	bool reserveSeat(unsigned number);
	void freeSeat(unsigned number);
	bool isSeatFree(unsigned number) const;
	unsigned getFreeSeatsCount() const;
	void displayInformation() const;
};

