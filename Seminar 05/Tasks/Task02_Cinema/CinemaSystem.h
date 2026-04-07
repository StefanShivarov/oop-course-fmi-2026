#pragma once
#include "Screening.h"

class CinemaSystem {
private:
    Screening* screenings = nullptr;
    unsigned screeningsCount;
    unsigned screeningsCapacity;

    void resizeScreenings(unsigned newCapacity);
    Screening* findScreeningById(unsigned screeningId);
    const Screening* findScreeningById(unsigned screeningId) const;

    void copyDynamicMemory(const CinemaSystem& other);
    void copyFrom(const CinemaSystem& other);
    void free();

public:
    CinemaSystem();
    CinemaSystem(const CinemaSystem& other);
    CinemaSystem& operator=(const CinemaSystem& other);
    ~CinemaSystem();

    bool addScreening(const Screening& screening);
    bool addScreening(const Movie* movie, const Hall* hall, const Date& date, const Time& time);
    bool removeScreening(unsigned screeningId);

    bool reserveSeat(unsigned screeningId, unsigned seatNumber);
    bool releaseSeat(unsigned screeningId, unsigned seatNumber);
    bool isSeatFree(unsigned screeningId, unsigned seatNumber) const;
    unsigned getFreeSeatsCount(unsigned screeningId) const;

    const Screening* getScreeningById(unsigned screeningId) const;

    unsigned getScreeningsCount() const;
    const Screening* getScreeningAt(unsigned index) const;
};

void printAllScreenings(const CinemaSystem& c, std::ostream& os = std::cout);
