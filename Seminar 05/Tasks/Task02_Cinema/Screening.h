#pragma once
#include <iostream>
#include "Movie.h"
#include "Hall.h"
#include "Time.h"
#include "Date.h"

class Screening {
private:
    static unsigned totalScreenings;
    unsigned id = 0;
    const Movie* movie = nullptr;
    const Hall* hall = nullptr;
    Date date;
    Time time;

    unsigned char* occupiedSeats = nullptr; // bit mask: 1 = busy, 0 = empty
    unsigned bytesCount = 0;

    void copyDynamicMemory(const Screening& other);
    void copyFrom(const Screening& other);
    void free();

    bool getBit(unsigned index) const;
    void setBit(unsigned index, bool value);

public:
    Screening() = default;
    Screening(const Movie* movie, const Hall* hall, const Date& date, const Time& time);
    Screening(const Screening& other);
    Screening& operator=(const Screening& other);
    ~Screening();

    unsigned getId() const;
    const Movie* getMovie() const;
    const Hall* getHall() const;
    Date getDate() const;
    Time getTime() const;

    bool reserveSeat(unsigned seatNumber);
    bool releaseSeat(unsigned seatNumber);
    bool isSeatFree(unsigned seatNumber) const;
    unsigned getFreeSeatsCount() const;
};

void printScreening(const Screening& movie, std::ostream& os = std::cout);
