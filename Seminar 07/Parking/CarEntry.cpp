#include "CarEntry.h"
#pragma warning(disable:4996)

namespace {
    void deepCopyString(char*& dest, const char* src) {
        if (!src) {
            dest = nullptr;
            return;
        }

        dest = new char[strlen(src) + 1];
        strcpy(dest, src);
    }
}

CarEntry::CarEntry(const char* licensePlate, const Date& entryDate, const Time& entryTime)
    : entryDate(entryDate), entryTime(entryTime) {
    setLicensePlate(licensePlate);
}

void CarEntry::free() {
    delete[] licensePlate;
    licensePlate = nullptr;
}

void CarEntry::copyFrom(const CarEntry& other) {
    deepCopyString(licensePlate, other.licensePlate);
    entryDate = other.entryDate;
    entryTime = other.entryTime;
}

void CarEntry::moveFrom(CarEntry&& other) noexcept {
    licensePlate = other.licensePlate;
    other.licensePlate = nullptr;
    entryDate = other.entryDate;
    entryTime = other.entryTime;
}

CarEntry::CarEntry(const CarEntry& other) {
    copyFrom(other);
}

CarEntry& CarEntry::operator=(const CarEntry& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

CarEntry::CarEntry(CarEntry&& other) noexcept {
    moveFrom(std::move(other));
}

CarEntry& CarEntry::operator=(CarEntry&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}

CarEntry::~CarEntry() {
    free();
}

const char* CarEntry::getLicensePlate() const {
    return licensePlate;
}

const Date& CarEntry::getEntryDate() const {
    return entryDate;
}

const Time& CarEntry::getEntryTime() const {
    return entryTime;
}

void CarEntry::setLicensePlate(const char* licensePlate) {
    delete[] this->licensePlate;
    deepCopyString(this->licensePlate, licensePlate);
}

void CarEntry::setEntryDate(const Date& entryDate) {
    this->entryDate = entryDate;
}

void CarEntry::setEntryTime(const Time& entryTime) {
    this->entryTime = entryTime;
}
