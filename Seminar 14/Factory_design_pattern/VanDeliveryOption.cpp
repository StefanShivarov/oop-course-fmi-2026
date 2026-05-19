#include "VanDeliveryOption.h"
#include <iostream>

std::string VanDeliveryOption::getName() const {
    return "Van delivery";
}

double VanDeliveryOption::calculatePrice(const Shipment& shipment) const {
    return 20.00
        + shipment.getDistance() * 1.30
        + shipment.getWeight() * 0.15
        + shipment.getVolume() * 2.00;
}

double VanDeliveryOption::estimateHours(const Shipment& shipment) const {
    return shipment.getDistance() / 40.0 + 1.00;
}
