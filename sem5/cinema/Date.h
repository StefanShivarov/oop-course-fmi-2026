#pragma once
class Date
{
private:
	int day = 1;
	int month = 1;
	int year = 2000;

	bool isLeapYear (int y) const;
	int getMaxDaysInMonth(int m, int y) const;
	bool isValidDate(int d, int m, int y) const;

public:
	Date();
	Date(int day, int month, int year);

	void printDate() const;
};

