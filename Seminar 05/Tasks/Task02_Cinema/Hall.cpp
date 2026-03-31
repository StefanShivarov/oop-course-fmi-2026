#include "Hall.h"

unsigned Hall::totalRoomsCount = 0;

Hall::Hall(unsigned seatsCount) : id(++totalRoomsCount), seatsCount(seatsCount) {}

unsigned Hall::getId() const
{
    return id;
}

unsigned Hall::getSeatsCount() const
{
    return seatsCount;
}

void printHall(const Hall& hall, std::ostream& os) {
    os << "Hall #" << hall.getId() << ", Seats: " << hall.getSeatsCount() << '\n';
}
