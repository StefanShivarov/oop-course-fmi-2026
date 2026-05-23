#include "Shipment.h"

#include "Shipment.h"

#include <stdexcept>

Shipment::Shipment(const std::string& description, double weight, double volume, double distance)
    : description(description), weight(weight), volume(volume), distance(distance) {}

const std::string& Shipment::getDescription() const {
    return description;
}

double Shipment::getWeight() const {
    return weight;
}

double Shipment::getVolume() const {
    return volume;
}

double Shipment::getDistance() const {
    return distance;
}
