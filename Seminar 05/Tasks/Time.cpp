#include "Time.h"
#include <iostream>
#include <cstring>
#pragma warning(disable: 4996)

void Time::recalculate()
{
	unsigned totalSeconds = toSeconds();
	hours = totalSeconds / 3600;
	minutes = (totalSeconds % 3600) / 60;
	seconds = totalSeconds % 60;
}

Time::Time(unsigned h, unsigned m, unsigned s) 
{
	setHours(h);
	setMinutes(m);
	setSeconds(s);
}

Time::Time(unsigned h, unsigned m) : Time(h, m, 0)
{
	
}

unsigned Time::toSeconds() const
{
	return hours * 3600 + minutes * 60 + seconds;
}

void Time::addSeconds(unsigned delta)
{
	unsigned total = toSeconds() + delta;
	recalculate();
}

bool Time::isBefore(const Time& other) const
{
	return other.toSeconds() > toSeconds();
}

bool Time::isAfter(const Time& other) const
{
	return other.toSeconds() < toSeconds();
}

void Time::setHours(unsigned hours)
{
	if (hours > 23) return;
	this->hours = hours;
}

void Time::setMinutes(unsigned minutes)
{
	if (minutes >59) return;
	this->minutes = minutes;
}

void Time::setSeconds(unsigned seconds)
{
	if (seconds > 59) return;
	this->seconds = seconds;
}

unsigned Time::getHours() const
{
	return hours;
}

unsigned Time::getMinutes() const
{
	return minutes;
}

unsigned Time::getSeconds() const
{
	return seconds;
}

void printTime(const Time& time, std::ostream& os)
{
	os << time.getHours() << ':' << time.getMinutes() << ':' << time.getSeconds() << '\n';
}
