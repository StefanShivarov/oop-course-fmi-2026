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
    unsigned previousValue = this->year;
    this->year = year;

    if (!isValid()) {
        this->year = previousValue;
    }
}

void Date::setMonth(unsigned month) {
    unsigned previousValue = this->month;
    this->month = month;

    if (!isValid()) {
        this->month = previousValue;
    }
}

void Date::setDay(unsigned day) {
    unsigned previousValue = this->day;
    this->day = day;

    if (!isValid()) {
        this->day = previousValue;
    }
}

bool Date::isValid() const {
    return !((month == 0 || month > 12) ||
        (day == 0 || day > getDaysInMonth(month, year)) ||
        (year == 0) ||
        (year == 1916 && month == 4 && day < 14));
}

bool Date::isLeapYear(unsigned year) const {
    if (year <= 1916) {
        return year % 4 == 0;
    }

    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

unsigned Date::getDaysInMonth(unsigned month, unsigned year) {
    static const unsigned DAYS_IN_MONTH[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (month == 0 || month > 12) {
        return 0;
    }

    bool leapYear;
    if (year <= 1916) {
        leapYear = year % 4 == 0;
    } else {
        leapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    if (month == 2 && leapYear) {
        return 29;
    }

    return DAYS_IN_MONTH[month - 1];
}

unsigned Date::daysFromStartOfYear() const {
    unsigned result = 0;

    for (unsigned m = 1; m < month; m++) {
        result += getDaysInMonth(m, year);
    }

    result += day - 1;
    return result;
}

unsigned Date::daysFromEpoch() const {
    unsigned result = 0;

    for (unsigned y = 1; y < year; y++) {
        result += isLeapYear(y) ? 366 : 365;
    }

    result += daysFromStartOfYear();
    return result;
}

int Date::differenceInDays(const Date& lhs, const Date& rhs) {
    return (int)lhs.daysFromEpoch() - (int)rhs.daysFromEpoch();
}

int compare(const Date& lhs, const Date& rhs) {
    if (lhs.getYear() < rhs.getYear()) return -1;
    if (lhs.getYear() > rhs.getYear()) return 1;

    if (lhs.getMonth() < rhs.getMonth()) return -1;
    if (lhs.getMonth() > rhs.getMonth()) return 1;

    if (lhs.getDay() < rhs.getDay()) return -1;
    if (lhs.getDay() > rhs.getDay()) return 1;

    return 0;
}

bool operator==(const Date& lhs, const Date& rhs) {
    return compare(lhs, rhs) == 0;
}

bool operator!=(const Date& lhs, const Date& rhs) {
    return !(lhs == rhs);
}

bool operator<(const Date& lhs, const Date& rhs) {
    return compare(lhs, rhs) < 0;
}

bool operator>(const Date& lhs, const Date& rhs) {
    return compare(lhs, rhs) > 0;
}

bool operator<=(const Date& lhs, const Date& rhs) {
    return !(lhs > rhs);
}

bool operator>=(const Date& lhs, const Date& rhs) {
    return !(lhs < rhs);
}

void printDate(const Date& date, std::ostream& os) {
    println(os, "{:02}/{:02}/{}", date.getDay(), date.getMonth(), date.getYear());
}
