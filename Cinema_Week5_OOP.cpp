#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<print>
#include"Cinema.h"

int main()
{
    Film film1("Love", Type::Drama, Time{ 2, 28 }, 12.5);
    Film film2("Friends", "Comedy", Time{1, 30}, 8.0);
    Film film3("Horror Night", "Horror", Time{ 1, 45 }, 10.0);

    Hall hall1(100);
    Hall hall2(80);

    Screening s1(&film1, &hall1, "26.03.2026", Time{ 20, 0 });
    Screening s2(&film2, &hall2, "25.03.2026", Time{ 18, 30 });
    Screening s3(&film3, &hall1, "27.03.2026", Time{ 16, 0 });

    Cinema cinema;
    cinema.addScreening(s1);
    cinema.addScreening(s2);
    cinema.addScreening(s3);

    std::println("\nAll screenings:");
    cinema.printCinema();

    size_t id = s2.getId();
    std::println("\nScreening with id {}:", id);
    cinema.printById(id);

    Screening* screen = cinema.getById(s1.getId());
    if (screen) 
    {
        screen->reserveSeat(0);
        screen->reserveSeat(1);
        screen->reserveSeat(2);
        std::println("\nFree seats for {}: {}", screen->getFilm()->getTitle(), screen->freeSeatsCount());
    }

    screen->freeSeat(1);
    std::println("After free: {}", screen->freeSeatsCount());

    cinema.removeScreening(s3.getId());
    std::println("\nAfter remove:");
    cinema.printCinema();

    return 0;
}
