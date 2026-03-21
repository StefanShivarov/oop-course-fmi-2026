#pragma once
#include <iostream>
class Date
{
private:
    int year = 1970;
    int month = 1;
    int day = 1;

    int DAYS_IN_MONTH[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    bool isLeapYear(int y) const
    {
        return (y % 4 == 0) && (y % 100 != 0 || y % 400 == 0);
    }

    int getMaxDaysForMonth(int y, int m) const
    {
        if (m < 1 || m > 12)
        {
            return 0;
        }

        if (m == 2 && isLeapYear(y))
        {
            return 29;
        }

        return DAYS_IN_MONTH[m - 1];
    }

    bool isValidCombination(int y, int m, int d) const
    {
        if (y < 1)
        {
            return false;
        }

        if (m < 1 || m > 12)
        {
            return false;
        }

        int maxDays = getMaxDaysForMonth(y, m);
        if (d < 1 || d > maxDays)
        {
            return false;
        }

        return true;
    }

public:
    bool setAll(int y, int m, int d)
    {
        if (!isValidCombination(y, m, d))
        {
            return false;
        }

        year = y;
        month = m;
        day = d;
        return true;
    }

    bool setYear(int y)
    {
        if (!isValidCombination(y, month, day))
        {
            return false;
        }

        year = y;
        return true;
    }

    bool setMonth(int m)
    {
        if (!isValidCombination(year, m, day))
        {
            return false;
        }

        month = m;
        return true;
    }

    bool setDay(int d)
    {
        if (!isValidCombination(year, month, d))
        {
            return false;
        }

        day = d;
        return true;
    }

    int getYear() const
    {
        return year;
    }

    int getMonth() const
    {
        return month;
    }

    int getDay() const
    {
        return day;
    }
    Date()
    {
    }
    Date(int day, int month, int year) : day(1), month(1), year(1970)
    {
        if (isValidCombination(year, month, day))
        {
            this->year = year;
            this->month = month;
            this->day = day;
        }
    }
    void printDate() const
    {
        std::cout << "\nDate: "<<day<<"."<<month<<"."<<year;
    }
};
