#pragma once
#include "Registration.h"
#include <iostream>

enum class EventType {
    SEMINAR,
    CONCERT,
    SPORTS_EVENT,
    WORKSHOP,
    OTHER
};

class Event {
public:
    Event(const char* name,
          const char* description,
          EventType type,
          double baseParticipationPrice,
          size_t capacity);

    Event(const Event& other);
    Event& operator=(const Event& other);

    Event(Event&& other) noexcept;
    Event& operator=(Event&& other) noexcept;

    ~Event();

    const char* getName() const;
    const char* getDescription() const;
    EventType getType() const;
    double getBaseParticipationPrice() const;
    size_t getCapacity() const;
    size_t getTakenSeatsCount() const;
    size_t getFreeSeatsCount() const;

    double getCurrentRevenue() const;

    bool registerUser(User& user, bool premiumTicket = false);
    bool registerUser(User* user, bool premiumTicket = false);
    bool registerUserAtSeat(User& user, size_t seatIndex, bool premiumTicket = false);
    bool registerUserAtSeat(User* user, size_t seatIndex, bool premiumTicket = false);

    bool removeRegistration(size_t seatIndex);

    const Registration* operator[](size_t index) const;

private:
    char* name = nullptr;
    char* description = nullptr;
    EventType type = EventType::OTHER;
    double baseParticipationPrice = 0.0;
    // you can also potentially add
    // Date date;
    // Time time;

    Registration** seats = nullptr;
    size_t capacity = 0;
    size_t takenSeatsCount = 0;
    size_t firstFreeSeatIndex = 0;

    void free();
    void copyFrom(const Event& other);
    void moveFrom(Event&& other) noexcept;

    void updateFirstFreeSeatIndex();

    double calculatePriceForUser(const User& user, bool premiumTicket = false) const;
    static TicketType getTicketTypeForUser(const User& user, bool premiumTicket = false);

    bool addRegistration(Registration* reg, size_t seatIndex);
};

void printEvent(const Event& event);
