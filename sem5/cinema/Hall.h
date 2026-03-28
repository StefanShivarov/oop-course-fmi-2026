#pragma once
class Hall
{
	int id = 0;
	size_t capacitySeats = 0;


public:
	Hall();
	Hall(int id, size_t capacitySeats);

	void printHall() const;
	size_t getCapacity() const;
};

