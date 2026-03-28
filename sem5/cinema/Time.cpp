#include "Time.h"
#include <iostream>

bool Time::isValidTime(int h, int m) const
{
    if (h >= 0 && h < 24 && m >= 0 && m <= 59) {
        return true;
    }

    return false;
}

Time::Time() : hour(0),minutes(0)
{
}

Time::Time(int h, int m)
{
    if (isValidTime(h, m)) {
        this->hour = h;
        this->minutes = m;
    }
}

void Time::printTime() const
{
    std::cout << "Start at: " << hour << ":" << minutes << '\n';
}


