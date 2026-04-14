#include "ParkingFeeCalculator.h"

unsigned ParkingFeeCalculator::calculateStayMinutes(
    const CarEntry& entry,
    const Date& exitDate,
    const Time& exitTime
) {
    int daysDiff = Date::differenceInDays(exitDate, entry.getEntryDate());

    unsigned entryMinutes = entry.getEntryTime().toMinutes();
    unsigned exitMinutes = exitTime.toMinutes();

    return daysDiff * 24 * 60 + exitMinutes - entryMinutes;
}

unsigned ParkingFeeCalculator::calculatePrice(
    const CarEntry& entry,
    const Date& exitDate,
    const Time& exitTime
) {
    unsigned stayMinutes = calculateStayMinutes(entry, exitDate, exitTime);

    const unsigned FREE_MINUTES = 2 * 60;
    if (stayMinutes <= FREE_MINUTES) {
        return 0;
    }

    unsigned chargedHours = (stayMinutes + 59) / 60;
    return chargedHours * 2;
}
