#pragma once
#include <string>
#include "Shipment.h"

class DeliveryOption {
public:
    virtual std::string getName() const = 0;
    virtual double calculatePrice(const Shipment& shipment) const = 0;
    virtual double estimateHours(const Shipment& shipment) const = 0;
    virtual ~DeliveryOption() = default;
};
