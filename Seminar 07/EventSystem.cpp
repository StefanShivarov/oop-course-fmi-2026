#pragma once
#include "EventSystem.h"
#include <iostream>

void EventSystem::resize()
{
    if (capacity == 0)
    {
        capacity = 2;
    }
    else capacity *= 2;

    Registry** newArr = new Registry * [capacity] {nullptr};
    for (size_t i = 0; i < count; i++)
    {
        newArr[i] = registries[i];
    }
    delete[] registries;
    registries = newArr;
}

void EventSystem::copyFrom(const EventSystem& other)
{
    count = other.count;
    capacity = other.capacity;
    registries = new Registry * [capacity] {nullptr};
    for (size_t i = 0; i < count; i++)
    {
        registries[i] = new Registry(*other.registries[i]);
    }
}

void EventSystem::moveFrom(EventSystem&& other) noexcept
{
    count = other.count;
    capacity = other.capacity;
    registries = other.registries;
    other.registries = nullptr;
    other.count = other.capacity = 0;
}

void EventSystem::free()
{
    for (size_t i = 0; i < count; i++)
    {
        delete registries[i];
    }
    delete[] registries;
}

EventSystem::EventSystem() = default;

EventSystem::EventSystem(const EventSystem& other)
{
    copyFrom(other);
}

EventSystem& EventSystem::operator=(const EventSystem& other)
{
    if (this != &other) 
    {
        free();
        copyFrom(other); 
    }
    return *this;
}

EventSystem::EventSystem(EventSystem&& other) noexcept
{
    moveFrom(std::move(other));
}

EventSystem& EventSystem::operator=(EventSystem&& other) noexcept
{
    if (this != &other) 
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

EventSystem::~EventSystem()
{
    free();
}

void EventSystem::addRegistry(const Registry& reg)
{
    if (count == capacity) resize();
    registries[count++] = new Registry(reg);
}

void EventSystem::removeRegistry(size_t index)
{
    if (index >= count) return;
    delete registries[index];
    registries[index] = registries[--count];
    registries[count] = nullptr;
}

const Registry* EventSystem::operator[](size_t index) const
{
    if (index >= count) return nullptr;
    return registries[index];
}

size_t EventSystem::getCount() const
{
    return count;
}