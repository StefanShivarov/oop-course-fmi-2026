#define _CRT_SECURE_NO_WARNINGS
#include "Registry.h"
#include <iostream>

int Registry::firstFree() const
{
    for (int i = 0; i < (int)event.getCapacity(); i++)
        if (!tickets[i]) return i;
    return -1;
}

void Registry::copyDynamicMemory(const Registry& other)
{
    size_t cap = other.event.getCapacity();
    tickets = new Ticket * [cap] {nullptr};
    for (size_t i = 0; i < cap; i++)
        if (other.tickets[i]) tickets[i] = new Ticket(*other.tickets[i]);
}

void Registry::copyFrom(const Registry& other)
{
    event = other.event;
    copyDynamicMemory(other);
    count = other.count;
}

void Registry::moveFrom(Registry&& other) noexcept
{
    count = other.count;
    event = std::move(other.event);
    tickets = other.tickets;
    other.tickets = nullptr;
    other.count = 0;
}

void Registry::free()
{
    for (size_t i = 0; i < event.getCapacity(); i++)
        delete tickets[i];
    delete[] tickets;
    tickets = nullptr;
}

Registry::Registry(const Event& event) : event(event)
{
    tickets = new Ticket * [event.getCapacity()] {nullptr};
}

Registry::Registry(const Registry& other) : count(other.count), event(other.event)
{
    copyDynamicMemory(other);
}

Registry& Registry::operator=(const Registry& other)
{
    if (this != &other) { free(); copyFrom(other); }
    return *this;
}

Registry::Registry(Registry&& other) noexcept : event(std::move(other.event))
{
    moveFrom(std::move(other));
}

Registry& Registry::operator=(Registry&& other) noexcept
{
    if (this != &other) { free(); moveFrom(std::move(other)); }
    return *this;
}

Registry::~Registry() { free(); }

size_t Registry::getFree() const { return event.getCapacity() - count; }
size_t Registry::getTaken() const { return count; }
const Event& Registry::getEvent() const { return event; }

bool Registry::addPersonAtSlot(const Person& person, size_t slot)
{
    if (count >= event.getCapacity() || firstFree() == -1
        || person.getBudget() < event.getPrice())
        return false;

    if (slot >= event.getCapacity() || tickets[slot])
        slot = firstFree();

    double price = event.getPrice();
    Person copy(person);
    copy.setBudget(person.getBudget() - price);
    tickets[slot] = new Ticket(std::move(copy), price);
    count++;
    return true;
}

bool Registry::addPersonAtSlot(Person&& person, size_t slot)
{
    if (count >= event.getCapacity() || firstFree() == -1
        || person.getBudget() < event.getPrice())
        return false;

    if (slot >= event.getCapacity() || tickets[slot])
        slot = firstFree();

    double price = event.getPrice();
    double newBudget = person.getBudget() - price;
    person.setBudget(newBudget);
    tickets[slot] = new Ticket(std::move(person), price);
    count++;
    return true;
}

bool Registry::addPersonAtSlot(Person* person, size_t slot)
{
    return addPersonAtSlot(*person, slot);
}

bool Registry::addPerson(const Person& person)
{
    return addPersonAtSlot(person, firstFree());
}

bool Registry::addPerson(Person&& person)
{
    return addPersonAtSlot(std::move(person), firstFree());
}

bool Registry::addPerson(Person* person)
{
    return addPersonAtSlot(*person, firstFree());
}

void Registry::removePerson(size_t slot)
{
    if (slot >= event.getCapacity() || !tickets[slot]) return;
    delete tickets[slot];
    tickets[slot] = nullptr;
    count--;
}

const Ticket* Registry::operator[](size_t index) const
{
    if (index >= event.getCapacity()) return nullptr;
    return tickets[index];
}

double Registry::calculate() const
{
    return count * event.getPrice();
}