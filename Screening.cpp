#define _CRT_SECURE_NO_WARNINGS
#include "Screening.h"
#include<cstring>
#include<print>

size_t Screening::nextId = 1;

Screening::Screening():film(nullptr),seats(nullptr),hall(nullptr),id(nextId++),seatsCount(0)
{
	t.hour = 0;
	t.min = 0;
	
	date = new char[1];
	date[0] = '\0';
}

Screening::Screening(Film* film, Hall* hall, const char* date, Time t):id(nextId++),
       film(film),hall(hall)
{
	setDate(date);
	setTime(t);
	seatsCount = hall->getCountSeats();
	seats = new bool[seatsCount] {false};
}

void Screening::copyFrom(const Screening& other)
{
	this->film = other.film;
	this->hall = other.hall;
	setDate(other.date);
	setTime(other.t);
	seatsCount = other.seatsCount;
	seats = new bool[seatsCount];

	for (size_t i = 0; i < seatsCount; i++)
	{
		seats[i] = other.seats[i];
	}
	id = other.id;
}

void Screening::free()
{
	delete[]date;
	date = nullptr;
	delete[]seats;
	seats = nullptr;
	seatsCount = 0;
}

Screening::Screening(const Screening& other)
{
	copyFrom(other);
}

Screening& Screening::operator=(const Screening& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Screening::~Screening()
{
	free();
}


void Screening::setDate(const char* date)
{
	if (date == nullptr)
	{
		return;
	}

	delete[] this->date;
	this->date = new char[strlen(date) + 1];
	strcpy(this->date, date);
}

void Screening::setTime(Time t)
{
	if (t.hour < 0 || t.min < 0 || t.min>60)
	{
		return;
	}
	this->t = t;
}

void Screening::printScreening()const
{
	std::println("Screening ID: {}", id);
	film->printFilm();
	hall->printHall();
	std::println("Date:{}", date);
	t.printTime();
	std::println("Free seats: {}", freeSeatsCount());
}

const Film* Screening::getFilm()const
{
	return film;
}

const Hall* Screening::getHall()const
{
	return hall;
}

const size_t Screening::getId()const
{
	return id;
}

void Screening::reserveSeat(size_t indexSeat)
{
	if (seats == nullptr || indexSeat >= seatsCount)
	{
		return;
	}

	seats[indexSeat] = true;
}

void Screening::freeSeat(size_t indexSeat)
{
	if (seats == nullptr || indexSeat >= seatsCount)
	{
		return;
	}

	seats[indexSeat] = false;
}

bool Screening::isSeatFree(size_t indexSeat)const
{
	return indexSeat < seatsCount && !seats[indexSeat];
}

size_t Screening::freeSeatsCount()const
{
	size_t count = 0;
	for (size_t i = 0;i < seatsCount;i++)
	{
		if (isSeatFree(i))
		{
			count++;
		}
	}
	return count;
}