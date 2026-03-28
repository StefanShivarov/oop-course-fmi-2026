#include "Projection.h"
#include "Hall.h"
#include "Film.h"
#include "Date.h"
#include <cstring>
#include <iostream>
#pragma warning(disable : 4996)

Projection::Projection() : film(nullptr), hall(nullptr), taken(nullptr)
{
}

void Projection::free() 
{
	delete[] taken;
	taken = nullptr;
}


void Projection::copyFrom(const Projection& other)
{
	film = other.film;
	hall = other.hall;
	date = other.date;
	t = other.t;

	size_t capacity = hall->getCapacity();

	if (other.taken != nullptr && other.hall != nullptr) {
		taken = new bool[capacity];
		for (size_t i = 0; i < capacity; i++)
		{
			taken[i] = other.taken[i];
		}
	}
	else{
		taken = nullptr;
	}

}

Projection::Projection(const Projection& other)
{
	copyFrom(other);
}

Projection& Projection::operator=(const Projection& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Projection::~Projection()
{
	free();
}

Projection::Projection(const Film* film, const Hall* hall, const Date& date, const Time& t)
	: film(film), hall(hall), date(date), t(t), taken(nullptr)
{
	if (hall != nullptr) {

		size_t capacity = hall->getCapacity();
		taken = new bool[capacity];

		for (size_t i = 0; i < capacity; i++)
		{
			taken[i] = false;
		}
	}
}

bool Projection::reserve(size_t index)
{
	if (!hall || !taken) return false;

	if (index >= hall->getCapacity()) {
		return false;
	}

	if (taken[index] == true) {
		return false;
	}

	taken[index] = true;

	return true;
}

bool Projection::release(size_t index)
{
	if (!hall || !taken) return false;

	if (index >= hall->getCapacity()) {
		return false;
	}

	if (taken[index] == false) {
		return false;
	}

	taken[index] = false;
	return true;
}

bool Projection::isSeatFree(size_t index) const
{
	if (!hall || !taken) return false;

	if (index >= hall->getCapacity()) {
		return false;
	}
	
	if (taken[index] == true) {
		return false;
	}

	return true;
}

size_t Projection::getFreeSeatsCount() const
{
	if (!hall || !taken) return 0;

	size_t countFree = 0;
	for (size_t i = 0; i < hall->getCapacity() ; i++)
	{
		if (isSeatFree(i)) {
			countFree++;
		}
	}
	return countFree;
}


void Projection::printProjectionInfo() const
{
	if (film != nullptr) {
		film->printFilm();
	}

	if (hall != nullptr) {
		hall->printHall();
	}

	date.printDate();
	t.printTime();
}
