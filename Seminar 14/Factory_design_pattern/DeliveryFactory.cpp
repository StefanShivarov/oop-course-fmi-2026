#include "DeliveryFactory.h"

#include "BikeDeliveryOption.h"
#include "CarDeliveryOption.h"
#include "TruckDeliveryOption.h"
#include "VanDeliveryOption.h"

std::unique_ptr<DeliveryOption> DeliveryFactory::createDelivery(const Shipment& shipment) {
    if (shipment.getWeight() <= 5.0 && shipment.getVolume() <= 0.05 && shipment.getDistance() <= 5) {
        return std::make_unique<BikeDeliveryOption>();
    }

    if (shipment.getWeight() <= 50.0 && shipment.getVolume() <= 1.0) {
        return std::make_unique<CarDeliveryOption>();
    }

    if (shipment.getWeight() <= 400.0 && shipment.getVolume() <= 6.0) {
        return std::make_unique<VanDeliveryOption>();
    }

    return std::make_unique<TruckDeliveryOption>();
}
