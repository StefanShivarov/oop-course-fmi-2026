#include "CinemaProgram.h"
#include <cstring>
#include<iostream>
#pragma warning(disable : 4996)

void CinemaProgram::resize() {
	capacity *= 2;
	Projection* temp = new Projection[capacity];

	for (size_t i = 0; i < count; i++)
	{
		temp[i] = projections[i];
	}

	delete[] projections;
	projections = temp;
}


void CinemaProgram::free()
{
	delete[] projections;
	projections = nullptr;
}

void CinemaProgram::copyFrom(const CinemaProgram& other)
{
	capacity = other.capacity;
	count = other.count;

	if (other.projections != nullptr) {
		projections = new Projection[capacity];
		for (size_t i = 0; i < count; i++)
		{
			projections[i] = other.projections[i];
		}
	}
}


CinemaProgram::CinemaProgram() : capacity(2), count(0)
{
	projections = new Projection[capacity];
}

CinemaProgram::CinemaProgram(const CinemaProgram& other)
{
	copyFrom(other);
}

CinemaProgram& CinemaProgram::operator=(const CinemaProgram& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

CinemaProgram::~CinemaProgram()
{
	free();
}

void CinemaProgram::addProjection(const Projection& projection)
{
	if (count == capacity) {
		resize();
	}

	projections[count++] = projection;
}

void CinemaProgram::removeProjection(size_t index)
{
	projections[index] = projections[count - 1];
	count--;
	
}

void CinemaProgram::printProgram() const
{
	std::cout << "--- Cinema Program ---\n";
	for (size_t i = 0; i < count; i++)
	{
		projections[i].printProjectionInfo();
	}
}


