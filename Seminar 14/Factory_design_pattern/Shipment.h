#pragma once

#include <string>

class Shipment {
public:
    Shipment(const std::string& description, double weight, double volume, double distance);

    const std::string& getDescription() const;
    double getWeight() const;
    double getVolume() const;
    double getDistance() const;

private:
    std::string description;
    double weight = 0;
    double volume = 0;
    double distance = 0;
};
