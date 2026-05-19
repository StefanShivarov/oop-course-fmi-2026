#pragma once
#include "DeliveryOption.h"

#include <memory>

class DeliveryFactory {
public:
    static std::unique_ptr<DeliveryOption> createDelivery(const Shipment& shipment);
};
