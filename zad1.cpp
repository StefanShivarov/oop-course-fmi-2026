// zad1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Rock.h"
#include "Paper.h"
#include "Scissors.h"
#include "Tournament.h"
#include "Tournament.h"

int main()
{
    Rock r1;
    Paper p1;
    Scissors s1;
    Rock r2;
    Tournament tournament;
    tournament.addPlayer(&r1);
    tournament.addPlayer(&p1);
    tournament.addPlayer(&s1);
    tournament.addPlayer(&r2);
    std::cout << r1.play(s1) << std::endl;
    std::cout << p1.play(s1) << std::endl;
    std::cout << r2.play(s1) << std::endl;
    std::cout << s1.play(s1) << std::endl;
    Player* winner = tournament.getWinner();
    if (winner == &r1) {
        std::cout << "Winner is Rock r1";
    }
    else if (winner == &p1) {
        std::cout << "Winner is Paper p1";
    }
    else if (winner == &s1) {
        std::cout << "Winner is Scissors s1";
    }
    else if (winner == &r2) {
        std::cout << "Winner is Rock r2";
    }
    return 0;
}

