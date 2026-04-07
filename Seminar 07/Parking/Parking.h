#pragma once
#include <iostream>
#include "CarEntry.h"

using std::size_t;

class Parking {
public:
    explicit Parking(size_t maxCapacity);

    Parking(const Parking& other);
    Parking& operator=(const Parking& other);

    Parking(Parking&& other) noexcept;
    Parking& operator=(Parking&& other) noexcept;

    ~Parking();

    size_t getTakenSpacesCount() const;
    size_t getFreeSpacesCount() const;
    size_t getMaxCapacity() const;

    bool parkCar(const CarEntry& entry);
    bool parkCar(CarEntry&& entry);
    bool parkCar(CarEntry* entry);

    bool parkCarAtSpace(const CarEntry& entry, size_t spaceIndex);
    bool parkCarAtSpace(CarEntry&& entry, size_t spaceIndex);
    bool parkCarAtSpace(CarEntry* entry, size_t spaceIndex);

    unsigned removeCar(size_t index, const Date& exitDate, const Time& exitTime);

    const CarEntry* operator[](size_t index) const;

private:
    CarEntry** spaces = nullptr;
    size_t carsCount = 0;
    size_t maxCapacity = 0;
    size_t firstFreeSpaceIndex = 0;

    void updateFirstFreeSpaceIndex();

    void copyFrom(const Parking& other);
    void moveFrom(Parking&& other) noexcept;
    void free();
};