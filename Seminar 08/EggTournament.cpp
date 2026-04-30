#include "EggTournament.h"

EggTournament::EggTournament()
{
    Borets = Egg("empty", 0, 0, 0, 0);
}

void EggTournament::addEgg(const Egg &newEgg)
{
    Eggs.push(newEgg);
}

void EggTournament::playNextBattle()
{
    if (isFinished())
    {
        return;
    }
    if(Borets.getHealth() <= 0){
        Borets = Eggs.front();
        Eggs.pop();
        if(Eggs.empty()) return;
    }
    Borets.addOneToGamesPlayed();
    Eggs.front().addOneToGamesPlayed();

    bool ongoing = true;
    while (ongoing)
    {
        if (Borets.getGamesPlayed() % 3 == 0)
        {
            Eggs.front().takeDamage(Borets.getCriticalStrike());
        }
        else
        {
            Eggs.front().takeDamage(Borets.getDamage());
        }
        if (Eggs.front().getHealth() > 0)
        {
            if (Eggs.front().getGamesPlayed() % 3 == 0)
            {
                Borets.takeDamage(Eggs.front().getCriticalStrike());
            }
            else
            {
                Borets.takeDamage(Eggs.front().getDamage());
            }
        }
        ongoing = (Borets.getHealth() > 0 && Eggs.front().getHealth() > 0);
    }

    if (!(Borets.getHealth() > 0))
    {
        Borets = Eggs.front();
    }
    Eggs.pop();
}
std::optional<Egg> EggTournament::borets()
{
    return Borets;
}
bool EggTournament::isFinished()
{
    return Eggs.empty();
}
