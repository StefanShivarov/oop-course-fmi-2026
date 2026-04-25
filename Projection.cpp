#include "Projection.h"

void Projection::copyDynamicMemory(const Projection& other) {
    this->time = new char[std::strlen(other.time) + 1];
    std::strcpy(this->time, other.time);

    unsigned newSeatsCount = other.hall->getSeatsCount();
    reservations = new bool[newSeatsCount];

    for (int i = 0; i < newSeatsCount; i++) {
        reservations[i] = other.reservations[i];
    }
}

void Projection::freeDynamicMemory() {
    delete[] time;
    delete[] reservations;
}

Projection::Projection() : movie(nullptr), hall(nullptr), time(nullptr), reservations(nullptr), takenSeats(0) {}

Projection::Projection(Movie* m, Hall* h, const char* t) : id(++totalCount), movie(m), hall(h), takenSeats(0) {
    this->time = new char[std::strlen(t) + 1];
    std::strcpy(this->time, t);

    int seatsCount = hall->getSeatsCount();
    this->reservations = new bool[seatsCount]();
}

Projection::Projection(const Projection& other) : id(other.id), movie(other.movie), hall(other.hall), takenSeats(other.takenSeats){
    copyDynamicMemory(other);
}

Projection& Projection::operator=(const Projection & other) {
    if (this != &other) {
        this->id = other.id;
        this->movie = other.movie;
        this->hall = other.hall;
        this->takenSeats = other.takenSeats;

        freeDynamicMemory();
        copyDynamicMemory(other);
    }

    return *this;
}

Projection::~Projection() {
    freeDynamicMemory();
}

unsigned Projection::getId() {
    return id;
}

bool Projection::reserveSeat(unsigned number) {
    if (number < 1 || number > hall->getSeatsCount()) {
        std::cout << "Invalid seat!" << std::endl;
        return false;
    }

    if(!isSeatFree(number)) {
        std::cout << "Seat is already reserved!" << std::endl;
        return false;
    }

    this->reservations[number - 1] = true;
    takenSeats++;

    return true;
}

void Projection::freeSeat(unsigned number) {
    if (number < 1 || number > hall->getSeatsCount()) {
        std::cout << "Invalid seat!" << std::endl;
        return;
    }

    if (isSeatFree(number)) {
        std::cout << "Seat is already free!" << std::endl;
        return;
    }

    this->reservations[number - 1] = false;
    takenSeats--;

    return;
}

bool Projection::isSeatFree(unsigned number) const {
    if (number < 1 || number > hall->getSeatsCount()) {
        std::cout << "Invalid seat!" << std::endl;
        return false;
    }

    return !this->reservations[number - 1];
}

unsigned Projection::getFreeSeatsCount() const {
    return hall->getSeatsCount() - takenSeats;
}

void Projection::displayInformation() const {
    std::cout << "\n=======================\n";
    std::cout << "Projection ID: " << id << "\n";
    std::cout << "Movie: " << movie->getTitle() << " (" << movie->getGenre() << ")\n";
    std::cout << "Duration: " << movie->getDuration() << " mins\n";
    std::cout << "Ticket Price: $" << movie->getTickerPrice() << "\n";
    std::cout << "\n";
    std::cout << "Projection time: " << time << "\n";
    std::cout << "Hall ID: " << hall->getId() << "\n";

    unsigned totalSeats = hall->getSeatsCount();
    unsigned freeSeats = totalSeats - takenSeats;

    std::cout << "Seats: " << freeSeats << " free / " << totalSeats << " total\n";
    std::cout << "=======================\n\n";
}

unsigned Projection::totalCount = 0;