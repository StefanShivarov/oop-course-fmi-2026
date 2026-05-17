#pragma once
#include <iostream>
#include <cstring>
#pragma warning(disable: 4996)
#include "Movie.h"
#include "Hall.h"
#include "Time.h"
#include "Date.h"

class Screening {
	const Movie* movie = nullptr;
	const Hall* hall = nullptr;
	Date date;
	Time time;


	static unsigned totalScreenings;
	unsigned id;

	unsigned char* occupiedSeats = nullptr;
	unsigned bytesCount = 0;

	void copyDynamicMemory(const Screening& other);
	void free();
	void copyFrom(const Screening& other);

	bool getBit(unsigned index) const;
	void setBit(unsigned index, bool value);
public:
	Screening() = default;
	Screening(const Movie* movie, const Hall* hall, const Date& date, const Time& time);
	Screening(const Screening& other);
	Screening& operator=(const Screening& other);
	~Screening();

	const Movie* getMovie() const;
	const Hall* getHall() const;
	Date getDate() const;
	Time getTime() const;
	unsigned getId() const;
	unsigned getFreeSeatsCount() const;

	bool reserveSeat(unsigned seatNumber);
	bool releaseSeat(unsigned seatNumber);
	bool isSeatFree(unsigned seatNumber) const;
};

void printScreening(const Screening& screening, std::ostream& os = std::cout);