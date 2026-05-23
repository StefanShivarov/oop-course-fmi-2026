#include "BikeDeliveryOption.h"
#include <iostream>

std::string BikeDeliveryOption::getName() const {
    return "Bike delivery";
}

double BikeDeliveryOption::calculatePrice(const Shipment& shipment) const {
    return 3.00 + shipment.getDistance() * 0.60;
}

double BikeDeliveryOption::estimateHours(const Shipment& shipment) const {
    return shipment.getDistance() / 15.0 + 0.25;
}
