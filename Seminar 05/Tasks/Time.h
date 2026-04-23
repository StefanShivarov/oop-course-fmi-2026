#pragma once
#include <iostream>
#include <cstring>
#pragma warning(disable: 4996)

class Time {
	unsigned hours = 0;
	unsigned minutes = 0;
	unsigned seconds = 0;

	void recalculate();
public:
	Time() = default;
	Time(unsigned h, unsigned m, unsigned s);
	Time(unsigned h, unsigned m);

	unsigned toSeconds() const;
	void addSeconds(unsigned delta);

	bool isBefore(const Time& other) const;
	bool isAfter(const Time& other) const;

	void setHours(unsigned hours);
	void setMinutes(unsigned minutes);
	void setSeconds(unsigned seconds);

	unsigned getHours() const;
	unsigned getMinutes() const;
	unsigned getSeconds() const;
};

void printTime(const Time& time, std::ostream& os = std::cout);