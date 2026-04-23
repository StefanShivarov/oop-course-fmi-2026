#pragma once
#include <iostream>
#include <cstring>
#pragma warning(disable: 4996)

class Hall {
	static unsigned roomNumber;
	unsigned counter;
	unsigned seatsCount;

public:
	Hall(unsigned seatsCount);
	unsigned getRoomNumber() const;
	unsigned getSeatsCount() const;
};

void printHall(const Hall& hall, std::ostream& os = std::cout);