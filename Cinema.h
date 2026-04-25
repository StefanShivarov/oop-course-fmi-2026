#pragma once

#include "Projection.h"
#include <cstring>
#pragma warning (disable: 4996)

class Cinema {
private:
	char* name;
	unsigned size;
	unsigned capacity;
	Projection* projections;

	void copyDynamicMemory(const Cinema& other);
	void freeDynamicMemory();
	void resize();

public:
	Cinema() = delete;
	Cinema(const char* name);
	Cinema(const Cinema& other);
	Cinema& operator=(const Cinema& other);
	~Cinema();

	void addProjection(const Projection& projection);
	void removeProjection(unsigned id);
	void displayProjections() const;
};

