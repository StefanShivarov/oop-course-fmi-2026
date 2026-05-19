#pragma once
#include <ostream>

class Time {
public:
    explicit Time(unsigned hours = 0, unsigned minutes = 0);
    Time(unsigned hours, unsigned minutes, unsigned seconds);

    unsigned getHours() const;
    unsigned getMinutes() const;
    unsigned getSeconds() const;

    bool setHours(unsigned hours);
    bool setMinutes(unsigned minutes);
    bool setSeconds(unsigned seconds);

    unsigned toSeconds() const;
    unsigned toMinutes() const;

    void addSeconds(int secondsDelta);

    static int differenceInSeconds(const Time& lhs, const Time& rhs);
    static int differenceInMinutes(const Time& lhs, const Time& rhs);

private:
    unsigned hours = 0;
    unsigned minutes = 0;
    unsigned seconds = 0;

    mutable unsigned totalSeconds = 0;
    mutable bool validTotalSeconds = false;

    void recalculate();
};

void printTime(const Time& time, std::ostream& os);

bool operator==(const Time& lhs, const Time& rhs);
bool operator!=(const Time& lhs, const Time& rhs);
bool operator<(const Time& lhs, const Time& rhs);
bool operator>(const Time& lhs, const Time& rhs);
bool operator<=(const Time& lhs, const Time& rhs);
bool operator>=(const Time& lhs, const Time& rhs);