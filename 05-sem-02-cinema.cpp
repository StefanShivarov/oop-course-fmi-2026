#include <iostream>

#include "Cinema.h"

int main() {
    Movie inception("Inception", "Sci-Fi", 148, 15.00);
    Hall smallHall(10);
    Projection proj(&inception, &smallHall, "21:00");

    proj.reserveSeat(3);
    proj.reserveSeat(4);
    proj.reserveSeat(10);

    proj.reserveSeat(3);
    proj.reserveSeat(15);
    proj.reserveSeat(0);
    std::cout << "Free seats left: " << proj.getFreeSeatsCount() << "\n";

    proj.freeSeat(4);
    proj.freeSeat(4);
    std::cout << "Free seats left: " << proj.getFreeSeatsCount() << "\n";

    proj.displayInformation();

    Movie interstellar("Interstellar", "Sci-Fi", 169, 18.50);

    Hall bigHall(50);

    Projection proj2(&interstellar, &bigHall, "18:30");

    proj2.reserveSeat(1);
    proj2.reserveSeat(2);
    proj2.reserveSeat(50);

    std::cout << "Free seats left (Interstellar): " << proj2.getFreeSeatsCount() << "\n\n";

    proj2.displayInformation();

    Cinema cinema("Odeon");

    cinema.addProjection(proj);
    cinema.addProjection(proj2);
    cinema.displayProjections();

    cinema.removeProjection(1);
    cinema.displayProjections();

    return 0;
}