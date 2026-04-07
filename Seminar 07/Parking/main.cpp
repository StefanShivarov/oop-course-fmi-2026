#include <iostream>
#include "Parking.h"
#include "CarEntry.h"
#include "Date.h"
#include "Time.h"

int main() {
    Parking parking(3);

    CarEntry c1("XY1234AB", Date(1, 6, 2025), Time(8, 0));

    parking.parkCar(c1);
    parking.parkCar(CarEntry("XY5678CD", Date(1, 6, 2025), Time(8, 30)));
    parking.parkCar(new CarEntry("XY999KK", Date(1, 6, 2025), Time(9, 15)));

    std::cout << "Taken: " << parking.getTakenSpacesCount() << '\n';
    std::cout << "Free: " << parking.getFreeSpacesCount() << '\n';

    double price = parking.removeCar(1, c1.getEntryDate(), Time(12, 30));
    std::cout << "Price: " << price << '\n';

    std::cout << "After removing car from space 1:\n";
    std::cout << "Taken: " << parking.getTakenSpacesCount() << '\n';
    std::cout << "Free: " << parking.getFreeSpacesCount() << '\n';
}
