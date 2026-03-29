#pragma once
#include <iostream>

class Time {
private:
    int hours, minutes, seconds;
public:
    int getHours() const;
    int getMinutes() const;
    int getSeconds() const;
    void setHours(int h);
    void setMinutes(int m);
    void setSeconds(int s);
    int toSeconds() const;
    void addSeconds(int delta);
    bool isBefore(const Time& other) const;
    bool isAfter(const Time& other) const;
    void readTime(std::istream& in);
    void writeTime(std::ostream& out) const;
    bool isValidTime(int hours, int minutes, int seconds) const;
};

void swapTimes(Time& time1, Time& time2);
void sortTimes(Time* times, int n);