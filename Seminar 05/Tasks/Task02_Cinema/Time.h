#pragma once
#include <iostream>

class Time {
private:
    unsigned hours = 0;
    unsigned minutes = 0;
    unsigned seconds = 0;

    mutable bool validTotalSeconds = false;
    mutable unsigned totalSeconds = 0;

    void recalculate();

public:
    Time() = default;
    Time(unsigned hours, unsigned minutes, unsigned seconds);
    Time(unsigned hours, unsigned minutes);

    unsigned toSeconds() const;
    void addSeconds(int secondsDelta);

    bool isBefore(const Time& other) const;
    bool isAfter(const Time& other) const;

    unsigned getHours() const;
    unsigned getMinutes() const;
    unsigned getSeconds() const;

    bool setHours(unsigned hours);
    bool setMinutes(unsigned minutes);
    bool setSeconds(unsigned seconds);
};

void printTime(const Time& time, std::ostream& os = std::cout);
