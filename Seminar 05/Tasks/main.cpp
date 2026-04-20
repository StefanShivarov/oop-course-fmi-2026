#include <iostream>
#include <cstring>
#pragma warning(disable: 4996)
#include "CinemaSystem.h"
#include "Movie.h"
#include "Hall.h"
#include "Date.h"
#include "Time.h"

int main() {
    Movie movie1("Peaky Blinders: The Immortal Man", Genre::Action, 154, 15.50);
    Movie movie2("Project Hail Mary", Genre::Comedy, 146, 16.00);
    Movie movie3("F1: The Movie", Genre::Other, 155, 14.50);

    Hall hall1(50);
    Hall hall2(80);
    Hall hall3(30);

    Date d1(28, 3, 2026);
    Date d2(29, 3, 2026);
    Date d3(30, 3, 2026);

    Time t1(18, 30);
    Time t2(20, 0);
    Time t3(19, 15);

    CinemaSystem cinema;
    cinema.addScreening(&movie1, &hall1, d1, t1);
    cinema.addScreening(&movie2, &hall2, d2, t2);
    cinema.addScreening(&movie3, &hall3, d3, t3);

    std::cout << "\nAll screenings:\n";
    printAllScreenings(cinema);

    std::cout << "\nReserve seats for screening with ID 1:\n";
    if (cinema.reserveSeat(1, 5)) {
        std::cout << "Seat 5 reserved successfully.\n";
    }
    else {
        std::cout << "Could not reserve seat 5.\n";
    }

    if (cinema.reserveSeat(1, 10)) {
        std::cout << "Seat 10 reserved successfully.\n";
    }
    else {
        std::cout << "Could not reserve seat 10.\n";
    }

    std::cout << "\nTrying to reserve seat 5 again:\n";
    if (cinema.reserveSeat(1, 5)) {
        std::cout << "Seat 5 reserved successfully.\n";
    }
    else {
        std::cout << "Seat 5 is already taken.\n";
    }

    std::cout << "\nCheck if seats are free:\n";
    std::cout << "Seat 5 in screening 1 is "
        << (cinema.isSeatFree(1, 5) ? "free" : "occupied") << ".\n";

    std::cout << "Seat 6 in screening 1 is "
        << (cinema.isSeatFree(1, 6) ? "free" : "occupied") << ".\n";

    std::cout << "\nFree seats in screening 1: "
        << cinema.getFreeSeatsCount(1) << '\n';

    std::cout << "\nRelease seat 5 from screening 1:\n";
    if (cinema.releaseSeat(1, 5)) {
        std::cout << "Seat 5 released successfully.\n";
    }
    else {
        std::cout << "Could not release seat 5.\n";
    }

    std::cout << "Seat 5 in screening 1 is now "
        << (cinema.isSeatFree(1, 5) ? "free" : "occupied") << ".\n";

    std::cout << "\nFree seats in screening 1 after release: "
        << cinema.getFreeSeatsCount(1) << '\n';

    std::cout << "\nRemove screening with ID 2:\n";
    if (cinema.removeScreening(2)) {
        std::cout << "Screening 2 removed successfully.\n";
    }
    else {
        std::cout << "Screening 2 not found.\n";
    }

    std::cout << "\nAll screenings after removal:\n";
    printAllScreenings(cinema);

    std::cout << "\nTrying to access removed screening 2:\n";
    const Screening* s = cinema.getScreeningById(2);
    if (s) {
        printScreening(*s);
    }
    else {
        std::cout << "Screening 2 does not exist.\n";
    }
}