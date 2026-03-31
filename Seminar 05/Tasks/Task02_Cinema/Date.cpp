#include "Date.h"
#include <print>

Date::Date(unsigned day, unsigned month, unsigned year) {
    setYear(year);
    setMonth(month);
    setDay(day);
}

unsigned Date::getYear() const {
    return year;
}

unsigned Date::getMonth() const {
    return month;
}

unsigned Date::getDay() const {
    return day;
}

void Date::setYear(unsigned year) {
    unsigned previousValue = getYear();
    bool leapYear = isLeapYear(year);

    if (leapYear) {
        MAX_DAYS_PER_MONTH[1] = 29;
    } else {
        MAX_DAYS_PER_MONTH[1] = 28;
    }

    this->year = year;

    if (!isValid()) {
        if (leapYear) {
            MAX_DAYS_PER_MONTH[1] = 28;
        } else {
            MAX_DAYS_PER_MONTH[1] = 29;
        }
        this->year = previousValue;
    }
}

void Date::setMonth(unsigned month) {
    unsigned previousValue = getMonth();
    this->month = month;
    if (!isValid()) {
        this->month = previousValue;
    }
}

void Date::setDay(unsigned day) {
    unsigned previousValue = getDay();
    this->day = day;
    if (!isValid()) {
        this->day = previousValue;
    }
}

bool Date::isValid() const {
    return !((month == 0 || month > 12) ||
        (day == 0 || day > MAX_DAYS_PER_MONTH[month - 1]) ||
        (year == 0) ||
        (year == 1916 && month == 4 && day < 14)); // due to the transition of Julian to Gregorian, weird stuff :D
}

bool Date::isLeapYear(unsigned year) const {
    if (year <= 1916) {
        return year % 4 == 0;
    }
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int compare(const Date& lhs, const Date& rhs) {
    if (lhs.getYear() == rhs.getYear()) {
        if (lhs.getMonth() == rhs.getMonth()) {
            return lhs.getDay() - rhs.getDay();
        }
        return lhs.getMonth() - rhs.getMonth();
    }
    return lhs.getYear() - rhs.getYear();
}

void printDate(const Date& date, std::ostream& os) {
    println(os, "{:02}/{:02}/{}", date.getDay(), date.getMonth(), date.getYear());
}
