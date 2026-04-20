#pragma once
#include <iostream>
#include <cstring>
#pragma warning(disable: 4996)

class Date {
	unsigned MAX_DAYS_PER_MONTH[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	unsigned day = 1;
	unsigned month = 1;
	unsigned year = 1;

	bool isLeap(unsigned year);
	bool isValid();
public:
	Date() = default;
	Date(unsigned d, unsigned m, unsigned y);

	unsigned getDay() const;
	unsigned getMonth() const;
	unsigned getYear() const;

	void setDay(const unsigned day);
	void setMonth(const unsigned month);
	void setYear(const unsigned year);

};

void printDate(const Date& date, std::ostream& os = std::cout);