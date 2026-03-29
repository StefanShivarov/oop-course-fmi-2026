#include "Time.h"
#include <print>

void Time::recalculate() {
    hours = totalSeconds / 3600;
    minutes = (totalSeconds % 3600) / 60;
    seconds = totalSeconds % 60;
    validTotalSeconds = true;
}

Time::Time(unsigned hours, unsigned minutes): Time(hours, minutes, 0) {
}

Time::Time(unsigned hours, unsigned minutes, unsigned seconds) {
    setHours(hours);
    setMinutes(minutes);
    setSeconds(seconds);
}

unsigned Time::toSeconds() const {
    if (validTotalSeconds) {
        return totalSeconds;
    }

    totalSeconds = seconds + minutes * 60 + hours * 3600;
    validTotalSeconds = true;
    return totalSeconds;
}

void Time::addSeconds(int secondsDelta) {
    totalSeconds = this->toSeconds();
    totalSeconds += secondsDelta;
    recalculate();
}

bool Time::isBefore(const Time& other) const {
    return this->toSeconds() < other.toSeconds();
}

bool Time::isAfter(const Time& other) const {
    return this->toSeconds() > other.toSeconds();
}

unsigned Time::getHours() const {
    return hours;
}

unsigned Time::getMinutes() const {
    return minutes;
}

unsigned Time::getSeconds() const {
    return seconds;
}

bool Time::setHours(unsigned hours) {
    if (hours > 23) {
        return false;
    }
    this->hours = hours;
    validTotalSeconds = false;
    return true;
}

bool Time::setMinutes(unsigned minutes) {
    if (minutes > 59) {
        return false;
    }
    this->minutes = minutes;
    validTotalSeconds = false;
    return true;
}

bool Time::setSeconds(unsigned seconds) {
    if (seconds > 59) {
        return false;
    }
    this->seconds = seconds;
    validTotalSeconds = false;
    return true;
}

void printTime(const Time& time, std::ostream& os) {
    println(os, "{:02}:{:02}:{:02}",
        time.getHours(), time.getMinutes(), time.getSeconds());
}
