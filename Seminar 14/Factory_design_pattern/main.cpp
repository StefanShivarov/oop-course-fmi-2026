#include "DeliveryFactory.h"
#include "Shipment.h"

#include <iostream>
#include <memory>
#include <vector>

void processShipment(const Shipment& shipment) {
    std::unique_ptr<DeliveryOption> delivery = DeliveryFactory::createDelivery(shipment);

    std::cout << "Shipment: " << shipment.getDescription() << '\n';
    std::cout << "Weight: " << shipment.getWeight() << " kg\n";
    std::cout << "Volume: " << shipment.getVolume() << " m3\n";
    std::cout << "Distance: " << shipment.getDistance() << " km\n";

    std::cout << delivery->getName() << '\n';
    std::cout << "Price: " << delivery->calculatePrice(shipment) << '\n';
    std::cout << "Estimated hours: " << delivery->estimateHours(shipment) << '\n';

    std::cout << "-----------------------------\n";
}

int main() {
    std::vector<Shipment> shipments;

    shipments.emplace_back("Documents", 0.5, 0.01, 4.0);
    shipments.emplace_back("Shoes box", 2.0, 0.03, 8.0);
    shipments.emplace_back("Office chair", 18.0, 0.4, 12.0);
    shipments.emplace_back("Washing machine", 75.0, 1.2, 25.0);
    shipments.emplace_back("Pallet with goods", 700.0, 10.0, 120.0);

    for (const Shipment& shipment : shipments) {
        processShipment(shipment);
    }

    return 0;
}