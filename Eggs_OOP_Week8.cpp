#include <iostream>
#include<print>
#include"EggTournament.h"

int main()
{
    Egg e1("Red", 100, 20, 10, 15);
    Egg e2("Blue", 80, 25, 5, 20);
    Egg e3("Green", 120, 15, 20, 10);

    EggTournament t;

    t.addEgg(e1);
    t.addEgg(e2);
    t.addEgg(e3);

    t.playNextBattle();

    auto winner = t.getCurrentFighter();

    if (winner.has_value())
    {
        std::println("The winner is {}!", winner->getName());
    }
}
