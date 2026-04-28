#pragma once
#include "EventType.h"
#include "Registration.h"
#include "ProfitConfig.h"
class Event
{
private:
    char* name;
    char* description;
    EventType type;
    double baseParticipationPrice;
    int maxSeats;
    double singleTicketPrice;

    Registration** seats;

    static char* copyString(const char* input);
    static bool areEqual(const char* first, const char* second);
    void copyFrom(const Event& other);
    void free();
   

public:
    int findFirstFreeSeat() const;
    bool hasFreeSeat() const;
    bool alreadyRegistered(const char* email) const;
    double calculateRegistrationPrice() const;
    Event(const char* name,
        const char* description,
        EventType type,
        double baseParticipationPrice,
        int maxSeats,
        double singleTicketPrice);

    Event(const Event& other);
    Event& operator=(const Event& other);
    ~Event();

    const char* getName() const;
    const char* getDescription() const;
    EventType getType() const;
    int getMaxSeats() const;
    int getOccupiedSeatsCount() const;
    int getFreeSeatsCount() const;

    bool addRegistration(const Registration& reg);
    bool addRegistration(Registration&& reg);
    bool addRegistration(const Registration* reg);
    bool addRegistrationAtSeat(const Registration& reg, int seatIndex);
    bool addRegistrationAtSeat(Registration&& reg, int seatIndex);
    bool addRegistrationAtSeat(const Registration* reg, int seatIndex);


    bool removeRegistrationBySeat(int seatIndex);
    bool removeRegistrationByEmail(const char* email);
    double calculateRevenue() const;
    double calculateExpectedProfit(const ProfitConfig& config) const;
    void printSeats() const;
};

