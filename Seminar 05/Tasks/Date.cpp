#include "Date.h"
#include <iostream>
#include <cstring>
#pragma warning(disable: 4996)

bool Date::isLeap(unsigned year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool Date::isValid()
{
    return !(day > MAX_DAYS_PER_MONTH[month - 1] || day < 1 || month > 12 || month < 1 || year < 0);
}

Date::Date(unsigned d, unsigned m, unsigned y)
{
    setDay(d);
    setMonth(m);
    setYear(y);
}

unsigned Date::getDay() const
{
    return day;
}

unsigned Date::getMonth() const
{
    return month;
}

unsigned Date::getYear() const
{
    return year;
}

void Date::setDay(const unsigned day)
{
    unsigned previous = getDay();
    this->day = day;
    if (!isValid())
        this->day = previous;
}

void Date::setMonth(const unsigned month)
{
    unsigned previous = getMonth();
    this->month = month;
    if (!isValid())
        this->month = previous;
}

void Date::setYear(const unsigned year)
{
    unsigned previous = getYear();
    if (isLeap(year)) {
        MAX_DAYS_PER_MONTH[1] = 29;
    }
    this->year = year;
    if (!isValid())
        this->year = previous;
    MAX_DAYS_PER_MONTH[1] = 28;
}

void printDate(const Date& date, std::ostream& os)
{
    os << date.getDay() << '.' << date.getMonth() << '.' << date.getYear() << '\n';
}
