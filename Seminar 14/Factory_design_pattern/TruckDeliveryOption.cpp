#include "TruckDeliveryOption.h"
#include <iostream>

std::string TruckDeliveryOption::getName() const {
    return "Truck delivery";
}

double TruckDeliveryOption::calculatePrice(const Shipment& shipment) const {
    return 80.00
        + shipment.getDistance() * 2.00
        + shipment.getWeight() * 0.20
        + shipment.getVolume() * 5.00;
}

double TruckDeliveryOption::estimateHours(const Shipment& shipment) const {
    return shipment.getDistance() / 35.0 + 2.00;
}
