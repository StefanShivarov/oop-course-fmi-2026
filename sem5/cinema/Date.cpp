#include "Date.h"
#include <iostream>

bool Date::isLeapYear(int y) const
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Date::getMaxDaysInMonth(int m, int y) const
{
    if (m == 2) {
        if (isLeapYear(y)) {
            return 29;
        }
        else {
            return 28;
        }
    }

    if (m == 4 || m == 6 || m == 9 || m == 11) {
        return 30;
    }

    return 31;
}

bool Date::isValidDate(int d, int m, int y) const
{
    if (y <= 0) return false;
    if (m < 1 || m > 12) return false;
    if (d < 1 || d > getMaxDaysInMonth(m, y)) return false;

    return true;
}

Date::Date() : day(1), month(1), year(2000)
{
}

Date::Date(int day, int month, int year)
{
    if (isValidDate(day, month, year)) {
        this->day = day;
        this->month = month;
        this->year = year;
    }
}

void Date::printDate() const
{
    std::cout << day << "." << month << "." << year << '\n';
}
