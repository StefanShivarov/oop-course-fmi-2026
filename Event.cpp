#define _CRT_SECURE_NO_WARNINGS
#include "Event.h"
#include <cstring>
#include <iostream>

char* Event::copyString(const char* input)
{
    if (!input)
    { return nullptr;
    }

    size_t len = std::strlen(input);
    char* result = new char[len + 1];
    std::strcpy(result, input);
    return result;
}

bool Event::areEqual(const char* first, const char* second)
{
    if (!first || !second)
    {
        return false;
    }
return std::strcmp(first, second) == 0;
}

Event::Event(const char* name,const char* description,EventType type,double baseParticipationPrice,int maxSeats,double singleTicketPrice)
{
    this->name = copyString(name);
    this->description = copyString(description);
    this->type = type;
    this->baseParticipationPrice = baseParticipationPrice;
    this->maxSeats = maxSeats;
    this->singleTicketPrice = singleTicketPrice;
    seats = new Registration * [maxSeats];
    for (int i = 0; i < maxSeats; i++)
    {
        seats[i] = nullptr;
    }
}

void Event::copyFrom(const Event& other)
{
    name = copyString(other.name);
    description = copyString(other.description);
    type = other.type;
    baseParticipationPrice = other.baseParticipationPrice;
    maxSeats = other.maxSeats;
    singleTicketPrice = other.singleTicketPrice;
    seats = new Registration * [maxSeats];

    for (int i = 0; i < maxSeats; i++)
    {if (other.seats[i] != nullptr)
        {
            seats[i] = new Registration(*other.seats[i]);
        }
        else
        {
            seats[i] = nullptr;
        }
    }
}

void Event::free()
{
    delete[] name;
    delete[] description;

    for (int i = 0; i < maxSeats; i++)
    {
        delete seats[i];
    }
    delete[] seats;
    name = nullptr;
    description = nullptr;
    seats = nullptr;
}

Event::Event(const Event& other)
{
    copyFrom(other);
}

Event& Event::operator=(const Event& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

Event::~Event()
{
    free();
}

const char* Event::getName() const
{
    return name;
}

const char* Event::getDescription() const
{
    return description;
}

EventType Event::getType() const
{
    return type;
}

int Event::getMaxSeats() const
{
    return maxSeats;
}

int Event::findFirstFreeSeat() const
{
    for (int i = 0; i < maxSeats; i++)
    {
        if (seats[i] == nullptr)
        {
            return i;
        }
    }


    return -1;
}

bool Event::hasFreeSeat() const
{
    return findFirstFreeSeat() != -1;
}

bool Event::alreadyRegistered(const char* email) const
{
    for (int i = 0; i < maxSeats; i++)
    { if (seats[i] != nullptr && seats[i]->getUser() != nullptr)
        {
            if (areEqual(seats[i]->getUser()->getEmail(), email))
            {
                return true;
            }
        }
    }

    return false;
}

double Event::calculateRegistrationPrice() const
{
    return baseParticipationPrice + singleTicketPrice;
}

int Event::getOccupiedSeatsCount() const
{
    int count = 0;

    for (int i = 0; i < maxSeats; i++)
    {
        if (seats[i] != nullptr)
        {
            count++;
        }
    }

    return count;
}

int Event::getFreeSeatsCount() const
{
    return maxSeats - getOccupiedSeatsCount();
}

bool Event::addRegistration(const Registration& reg)
{
    int freeSeat = findFirstFreeSeat();
    if (freeSeat == -1)
    {
        return false;
    }

    User* user = reg.getUser();
    if (user == nullptr)
    {
        return false;
    }
    if (alreadyRegistered(user->getEmail()))
    {
        return false;
    }

    double price = calculateRegistrationPrice();
    if (!user->canAfford(price))
    {
        return false;
    }

    user->spend(price);
    Registration* newReg = new Registration(reg);
    newReg->setSeatIndex(freeSeat);
    newReg->setPaidPrice(price);
    seats[freeSeat] = newReg;

    return true;
}

bool Event::addRegistration(Registration&& reg)
{
    return addRegistration(reg);
}

bool Event::addRegistration(const Registration* reg)
{
    if (reg == nullptr)
    {
        return false;
    }

    return addRegistration(*reg);
}

bool Event::addRegistrationAtSeat(const Registration& reg, int seatIndex)
{
    if (seatIndex < 0 || seatIndex >= maxSeats)
    {
        return false;
    }

    if (seats[seatIndex] != nullptr)
    {
        return addRegistration(reg);
    }

    User* user = reg.getUser();
    if (user == nullptr)
    {
        return false;
    }

    if (alreadyRegistered(user->getEmail()))
    {
        return false;
    }
    double price = calculateRegistrationPrice();

    if (!user->canAfford(price))
    {
        return false;
    }
    user->spend(price);

    Registration* newReg = new Registration(reg);
    newReg->setSeatIndex(seatIndex);
    newReg->setPaidPrice(price);
    seats[seatIndex] = newReg;
    return true;
}

bool Event::addRegistrationAtSeat(Registration&& reg, int seatIndex)
{
    return addRegistrationAtSeat(reg, seatIndex);
}

bool Event::addRegistrationAtSeat(const Registration* reg, int seatIndex)
{
    if (reg == nullptr)
    {
        return false;
    }

    return addRegistrationAtSeat(*reg, seatIndex);
}

bool Event::removeRegistrationBySeat(int seatIndex)
{
    if (seatIndex < 0 || seatIndex >= maxSeats)
    {
        return false;
    }

    if (seats[seatIndex] == nullptr)
    {
        return false;
    }

    delete seats[seatIndex];
    seats[seatIndex] = nullptr;
    return true;
}

bool Event::removeRegistrationByEmail(const char* email)
{
    for (int i = 0; i < maxSeats; i++)
    {
        if (seats[i] != nullptr && seats[i]->getUser() != nullptr)
        {
            if (areEqual(seats[i]->getUser()->getEmail(), email))
            {
                delete seats[i];
                seats[i] = nullptr;

                return true;
            }
        }
    }
    return false;
}

double Event::calculateRevenue() const
{
    double revenue = 0.0;
    for (int i = 0; i < maxSeats; i++)
    {
        if (seats[i] != nullptr)
        {
            revenue += seats[i]->getPaidPrice();
        }
    }
    return revenue;
}

double Event::calculateExpectedProfit(const ProfitConfig& config) const
{
    double revenue = calculateRevenue();
    double result = revenue;
    if (config.hasFixed())
    {
        result -= config.getFixedCost();
    }

    if (config.hasVenue())
    {
        result -= revenue * config.getVenueFeePercent();
    }

    if (config.hasPerPerson())
    {
        result -= config.getPerPersonCost() * getOccupiedSeatsCount();
    }

    if (config.hasCharityValue())
    {
        result -= config.getCharityAmount();
    }


    return result;
}

void Event::printSeats() const
{
    std::cout << "Event: " << name << std::endl;
    std::cout << "Occupied seats: " << getOccupiedSeatsCount() << std::endl;
    std::cout << "Free seats: " << getFreeSeatsCount() << std::endl;

    for (int i = 0; i < maxSeats; i++)
    {
        std::cout << "Seat " << i << ": ";
        if (seats[i] == nullptr)
        {
            std::cout << "free";
        }
        else
        {
            std::cout << "occupied by " << seats[i]->getUser()->getEmail()
                << ", paid " << std::fixed << seats[i]->getPaidPrice();
        }
        std::cout << std::endl;
    }
}
