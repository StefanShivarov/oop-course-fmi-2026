#include "Event.h"
#include <iostream>
#include <cstring>

void Event::copyDynamicMemory(const Event& other)
{
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    description = new char[strlen(other.description)+1];
    strcpy(description, other.description);
}
void Event::copyFrom(const Event& other)
{
    copyDynamicMemory(other);
    type = other.type;
    capacity = other.capacity;
    basePrice = other.basePrice;
    price = other.price;
}
void Event::moveFrom(Event&& other) noexcept
{
    name = other.name;
    other.name = nullptr;
    description = other.description;
    other.description = nullptr;
    type = other.type;
    capacity = other.capacity;
    basePrice = other.basePrice;
    price = other.price;
}

void Event::free()
{
    delete[] description;
    delete[] name;
    name = nullptr;
    description = nullptr;

}
Event::Event(const char* name, const char* description, Type type, double basePrice, double price, unsigned capacity):capacity(capacity),price(price), basePrice(basePrice), type(type)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    this->description = new char[strlen(description)+1];
    strcpy(this->description, description );
}
Event::Event(const Event& other):capacity(other.capacity), price(other.price), basePrice(other.basePrice), type(other.type)
{
    copyDynamicMemory(other);
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
Event::Event(Event&& other) noexcept
{
    moveFrom(std::move(other));
}
Event& Event::operator=(Event&& other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
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

Type Event::getType() const
{
    return type;
}

double Event::getBasePrice() const
{
    return basePrice;
}

unsigned Event::getCapacity() const
{
    return capacity;
}

double Event::getPrice() const
{
    return price;
}
