#include "Screening.h"

unsigned Screening::totalScreenings = 0;

void Screening::copyFrom(const Screening& other) {
    id = other.id;
    movie = other.movie;
    hall = other.hall;
    date = other.date;
    time = other.time;
    bytesCount = other.bytesCount;
    copyDynamicMemory(other);
}

void Screening::copyDynamicMemory(const Screening& other) {
    occupiedSeats = new unsigned char[other.bytesCount];
    for (unsigned i = 0; i < other.bytesCount; i++) {
        occupiedSeats[i] = other.occupiedSeats[i];
    }
}

void Screening::free() {
    delete[] occupiedSeats;
    occupiedSeats = nullptr;
    bytesCount = 0;
}

bool Screening::getBit(unsigned index) const {
    unsigned byteIndex = index / 8;
    unsigned bitIndex = index % 8;
    return (occupiedSeats[byteIndex] & (1 << bitIndex)) != 0;
}

void Screening::setBit(unsigned index, bool value) {
    unsigned byteIndex = index / 8;
    unsigned bitIndex = index % 8;

    if (value)
        occupiedSeats[byteIndex] |= (1 << bitIndex);
    else
        occupiedSeats[byteIndex] &= ~(1 << bitIndex);
}

Screening::Screening(const Movie* movie, const Hall* hall, const Date& date, const Time& time)
    : id(++totalScreenings), movie(movie), hall(hall), date(date), time(time) {
    unsigned seatsCount = hall->getSeatsCount();
    bytesCount = (seatsCount + 7) / 8; // calculating the amount of bytes needed to store
                                       // seatsCount amount of bits
    occupiedSeats = new unsigned char[bytesCount];
    for (unsigned i = 0; i < bytesCount; i++) {
        occupiedSeats[i] = 0;
    }
}

Screening::Screening(const Screening& other)
    : id(++totalScreenings), movie(other.movie), hall(other.hall), date(other.date), time(other.time),
      bytesCount(other.bytesCount) {
    copyDynamicMemory(other);
}

Screening& Screening::operator=(const Screening& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Screening::~Screening() {
    free();
}

unsigned Screening::getId() const {
    return id;
}

const Movie* Screening::getMovie() const {
    return movie;
}

const Hall* Screening::getHall() const {
    return hall;
}

Date Screening::getDate() const {
    return date;
}

Time Screening::getTime() const {
    return time;
}

bool Screening::reserveSeat(unsigned seatNumber) {
    if (!hall || seatNumber == 0 || seatNumber > hall->getSeatsCount()) {
        return false;
    }

    unsigned index = seatNumber - 1;
    if (getBit(index)) {
        return false;
    }

    setBit(index, true);
    return true;
}

bool Screening::releaseSeat(unsigned seatNumber) {
    if (!hall || seatNumber == 0 || seatNumber > hall->getSeatsCount()) {
        return false;
    }

    unsigned index = seatNumber - 1;
    if (!getBit(index)) {
        return false;
    }

    setBit(index, false);
    return true;
}

bool Screening::isSeatFree(unsigned seatNumber) const {
    if (!hall || seatNumber == 0 || seatNumber > hall->getSeatsCount()) {
        return false;
    }

    unsigned index = seatNumber - 1;
    return !getBit(index);
}

unsigned Screening::getFreeSeatsCount() const {
    if (!hall) {
        return 0;
    }

    unsigned freeSeats = 0;
    unsigned seatsCount = hall->getSeatsCount();

    for (unsigned i = 1; i <= seatsCount; i++) {
        if (isSeatFree(i)) {
            freeSeats++;
        }
    }
    return freeSeats;
}

void printScreening(const Screening& screening, std::ostream& os) {
    os << "Screening ID: " << screening.getId() << '\n';
    if (screening.getMovie()) {
        os << "Movie: ";
        printMovie(*screening.getMovie(), os);
    }

    if (screening.getHall()) {
        os << "Hall: ";
        printHall(*screening.getHall(), os);

        os << "Free seats: " << screening.getFreeSeatsCount()
            << "/" << screening.getHall()->getSeatsCount() << '\n';
    }

    os << "Date: ";
    printDate(screening.getDate(), os);
    os << '\n';

    os << "Time: ";
    printTime(screening.getTime(), os);
    os << '\n';
}
