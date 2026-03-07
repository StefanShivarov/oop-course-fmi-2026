#include <iostream>
#include <fstream>
#include <print>

#pragma once
class Time {
private:
    int hours = 0;
    int minutes = 0;
    int seconds = 0;

    bool validateTimestamp(const char* timestamp);

public:
	Time() = default;
    Time(int hours, int minutes, int seconds);
    int getHours() const;
    void setHours(int hours);
    int getMinutes() const;
    void setMinutes(int minutes);
    int getSeconds() const;
    void setSeconds(int seconds);
    void setAll(int hours, int minutes, int seconds);
    int toSeconds() const;
    void addSeconds(int delta);
    bool isBefore(const Time& other) const;
    bool isAfter(const Time& other) const;
    void readFromStream(std::istream& is = std::cin);
    void writeToStream(std::ostream& os = std::cout) const;
};