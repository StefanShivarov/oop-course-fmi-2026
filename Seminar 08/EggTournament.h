#pragma once
#include "Egg.h"
#include <iostream>
#include <queue>
#include <optional>
class EggTournament
{
private:
    Egg Borets;
    std::queue<Egg> Eggs;

public:
    EggTournament();
    void addEgg(const Egg &newEgg);
    template <typename... Args>
    void addEggs(const Egg &first, const Args &...rest)
    {
        addEgg(first);
        addEggs(rest...);
    }
    void addEggs() {}
    void playNextBattle();
    std::optional<Egg> borets();
    bool isFinished();
};