#pragma once
class Hall
{
private:
	static size_t nextId;
	size_t id = 0;
	size_t countSeats = 0;

public:
	Hall();
	Hall(size_t countSeats);

	void setCountSeats(size_t countSeats);

	size_t getId()const;
	size_t getCountSeats()const;

	void printHall()const;
};

