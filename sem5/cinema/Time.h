#pragma once
class Time
{
private:
	int hour = 0;
	int minutes = 0;

	bool isValidTime(int h, int m) const;

public:
	Time();
	Time(int h, int m);

	void printTime() const;

};

