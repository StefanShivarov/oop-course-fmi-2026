#pragma once
#include <iostream>
#include <cstring>
#pragma warning(disable: 4996)
#include "Screening.h"

class CinemaSystem {
	Screening* screenings;
	unsigned screeningsCount;
	unsigned screeningsCapacity;
	const unsigned int DEFAULT_RECIZE = 10;

	void recize();
	Screening* findScreeningById(unsigned screeningId);
	const Screening* findScreeningById(unsigned screeningId) const;

	void copyDynamicMemory(const CinemaSystem& other);
	void free();
	void copyFrom(const CinemaSystem& other);
public:
	CinemaSystem();
	CinemaSystem(const CinemaSystem& other);
	CinemaSystem& operator=(const CinemaSystem& other);
	~CinemaSystem();

	bool addScreening(const Screening& screening);
	bool addScreening(const Movie* movie, const Hall* hall, const Date& date, const Time& time);
	bool removeScreening(unsigned screeningId);

	bool reserveSeat(unsigned screeningId, unsigned seatNumber);
	bool releaseSeat(unsigned screeningId, unsigned seatNumber);
	bool isSeatFree(unsigned screeningId, unsigned seatNumber) const;
	unsigned getFreeSeatsCount(unsigned screeningId) const;

	const Screening* getScreeningById(unsigned screeningId) const;

	unsigned getScreeningsCount() const;
	const Screening* getScreeningAt(unsigned index) const;
};

void printAllScreenings(const CinemaSystem& c, std::ostream& os = std::cout);