#include "Parking.h"
#include "ParkingFeeCalculator.h"

Parking::Parking(size_t maxCapacity) : maxCapacity(maxCapacity) {
    spaces = new CarEntry*[maxCapacity]{nullptr};
}

void Parking::free() {
    for (size_t i = 0; i < maxCapacity; i++) {
        delete spaces[i];
    }

    delete[] spaces;
    spaces = nullptr;
    carsCount = 0;
    maxCapacity = 0;
    firstFreeSpaceIndex = 0;
}

void Parking::copyFrom(const Parking& other) {
    maxCapacity = other.maxCapacity;
    carsCount = other.carsCount;
    firstFreeSpaceIndex = other.firstFreeSpaceIndex;

    spaces = new CarEntry*[maxCapacity]{nullptr};

    for (size_t i = 0; i < maxCapacity; i++) {
        if (other.spaces[i]) {
            spaces[i] = new CarEntry(*other.spaces[i]);
        }
    }
}

void Parking::moveFrom(Parking&& other) noexcept {
    spaces = other.spaces;
    carsCount = other.carsCount;
    maxCapacity = other.maxCapacity;
    firstFreeSpaceIndex = other.firstFreeSpaceIndex;

    other.spaces = nullptr;
    other.carsCount = 0;
    other.maxCapacity = 0;
    other.firstFreeSpaceIndex = 0;
}

Parking::Parking(const Parking& other) {
    copyFrom(other);
}

Parking& Parking::operator=(const Parking& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

Parking::Parking(Parking&& other) noexcept {
    moveFrom(std::move(other));
}

Parking& Parking::operator=(Parking&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}

Parking::~Parking() {
    free();
}

size_t Parking::getTakenSpacesCount() const {
    return carsCount;
}

size_t Parking::getFreeSpacesCount() const {
    return maxCapacity - carsCount;
}

size_t Parking::getMaxCapacity() const {
    return maxCapacity;
}

bool Parking::parkCar(const CarEntry& entry) {
    return parkCarAtSpace(entry, firstFreeSpaceIndex);
}

bool Parking::parkCar(CarEntry&& entry) {
    return parkCarAtSpace(std::move(entry), firstFreeSpaceIndex);
}

bool Parking::parkCar(CarEntry* entry) {
    return parkCarAtSpace(entry, firstFreeSpaceIndex);
}

bool Parking::parkCarAtSpace(const CarEntry& entry, size_t spaceIndex) {
    if (carsCount >= maxCapacity || firstFreeSpaceIndex >= maxCapacity) {
        return false;
    }

    if (spaceIndex >= maxCapacity || spaces[spaceIndex]) {
        spaceIndex = firstFreeSpaceIndex;
    }

    spaces[spaceIndex] = new CarEntry(entry);
    carsCount++;
    updateFirstFreeSpaceIndex();
    return true;
}

bool Parking::parkCarAtSpace(CarEntry&& entry, size_t spaceIndex) {
    if (carsCount >= maxCapacity || firstFreeSpaceIndex >= maxCapacity) {
        return false;
    }

    if (spaceIndex >= maxCapacity || spaces[spaceIndex]) {
        spaceIndex = firstFreeSpaceIndex;
    }

    spaces[spaceIndex] = new CarEntry(std::move(entry));
    carsCount++;
    updateFirstFreeSpaceIndex();
    return true;
}

bool Parking::parkCarAtSpace(CarEntry* entry, size_t spaceIndex) {
    if (!entry || carsCount >= maxCapacity || firstFreeSpaceIndex >= maxCapacity) {
        return false;
    }

    if (spaceIndex >= maxCapacity || spaces[spaceIndex]) {
        spaceIndex = firstFreeSpaceIndex;
    }
    // if you want to take ownership of this ptr, then do:
    spaces[spaceIndex] = entry;
    // if you don't want to take ownership of the passed ptr:
    // spaces[firstFreeSpaceIndex] = new CarEntry(*entry);
    carsCount++;
    updateFirstFreeSpaceIndex();
    return true;
}

unsigned Parking::removeCar(size_t index, const Date& exitDate, const Time& exitTime) {
    if (index >= maxCapacity) {
        //throw std::out_of_range("Space index out of range");
        return 0;
    }

    if (!spaces[index]) {
        // throw
        return 0;
    }

    if (spaces[index]->getEntryDate() > exitDate) {
        // throw
        return 0;
    }

    if (spaces[index]->getEntryDate() == exitDate && spaces[index]->getEntryTime() > exitTime) {
        // throw
        return 0;
    }

    unsigned price = ParkingFeeCalculator::calculatePrice(*spaces[index], exitDate, exitTime);

    delete spaces[index]; // !
    spaces[index] = nullptr;
    carsCount--;

    if (index < firstFreeSpaceIndex) {
        firstFreeSpaceIndex = index;
    }

    return price;
}

const CarEntry* Parking::operator[](size_t index) const {
    if (index >= maxCapacity) {
        throw std::out_of_range("Car index out of range");
    }

    return spaces[index];
}

void Parking::updateFirstFreeSpaceIndex() {
    for (size_t i = 0; i < maxCapacity; i++) {
        if (!spaces[i]) {
            firstFreeSpaceIndex = i;
            return;
        }
    }

    firstFreeSpaceIndex = maxCapacity;
}
