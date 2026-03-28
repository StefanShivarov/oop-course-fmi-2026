#pragma once
#include "Projection.h"
#include "Hall.h"
#include "Film.h"

class CinemaProgram
{
	Projection* projections = nullptr;

	size_t capacity = 0;
	size_t count = 0;

	void free();
	void copyFrom(const CinemaProgram& other);
	void resize();

public:
	CinemaProgram();
	CinemaProgram(const CinemaProgram& other);
	CinemaProgram& operator=(const CinemaProgram& other);
	~CinemaProgram();

	void addProjection(const Projection& projection);
	void removeProjection(size_t index);
	void printProgram() const;
};

