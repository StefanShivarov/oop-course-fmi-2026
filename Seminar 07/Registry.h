#pragma once
#include "Event.h"
#include "Ticket.h"

class Registry
{
private:
    size_t count = 0;
    Event event;
    Ticket** tickets = nullptr;

    int firstFree() const;
    void copyDynamicMemory(const Registry& other);
    void copyFrom(const Registry& other);
    void moveFrom(Registry&& other) noexcept;
    void free();

public:
    explicit Registry(const Event& event);
    Registry(const Registry& other);
    Registry& operator=(const Registry& other);
    Registry(Registry&& other) noexcept;
    Registry& operator=(Registry&& other) noexcept;
    ~Registry();

    size_t getFree() const;
    size_t getTaken() const;
    const Event& getEvent() const;

    bool addPerson(const Person& person);
    bool addPerson(Person&& person);
    bool addPerson(Person* person);
    bool addPersonAtSlot(const Person& person, size_t slot);
    bool addPersonAtSlot(Person&& person, size_t slot);
    bool addPersonAtSlot(Person* person, size_t slot);
    void removePerson(size_t slot);

    const Ticket* operator[](size_t index) const;
    double calculate() const;
};