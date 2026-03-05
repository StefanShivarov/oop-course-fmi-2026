#include <iostream>
#include <fstream>
#include <print>
#include "Time.h"

namespace Constants {
    constexpr int MinHours = 0;
    constexpr int MaxHours = 23;
    constexpr int MinMinutes = 0;
    constexpr int MaxMinutes = 59;
    constexpr int MinSeconds = 0;
    constexpr int MaxSeconds = 59;
    constexpr int MinutesInHour = 60;
    constexpr int SecondsInMinute = 60;
    constexpr int SecondsInHour = 60 * SecondsInMinute;
    constexpr int MaxTimeInSeconds = 24 * SecondsInHour;
    constexpr int BufferSize = 32;
    constexpr char FileName[10] = "times.txt";
    constexpr int ValidTimestampLength = 8;
}

bool Time::validateTimestamp(const char* timestamp) {
    if (std::strlen(timestamp) != Constants::ValidTimestampLength) return false;
    if (timestamp[2] != ':' || timestamp[5] != ':') return false;

    for (int i = 0; i < Constants::ValidTimestampLength; i++) {
        if (i == 2 || i == 5) continue;

        if (!std::isdigit(timestamp[i])) return false;
    }

    int hours = (timestamp[0] - '0') * 10 + (timestamp[1] - '0');
    int minutes = (timestamp[3] - '0') * 10 + (timestamp[4] - '0');
    int seconds = (timestamp[6] - '0') * 10 + (timestamp[7] - '0');

    if (
        hours < Constants::MinHours || hours > Constants::MaxHours ||
        minutes < Constants::MinMinutes || minutes > Constants::MaxMinutes ||
        seconds < Constants::MinSeconds || seconds > Constants::MaxSeconds) {
        return false;
    }

    return true;
}

Time::Time(int hours, int minutes, int seconds)
{
    setAll(hours, minutes, seconds);
}

int Time::getHours() const {
    return hours;
}

void Time::setHours(int hours) {
    if (hours < Constants::MinHours || hours > Constants::MaxHours) return;

    this->hours = hours;
}

int Time::getMinutes() const {
    return minutes;
}

void Time::setMinutes(int minutes) {
    if (minutes < Constants::MinMinutes || minutes > Constants::MaxMinutes) return;

    this->minutes = minutes;
}

int Time::getSeconds() const {
    return seconds;
}

void Time::setSeconds(int seconds) {
    if (seconds < Constants::MinSeconds || seconds > Constants::MaxSeconds) return;

    this->seconds = seconds;
}

void Time::setAll(int hours, int minutes, int seconds) {
    setHours(hours);
    setMinutes(minutes);
    setSeconds(seconds);
}

int Time::toSeconds() const {
    return hours * Constants::SecondsInHour + minutes * Constants::SecondsInMinute + seconds;
}

void Time::addSeconds(int delta) {
    if (delta <= 0) return;
    int totalSeconds = toSeconds() + delta;
    totalSeconds %= Constants::MaxTimeInSeconds;

    hours = totalSeconds / Constants::SecondsInHour;
    totalSeconds %= Constants::SecondsInHour;

    minutes = totalSeconds / Constants::SecondsInMinute;
    seconds = totalSeconds % Constants::SecondsInMinute;
}

bool Time::isBefore(const Time& other) const {
    if (hours < other.hours) return true;
    if (hours > other.hours) return false;

    if (minutes < other.minutes) return true;
    if (minutes > other.minutes) return false;

    return seconds < other.seconds;
}

bool Time::isAfter(const Time& other) const {
    if (hours > other.hours) return true;
    if (hours < other.hours) return false;

    if (minutes > other.minutes) return true;
    if (minutes < other.minutes) return false;

    return seconds > other.seconds;
}

void Time::readFromStream(std::istream& is) {
    char buffer[Constants::BufferSize];
    is.getline(buffer, Constants::BufferSize);

    if (!validateTimestamp(buffer)) return;

    int hours = (buffer[0] - '0') * 10 + (buffer[1] - '0');
    int minutes = (buffer[3] - '0') * 10 + (buffer[4] - '0');
    int seconds = (buffer[6] - '0') * 10 + (buffer[7] - '0');

    setAll(hours, minutes, seconds);
}

void Time::writeToStream(std::ostream& os) const {
    std::print(os, "{:02}:{:02}:{:02}", hours, minutes, seconds);
}