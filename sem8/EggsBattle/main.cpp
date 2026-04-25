#include <iostream>
#include "Egg.h"
#include "EggTournament.h"

using std::cout;

int main()
{
    Egg e1("Egg1", 30, 20, 7, 3);
    Egg e2("Egg2", 60, 10, 11, 7);
    Egg e3("Egg3", 45, 8, 16, 2);
    Egg e4("Egg4", 17, 15, 9, 8);

    EggTournament tournament;
    tournament.addEgg(e1);
    tournament.addEgg(e2);
    tournament.addEgg(e3);
    tournament.addEgg(e4);

    cout << "--------- EGG TOURNAMENT ----------" << '\n';

    std::optional<Egg> currentFighter = tournament.getCurrentFighter();
    cout << "Current Fighter: " << *currentFighter << '\n';

    while (tournament.hasNextBattle()) {
        tournament.playNextBattle();
        cout << "Winner of round: " << *tournament.getCurrentFighter();
    }
    
    cout << '\n';

    cout << "--------- TOURNAMENT OVER ---------" << '\n';
    cout << "WINNER: " << *tournament.getCurrentFighter();
}

