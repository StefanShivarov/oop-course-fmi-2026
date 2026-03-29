#pragma once
#include"Screening.h"

class Cinema
{
private:
	static const size_t INITIAL_CAPACITY = 16;
	Screening* screenings = nullptr;
	size_t screeningsCount = 0;
	size_t capacity = INITIAL_CAPACITY;

	void copyFrom(const Cinema& other);
	void free();
	void resize(size_t newCapacity);

public:
	Cinema();

	Cinema(const Cinema& other);
	Cinema& operator=(const Cinema& other);
	~Cinema();

	void addScreening(const Screening& screening);
	void removeScreening(const size_t id);
	
	void printById(const size_t id) const;
	void printCinema() const;

	Screening* getById(size_t id)const;
};

