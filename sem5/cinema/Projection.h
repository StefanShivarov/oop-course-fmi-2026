#pragma once
#include "Film.h"
#include "Hall.h"
#include "Date.h"
#include "Time.h"

class Projection
{
	const Film* film;
	const Hall* hall;
	Date date;
	Time t;
	bool* taken = nullptr;

	void free();
	void copyFrom(const Projection& other);

public:
	Projection();
	Projection(const Projection& other);
	Projection& operator=(const Projection& other);
	~Projection();

	Projection(const Film* film, const Hall* hall, const Date& date, const Time& t);

	bool reserve(size_t index);
	bool release(size_t index);
	bool isSeatFree(size_t index) const;
	size_t getFreeSeatsCount() const;

	void printProjectionInfo() const;
};

