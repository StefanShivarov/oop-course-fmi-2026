#pragma once
#include"Film.h"
#include"Hall.h"

class Screening
{
private:
	static size_t nextId;
	size_t id = 0;
	Film* film = nullptr;
	Hall* hall = nullptr;
	bool* seats = nullptr;
	size_t seatsCount = 0;
	char* date = nullptr;
	Time t;

	void copyFrom(const Screening& other);
	void free();

public:
	Screening();
	Screening( Film* film, Hall* hall, const char* date, Time t);

	Screening(const Screening& other);
	Screening& operator=(const Screening& other);
	~Screening();

	void setDate(const char* date);
	void setTime(Time t);

	const Film* getFilm()const;
	const Hall* getHall()const;
    const size_t getId()const;

	void reserveSeat(size_t indexSeat);
	void freeSeat(size_t indexSeat);
	bool isSeatFree(size_t indexSeat)const;
	size_t freeSeatsCount()const;

	void printScreening()const;
};

