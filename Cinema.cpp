#include "Cinema.h"
#include<iostream>
#include<print>


Cinema::Cinema():screenings(nullptr), screeningsCount(0), capacity(INITIAL_CAPACITY)
{
	screenings = new Screening[capacity];
}

void Cinema::copyFrom(const Cinema& other)
{
	screeningsCount = other.screeningsCount;
	capacity = other.capacity;
	screenings = new Screening[capacity];
	for (size_t i = 0; i < screeningsCount; i++)
	{
		screenings[i] = other.screenings[i];
	}
}

void Cinema::free()
{
	delete[]screenings;
	screenings = nullptr;
	screeningsCount = 0;
	capacity = 0;
}

Cinema::Cinema(const Cinema& other)
{
	copyFrom(other);
}

Cinema& Cinema::operator=(const Cinema& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Cinema::~Cinema()
{
	free();
}

void Cinema::resize(size_t newCapacity)
{
	capacity = newCapacity;
	Screening* newScreenings = new Screening[capacity];

	for (size_t i = 0;i < screeningsCount;i++)
	{
		newScreenings[i] = screenings[i];
	}
	delete[]screenings;
	screenings = newScreenings;
}

void Cinema::printCinema()const
{
	for (size_t i = 0;i < screeningsCount;i++)
	{
		screenings[i].printScreening();
		std::println();
	}
}

void Cinema::addScreening(const Screening& screening)
{
	if (screeningsCount == capacity)
	{
		resize(capacity * 2);
	}

	screenings[screeningsCount++] = screening;
}

void Cinema::removeScreening(const size_t id)
{
	for (size_t i = 0;i < screeningsCount;i++)
	{
		if (screenings[i].getId() == id)
		{
			for (size_t j = i + 1;j < screeningsCount;j++)
			{
				screenings[j - 1] = screenings[j];
			}
			screeningsCount--;
			return;
		}
	}
}

void Cinema::printById(const size_t id)const
{
	for (size_t i = 0;i < screeningsCount;i++)
	{
		if (screenings[i].getId() == id)
		{
			screenings[i].printScreening();
			return;
		}
	}

	std::println("Screening not found in cinema.");
}

Screening* Cinema::getById(size_t id)const
{
	for (size_t i = 0; i < screeningsCount; i++)
	{
		if (screenings[i].getId() == id)
		{
			return &screenings[i];
		}
	}
	return nullptr;
}