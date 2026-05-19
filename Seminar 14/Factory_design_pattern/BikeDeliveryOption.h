#pragma once

#pragma once

#include "DeliveryOption.h"

class BikeDeliveryOption : public DeliveryOption {
public:
    std::string getName() const override;
    double calculatePrice(const Shipment& shipment) const override;
    double estimateHours(const Shipment& shipment) const override;
};