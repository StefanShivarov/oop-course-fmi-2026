#pragma once
class Hall {
private:
	static unsigned totalHalls;
	unsigned id;
	unsigned seatsCount;

public:
	Hall(int seats);

	unsigned getId() const;
	unsigned getSeatsCount() const;
};

