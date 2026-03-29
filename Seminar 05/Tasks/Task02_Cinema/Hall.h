#pragma once
#include <iostream>

class Hall
{
private:
    static unsigned totalRoomsCount;
    unsigned id;
    unsigned seatsCount;

public:
    explicit Hall(unsigned seatsCount);

    unsigned getId() const;
    unsigned getSeatsCount() const;
};

void printHall(const Hall& hall, std::ostream& os = std::cout);
