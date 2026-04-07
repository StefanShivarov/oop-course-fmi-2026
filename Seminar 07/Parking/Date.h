#pragma once
#include <ostream>

class Date {
public:
    Date(unsigned day = 1, unsigned month = 1, unsigned year = 2000);

    unsigned getYear() const;
    unsigned getMonth() const;
    unsigned getDay() const;

    void setYear(unsigned year);
    void setMonth(unsigned month);
    void setDay(unsigned day);

    bool isValid() const;
    bool isLeapYear(unsigned year) const;

    unsigned daysFromStartOfYear() const;
    unsigned daysFromEpoch() const;

    static int differenceInDays(const Date& lhs, const Date& rhs);
    static unsigned getDaysInMonth(unsigned month, unsigned year);

private:
    unsigned day = 1;
    unsigned month = 1;
    unsigned year = 2000;
};

int compare(const Date& lhs, const Date& rhs);
void printDate(const Date& date, std::ostream& os);

bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator<(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);