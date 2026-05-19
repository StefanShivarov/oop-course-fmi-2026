#pragma once
#include "Date.h"
#include "Time.h"
#include "CarEntry.h"

class ParkingFeeCalculator {
public:
    static unsigned calculatePrice(
        const CarEntry& entry,
        const Date& exitDate,
        const Time& exitTime
    );

private:
    static unsigned calculateStayMinutes(
        const CarEntry& entry,
        const Date& exitDate,
        const Time& exitTime
    );
};
