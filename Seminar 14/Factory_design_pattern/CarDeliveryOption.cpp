#include "CarDeliveryOption.h"
#include <iostream>

std::string CarDeliveryOption::getName() const {
    return "Car delivery";
}

double CarDeliveryOption::calculatePrice(const Shipment& shipment) const {
    return 7.00
        + shipment.getDistance() * 0.90
        + shipment.getWeight() * 0.10;
}

double CarDeliveryOption::estimateHours(const Shipment& shipment) const {
    return shipment.getDistance() / 50.0 + 0.50;
}
