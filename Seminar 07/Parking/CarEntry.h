#pragma once
#include "Date.h"
#include "Time.h"

class CarEntry {
public:
    CarEntry(const char* licensePlate, const Date& entryDate, const Time& entryTime);

    CarEntry(const CarEntry& other);
    CarEntry& operator=(const CarEntry& other);

    CarEntry(CarEntry&& other) noexcept;
    CarEntry& operator=(CarEntry&& other) noexcept;

    ~CarEntry();

    const char* getLicensePlate() const;
    const Date& getEntryDate() const;
    const Time& getEntryTime() const;

    void setLicensePlate(const char* licensePlate);
    void setEntryDate(const Date& entryDate);
    void setEntryTime(const Time& entryTime);

private:
    char* licensePlate = nullptr;
    Date entryDate;
    Time entryTime;

    void copyFrom(const CarEntry& other);
    void moveFrom(CarEntry&& other) noexcept;
    void free();
};
