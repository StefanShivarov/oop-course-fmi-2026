#include "Screening.h"
#include <iostream>
#include <cstring>
#pragma warning(disable: 4996)

unsigned Screening::totalScreenings = 0;

void Screening::copyDynamicMemory(const Screening& other)
{
	occupiedSeats = new unsigned char[other.bytesCount];
	for (unsigned i = 0; i < other.bytesCount; i++) {
		occupiedSeats[i] = other.occupiedSeats[i];
	}
}

void Screening::free()
{
	delete[] occupiedSeats;
	occupiedSeats = nullptr;
	bytesCount = 0;
}

void Screening::copyFrom(const Screening& other)
{
	movie = other.movie;
	date = other.date;
	time = other.time;
	hall = other.hall;
	id = other.id;
	bytesCount = other.bytesCount;
	copyDynamicMemory(other);
}

bool Screening::getBit(unsigned index) const
{
	unsigned byteIndex = index / 8;
	unsigned bitIndex = index % 8;
	return (occupiedSeats[byteIndex] & (1 << bitIndex)) != 0;
}

void Screening::setBit(unsigned index, bool value)
{
	unsigned byteIndex = index / 8;
	unsigned bitIndex = index % 8;

	if (value)
		occupiedSeats[byteIndex] |= (1 << bitIndex);
	else
		occupiedSeats[byteIndex] &= ~(1 << bitIndex);
}

Screening::Screening(const Movie* movie, const Hall* hall, const Date& date, const Time& time) :
	movie(movie), hall(hall), date(date), time(time), id(++totalScreenings)
{
	unsigned seatsCount = hall->getSeatsCount();
	bytesCount = (seatsCount + 7) / 8;

	occupiedSeats = new unsigned char[bytesCount];
	for (unsigned i = 0; i < bytesCount; i++) {
		occupiedSeats[i] = 0;
	}
}

Screening::Screening(const Screening& other)
{
	copyFrom(other);
}

Screening& Screening::operator=(const Screening& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Screening::~Screening()
{
	free();
}

const Movie* Screening::getMovie() const
{
	return movie;
}

const Hall* Screening::getHall() const
{
	return hall;
}

Date Screening::getDate() const
{
	return date;
}

Time Screening::getTime() const
{
	return time;
}

unsigned Screening::getId() const
{
	return id;
}

bool Screening::isSeatFree(unsigned seatNumber) const
{
	if (!hall || seatNumber == 0 || seatNumber > hall->getSeatsCount()) {
		return false;
	}

	unsigned index = seatNumber - 1;
	return !getBit(index);
}

unsigned Screening::getFreeSeatsCount() const
{
	if (!hall) return 0;
	unsigned freeseats = 0;
	unsigned totalSeat = hall->getSeatsCount();
	for (unsigned i = 1; i <= totalSeat; i++) {
		if (isSeatFree(i))
			freeseats++;
	}
	return freeseats;
}

bool Screening::reserveSeat(unsigned seatNumber)
{
	if (!hall || seatNumber == 0 || seatNumber > hall->getSeatsCount()) {
		return false;
	}

	unsigned index = seatNumber - 1;
	if (getBit(index)) {
		return false;
	}

	setBit(index, true);
	return true;
}

bool Screening::releaseSeat(unsigned seatNumber)
{
	if (!hall || seatNumber == 0 || seatNumber > hall->getSeatsCount()) {
		return false;
	}

	unsigned index = seatNumber - 1;
	if (!getBit(index)) {
		return false;
	}

	setBit(index, false);
	return true;
}

void printScreening(const Screening& screening, std::ostream& os)
{
	os << "Screening ID: " << screening.getId() << '\n';
	if (screening.getMovie()) {
		os << "Movie: ";
		printMovie(*screening.getMovie(), os);
	}

	if (screening.getHall()) {
		os << "Hall: ";
		printHall(*screening.getHall(), os);

		os << "Free seats: " << screening.getFreeSeatsCount()
			<< "/" << screening.getHall()->getSeatsCount() << '\n';
	}

	os << "Date: ";
	printDate(screening.getDate(), os);
	os << '\n';

	os << "Time: ";
	printTime(screening.getTime(), os);
	os << '\n';
}
